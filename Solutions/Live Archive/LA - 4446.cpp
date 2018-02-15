/*
Simulate the circuit completely, then if the expected outputs are the same as the ones given in the input then there's no problem.
Else, you have to run the simulation again but with picking a gate and assigning it a fault, then if the outputs with that fault 
are the same as the ones given in the input then that gate is potentially the problem. So, brute force the gates and faults (19*3=57)
and if there's is exactly one gate with exactly one fault, then you know where the fault is, else you can never know.
*/

#include<bits/stdc++.h>
#include<ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define sz(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))

typedef long long ll;
typedef vector<int> vi;

const int MAXG = 25, MAXN = 10;
int IGate[MAXG][2], OGate[MAXG], outputs[MAXG], N, G, U, TC, B, faultyGate;
int fault, numFaults, FG, F;
vector<vector<int> > inputScenarios, outputScenarios;
vi adjList[MAXG];
char CIN[20];
char gateType[MAXG];
int IGateType[MAXG][2], indegree[MAXG];
int inputVal[MAXN], outputVal[MAXN], GateOutput[MAXG];
vi tsort;
string faultStr[] = { "output stuck at 0", "output stuck at 1",
		"output inverted" };

void init() {
	CLR(IGate, 0);
	CLR(IGateType, 0);
	CLR(OGate, 0);
	CLR(outputs, 0);
	faultyGate = -1;
	numFaults = 0;
	inputScenarios.clear();
	outputScenarios.clear();
	for (int i = 0; i < MAXG; ++i)
		adjList[i].clear();
	CLR(indegree, 0);
	CLR(inputVal, 0);
	CLR(outputVal, 0);
	CLR(GateOutput, 0);
	tsort.clear();

}

bool simSameAsIP() {
	for (int i = 0; i < U; ++i)
		if (outputVal[i] != GateOutput[outputs[i]])
			return 0;
	return 1;
}

pair<int, int> getIP(int i) {
	int ret[2];
	for (int j = 0; j < 2; ++j)
		if (IGateType[i][j] == 1)
			ret[j] = GateOutput[IGate[i][j]];
		else
			ret[j] = inputVal[IGate[i][j]];
	return {ret[0],ret[1]};
}

void toposort() {
	queue<int> q;
	for (int i = 0; i < G; ++i)
		if (!indegree[i])
			q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		tsort.push_back(u);
		for (auto v : adjList[u]) {
			--indegree[v];
			if (!indegree[v])
				q.push(v);
		}
	}
}

bool sim() {
	bool ret = 1;
	for (int l = 0; l < B; ++l) {
		for (int j = 0; j < N; ++j)
			inputVal[j] = inputScenarios[l][j];
		for (int j = 0; j < U; ++j)
			outputVal[j] = outputScenarios[l][j];

		for (int k = 0; k < G; ++k) {
			int i = tsort[k];
			pair<int, int> I = getIP(i);
			int a = I.first, b = I.second;
			if (gateType[i] == 'o')
				GateOutput[i] = a || b;
			else if (gateType[i] == 'a')
				GateOutput[i] = a && b;
			else if (gateType[i] == 'x')
				GateOutput[i] = a ^ b;
			else
				GateOutput[i] = !a;
			if (i == faultyGate) {
				if (fault == 0)
					GateOutput[i] = 0;
				else if (fault == 1)
					GateOutput[i] = 1;
				else
					GateOutput[i] = !GateOutput[i];
			}
		}
		ret &= simSameAsIP();
	}
	return ret;
}

void outputInput() {
	for (int i = 0; i < U; ++i){
		scanf("%d", &outputs[i]);
		--outputs[i];
	}
}

void addEdge(int u, int v) {
	adjList[u].push_back(v);
	indegree[v]++;
}

void checkInputFromGate(int i, int j) {
	if (CIN[0] == 'g') {
		int u = 0,siz=strlen(CIN);
		for(int k =1;k<siz;++k)u=(u*10+CIN[k]-'0');
		u--;
		addEdge(u, i);
		IGateType[i][j] = 1, IGate[i][j] = u;
	} else {
		IGateType[i][j] = 0;
		IGate[i][j] = CIN[1] - '0' - 1;
	}
}

void gateInput() {
	for (int i = 0; i < G; ++i) {
		cin >> gateType[i];
		scanf("%s", CIN);
		checkInputFromGate(i, 0);
		if (gateType[i] != 'n') {
			scanf("%s", CIN);
			checkInputFromGate(i, 1);
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	while (scanf("%d%d%d", &N, &G, &U) == 3 && (N || G || U)) {
		printf("Case %d: ", ++TC);
		init();
		gateInput();
		outputInput();
		scanf("%d", &B);
		for (int j = 0; j < B; ++j) {
			vi cur(N);
			for (int i = 0; i < N; ++i)
				scanf("%d", &cur[i]);
			inputScenarios.push_back(cur);
			cur.resize(U);
			for (int i = 0; i < U; ++i)
				scanf("%d", &cur[i]);
			outputScenarios.push_back(cur);
		}
		toposort();
		faultyGate = -1;

		// for(int i=0;i<G;++i)
		// cout<<tsort[i]<<' ';
		// cout<<endl;

		bool b =sim();
		if (b)
			puts("No faults detected");
		else {
			for (int i = 0; i < G; ++i)
				for (int j = 0; j < 3; ++j) {
					faultyGate = i, fault = j;
					b = sim();
					if (b)
						++numFaults, FG = i, F = j;
				}
			if (numFaults == 1)
				printf("Gate %d is failing; %s\n", FG + 1, faultStr[F].c_str());
			else
				puts("Unable to totally classify the failure");
		}
	}
}
