/*
Imagine the grid as a graph, nodes (i,j) represent the nodes, edges connect nodes that
can visit each other directly, and weight of each edge is the absolute difference between
the numbers on each node. Then the answer to our problem is to find the maximum spanning
tree of the graph.
*/
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define CLR(a,v) memset(a,v,sizeof(a))
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()

const int MAX = 55;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

struct edge {
	int u, v, w;
	edge(int u = 0, int v = 0, int w = 0) :
			u(u), v(v), w(w) {
	}
	bool operator <(const edge& e) const {
		return w > e.w;
	}
};

int par[MAX * MAX], n, m;
vector<edge> edgeList;

bool valid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int num(int i, int j) {
	return i * m + j;
}

int C(char a) {
	if (a >= '0' && a <= '9')
		return a - '0';
	if (a >= 'a' && a <= 'z')
		return a - 'a' + 10;
	return a - 'A' + 36;
}

int weight(char a, char b) {
	return abs(C(a) - C(b));
}

int findSet(int x) {
	return par[x] == x ? x : par[x] = findSet(par[x]);
}

bool sameSet(int u, int v) {
	return findSet(u) == findSet(v);
}

void unionSet(int u, int v) {
	int s1 = findSet(u), s2 = findSet(v);
	par[s2] = s1;
}

class ActivateGame {
public:
	int findMaxScore(vector<string> grid) {
		n = sz(grid), m = sz(grid[0]);
		for (int i = 0; i < n * m; ++i)
			par[i] = i;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				for (int k = 0; k < 4; ++k) {
					int ni = i + dx[k], nj = j + dy[k];
					if (valid(ni, nj))
						edgeList.push_back(
								{ num(i, j), num(ni, nj), weight(grid[i][j],
										grid[ni][nj]) });
				}
		for (auto e : edgeList)
			cout << e.u << ' ' << e.v << ' ' << e.w << endl;
		sort(all(edgeList));
		int ret = 0;
		for (auto &e : edgeList) {
			int u = e.u, v = e.v, w = e.w;
			if (sameSet(u, v))
				continue;
			ret += w;
			unionSet(u, v);
		}
		return ret;
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	vector<string> v = { "05", "aB" };
	ActivateGame a;
	cout << a.findMaxScore(v);
}
