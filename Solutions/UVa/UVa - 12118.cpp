/*
Since we want to travel an edge only once to minimize our cost, we want to find an eulerian path for the given graph. If we have x connected
components we need x-1 edges to connect them. it's interesting to see that there exists even number of nodes with odd degrees so we just
pick every pair and connect them.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))
typedef pair<int, int> ii;
typedef vector<ii> vii;

const int MAX = 1005;
int V, E, t, p[MAX], T;
bool odd[MAX], exist[MAX];
int cntOdd[MAX];

void init() {
	for (int i = 1; i <= V; ++i)
		p[i] = i;
	CLR(odd, 0);
	CLR(exist, 0);
	CLR(cntOdd, 0);
}

int findSet(int x) {
	return p[x] == x ? x : p[x] = findSet(p[x]);
}

bool sameSet(int u, int v) {
	return findSet(u) == findSet(v);
}

void unionSet(int u, int v) {
	if (sameSet(u, v))
		return;
	int s1 = findSet(u), s2 = findSet(v);
	p[s2] = s1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d%d", &V, &E, &T) == 3 && V) {
		init();
		printf("Case %d: ", ++t);
		for (int i = 0; i < E; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			odd[u] = 1 - odd[u], odd[v] = 1 - odd[v];
			exist[u] = exist[v] = 1;
			unionSet(u, v);
		}
		int out = 0, comp = 0;
		for (int i = 1; i <= V; ++i) {
			if (!exist[i])
				continue;
			if (findSet(i) == i)
				++comp;
			if (odd[i])
				++cntOdd[findSet(i)];
		}
		for (int i = 1; i <= V; ++i)
			out += max(0, cntOdd[i] / 2 - 1);
		if (comp == 0)
			puts("0");
		else
			printf("%d\n", (out + E + comp - 1) * T);
	}
}
