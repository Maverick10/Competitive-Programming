/*
sssp problem. can be solved by dijkstra's algorithm. cost of an edge (u,v) can be determined by calculating the euclidean distance between
nodes u and v, and by calculating the angle between the vectors (par[u],u) and (u,v), this can be calculated using dot product.
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
int t, n, m, s, f, x[MAX], y[MAX], par[MAX];
double k, dist[MAX];
vi adjList[MAX];

void init() {
	CLR(par, -1);
	for (int i = 0; i < MAX; ++i)
		dist[i] = 1e18, adjList[i].clear();
}

double len(int i, int j) {
	return hypot(x[i] - x[j], y[i] - y[j]);
}

double dot(int a, int b, int c, int d) {
	int X = x[b] - x[a], Y = y[b] - y[a];
	int X2 = x[d] - x[c], Y2 = y[d] - y[c];
	return X * X2 + Y * Y2;
}
const double PI = acos(-1);
double toDeg(double x) {
	return x * 180 / PI;
}

double calcAngle(int i, int j) {
	if (par[i] == -1)
		return 0;
	double d = dot(par[i], i, i, j);
	double n1 = len(par[i], i);
	double n2 = len(i, j);
	return toDeg(acos(d / n1 / n2)) * k;
}

void dijkstra() {
	dist[s] = 0;
	priority_queue<pair<double, int>, vector<pair<double, int> >,
			greater<pair<double, int> > > q;
	q.push( { 0, s });
	while (sz(q)) {
		int u = q.top().second;
		double c = q.top().first;
		q.pop();
		for (auto &v : adjList[u]) {
			double nc = len(u, v) + calcAngle(u, v);
			if (c + nc < dist[v]) {
				dist[v] = c + nc, par[v] = u;
				q.push( { dist[v], v });
			}
		}
	}
}

void dfs(int u) {
	if (u == -1)
		return;
	dfs(par[u]);
	if (u != s)
		printf(" ");
	printf("%d", u);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cin >> t;
	while (t--) {
		init();
		scanf("%d%d%d%d%lf", &n, &m, &s, &f, &k);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &x[i], &y[i]);
		while (m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			adjList[u].push_back(v);
		}
		dijkstra();
		if (dist[f] < 1e17) {
			printf("%.6lf\n", dist[f]);
			dfs(f);
			puts("");
		} else
			puts("Impossible");
		if (t)
			puts("");
	}
}
