/*
Let's ask ourselves a question: when do we consider an edge to be a shortest-path edge? well, if dist[u] is the shortest path from a single
source to the node u, and if we have an edge e = (u,v,c) which means that there's an edge from node u to node v with cost c, then edge e
is a shortest path edge iff dist[u] + e.c == dist[v]. That's the key to solving this problem.
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

const int MAX = 505, oo = 1e9;
int n, m, s[2], sp[2][MAX], sp2[MAX];
vii adjList[2][MAX];

void dijkstra(int src, int idx) {
	for (int i = 0; i < MAX; ++i)
		sp[idx][i] = oo;
	sp[idx][src] = 0;
	priority_queue<ii, vii, greater<ii> > q;
	q.push( { 0, src });
	while (sz(q)) {
		int u = q.top().second;
		int c = q.top().first;
		q.pop();
		for (auto &v : adjList[idx][u])
			if (v.second + c < sp[idx][v.first]) {
				sp[idx][v.first] = v.second + c;
				q.push( { sp[idx][v.first], v.first });
			}
	}
}

int dijkstra2(int src) {
	for (int i = 0; i < MAX; ++i)
		sp2[i] = oo;
	sp2[src] = 0;
	priority_queue<ii, vii, greater<ii> > q;
	q.push( { 0, src });
	while (sz(q)) {
		int u = q.top().second;
		int c = q.top().first;
		q.pop();
		for (auto &v : adjList[0][u]) {
			if (v.second + sp[0][u] == sp[0][v.first]
					&& sp[0][v.first] + sp[1][v.first] == sp[0][s[1]])
				continue;
			if (c + v.second < sp2[v.first]) {
				sp2[v.first] = c + v.second;
				q.push( { sp2[v.first], v.first });
			}
		}
	}
	return sp2[s[1]];
}

void init() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < MAX; ++j)
			adjList[i][j].clear();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%d%d%d%d", &n, &m, &s[0], &s[1]) == 4 && n) {
		init();
		while (m--) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			adjList[0][u].push_back( { v, c });
			adjList[1][v].push_back( { u, c });
		}
		for (int i = 0; i < 2; ++i)
			dijkstra(s[i], i);
		if (sp[0][s[1]] == oo)
			puts("-1");
		else {
			int out = dijkstra2(s[0]);
			printf("%d\n", out == oo ? -1 : out);
		}
	}
}
