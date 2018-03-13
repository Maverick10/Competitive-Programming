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

const int MAX = 1005;
int n, vis[MAX], visID;
ii p[MAX];

int getDist(int i, int j) {
	int x = p[i].first - p[j].first, y = p[i].second - p[j].second;
	return x * x + y * y;
}

void dfs(int u) {
	vis[u] = visID;
	int idx[2], dist[2] = { 1000000, 1000000 };
	for (int i = 0; i < n; ++i)
		if (i != u) {
			int d = getDist(i, u);
			if (d < dist[0]) {
				swap(dist[0], dist[1]);
				swap(idx[0], idx[1]);
				dist[0] = d;
				idx[0] = i;
			} else if (d < dist[1]) {
				dist[1] = d;
				idx[1] = i;
			}
		}
	for (int i = 0; i < 2; ++i)
		if (vis[idx[i]] != visID)
			dfs(idx[i]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%d", &n) == 1 && n) {
		int x, y;
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].first, &p[i].second);
		x = p[0].first, y = p[0].second;
		if (n < 3) {
			puts("All stations are reachable.");
			continue;
		}
		sort(p, p + n);
		++visID;
		int idx;
		for (int i = 0; i < n; ++i)
			if (p[i].first == x && p[i].second == y) {
				idx = i;
				break;
			}
		dfs(idx);
		bool b = 1;
		for (int i = 0; i < n; ++i)
			if (vis[i] != visID) {
				b = 0;
				puts("There are stations that are unreachable.");
				break;
			}
		if (b)
			puts("All stations are reachable.");
	}
}
