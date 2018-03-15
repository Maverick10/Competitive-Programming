/*
Sort the input edges according to non-decreasing weights. Then we can process the edges one by one. Suppose we are now processing edge
e = (u,v,c) then we add to the answer the cost of the edge e, then consider the set that the node u belong to before adding that edge, 
say that this set is called s1 and has siz[s1] nodes in it, similarly we can say the same for the set that contain node v, then node u
needs to be connected to (siz[s2]-1) nodes with costs e.c+1, and the rest of the nodes of set s1 need to be connected to all siz[s2] nodes
with the same cost e.c, which yields (siz[s1]*siz[s2]-1)*(c+1)
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

const int MAX = 15005;
struct edge {
	int u, v, c;
	edge(int u = 0, int v = 0, int c = 0) :
			u(u), v(v), c(c) {
	}
	bool operator <(const edge& e) const {
		return c < e.c;
	}
} edgeList[MAX];
int t, n, p[MAX], siz[MAX];
ll out;

int findSet(int x) {
	return p[x] == x ? x : p[x] = findSet(p[x]);
}

void unionSet(int u, int v, int c) {
	int s1 = findSet(u), s2 = findSet(v);
	out += (c + 1ll) * (siz[s1] * siz[s2] - 1ll);
	siz[s1] += siz[s2];
	p[s2] = s1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> t;
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			p[i] = i, siz[i] = 1;
		out = 0;
		for (int i = 0; i < n - 1; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			--u, --v;
			edgeList[i] = edge(u, v, c);
		}
		sort(edgeList, edgeList + n - 1);

		for (int i = 0; i < n - 1; ++i) {
			edge e = edgeList[i];
			out += e.c;
			unionSet(e.u, e.v, e.c);
		}
		printf("%lld\n", out);
	}
}
