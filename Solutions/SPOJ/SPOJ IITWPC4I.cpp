/*
An MST problem. We can use Kruskal's algorithm to solve it, except when we try to join two nodes, we check first if they are already joined
with some milkmen, if so, then we don't join them.
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

const int MAX = 1e5 + 5;
int t, n, m, milk[MAX], p[MAX];

void init() {
	for (int i = 0; i < n; ++i)
		p[i] = i;
}

struct edge {
	int u, v, c;
	edge(int u = 0, int v = 0, int c = 0) :
			u(u), v(v), c(c) {
	}
	bool operator <(const edge& e) const {
		return c < e.c;
	}
};

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
	milk[s1] |= milk[s2];
	p[s2] = s1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> t;
	while (t--) {
		set<edge> edges;
		scanf("%d%d", &n, &m);
		init();
		for (int i = 0; i < n; ++i)
			scanf("%d", &milk[i]);
		ll out = 0;
		vector<edge> edgeList;
		for (int i = 0; i < m; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			--u, --v;
			edgeList.push_back(edge(u, v, c));
		}
		sort(all(edgeList));
		for (int i = 0; i < m; ++i) {
			int u = edgeList[i].u, v = edgeList[i].v, c = edgeList[i].c;
			if (sameSet(u, v) || (milk[findSet(u)] && milk[findSet(v)]))
				continue;
			out += c;
			unionSet(u, v);
		}
		bool b = 1;
		for (int i = 0; b && i < n; ++i)
			if (!milk[findSet(i)]) {
				b = 0;
				puts("impossible");
			}
		if (b)
			printf("%lld\n", out);
	}
}
