/*
Since numbers don't exceed 10^6, maximum number of different prime divisors will not exceed
7. GCD can be calculated by multiplying the minimum of the two powers of all different primes
that divide the two numbers. LCM can be calculated the same way but finding maximum instead
of minimum. So for a given number and a given edge, we can try all combinations which are no 
more than 2^7. We can do this for every connected component and checking the validity every
time we try a new combination until we get a valid one.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()

const int MAX = 105;

struct edge {
	int v, g, l;
	edge(int v = 0, int g = 0, int l = 0) :
			v(v), g(g), l(l) {
	}
};

int par[MAX];

int findSet(int x) {
	return x == par[x] ? x : par[x] = findSet(par[x]);
}

bool sameSet(int u, int v) {
	return findSet(u) == findSet(v);
}

void unionSet(int u, int v) {
	if (sameSet(u, v))
		return;
	int s1 = findSet(u), s2 = findSet(v);
	par[s2] = s1;
}

vector<edge> adjList[MAX];
int n, m, visC[MAX], visID, num[MAX], vis[MAX];
vi st[MAX];
set<int> s;
map<int, int> mp[2];

void fact(int x, int i) {
	int j = 2;
	for (; j * j <= x; ++j)
		while (x % j == 0)
			mp[i][j]++, x /= j, s.insert(j);
	if (x > 1)
		s.insert(x), mp[i][x]++;
}

void f(int u, int g, int l) {
	s.clear();
	mp[0].clear();
	mp[1].clear();
	fact(g, 0);
	fact(l, 1);
}

int pw(int x, int p) {
	int ret = 1;
	while (p) {
		if (p & 1)
			ret *= x;
		x *= x;
		p >>= 1;
	}
	return ret;
}

int findNum(int msk) {
	int i = 0;
	int ret = 1;
	for (auto x : s) {
		ret *= pw(x, mp[(msk >> i) & 1][x]);
		i++;
	}
	return ret;
}

bool dfs(int u) {
	vis[u] = visID;
	bool ret = 1;
	for (auto &e : adjList[u]) {
		int v = e.v, g = e.g, l = e.l;
		if (vis[v] != visID) {
			if ((l * 1ll * g) % num[u])
				return 0;
			num[v] = l * 1ll * g / num[u];
			ret &= dfs(v);
		}
	}
	return ret;
}

int lcm(int x, int y) {
	return x * 1ll * y / __gcd(x, y);
}

bool verify(int x) {
	for (auto &u : st[x])
		for (auto &e : adjList[u]) {
			int v = e.v, g = e.g, l = e.l;
			if (__gcd(num[u], num[v]) != g || lcm(num[u], num[v]) != l)
				return 0;
		}
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		par[i] = i;
	while (m--) {
		int u, v, g, l;
		cin >> u >> v >> g >> l;
		--u, --v;
		adjList[u].push_back( { v, g, l });
		adjList[v].push_back( { u, g, l });
		unionSet(u, v);
		if (l % g)
			return puts("NO");
	}
	for (int i = 0; i < n; ++i)
		st[findSet(i)].push_back(i);
	for (int i = 0; i < n; ++i)
		if (!visC[findSet(i)]) {
			visC[findSet(i)] = 1;
			if (!sz(adjList[i])) {
				num[i] = 1;
				continue;
			}
			bool b = 0;
			f(i, adjList[i][0].g, adjList[i][0].l);
			for (int j = 0; !b && j < (1 << sz(s)); ++j) {
				++visID;
				num[i] = findNum(j);
				if (!dfs(i))
					continue;
				b |= verify(findSet(i));
			}
			if (!b)
				return puts("NO");
		}
	puts("YES");
	for (int i = 0; i < n; ++i)
		printf("%d ", num[i]);
}