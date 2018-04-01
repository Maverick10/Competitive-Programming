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

const int MAX = 5005, oo = 1e9;
const ll OO = 1e18;
int n, b, s, r, dist[2][MAX], c[MAX];
vii adjList[2][MAX];
ll memo[MAX][MAX], preSum[MAX];

void dijkstra(int src, int idx) {
	for (int i = 1; i <= n; ++i)
		dist[idx][i] = oo;

	dist[idx][src] = 0;
	priority_queue<ii, vii, greater<ii> > q;
	q.push( { 0, src });
	while (sz(q)) {
		int u = q.top().second;
		int c = q.top().first;
		q.pop();
		for (auto &v : adjList[idx][u])
			if (c + v.second < dist[idx][v.first]) {
				dist[idx][v.first] = c + v.second;
				q.push( { dist[idx][v.first], v.first });
			}
	}
}

ll cost(int l, int r) {
	return preSum[r] - preSum[l - 1];
}

ll solve(int idx, int rs) {
	if (!idx)
		return !rs ? 0 : OO;
	if (!rs)
		return OO;
	ll &ret = memo[idx][rs];
	if (~ret)
		return ret;
	ret = OO;
	for (int k = 1; k <= idx / rs; ++k)
		ret = min(ret,
				solve(idx - k, rs - 1) + (k - 1) * cost(idx - k + 1, idx));
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n >> b >> s >> r;
	while (r--) {
		int u, v, l;
		scanf("%d%d%d", &u, &v, &l);
		adjList[0][u].push_back( { v, l });
		adjList[1][v].push_back( { u, l });
	}

	for (int i = 0; i < 2; ++i)
		dijkstra(b + 1, i);

	for (int i = 1; i <= b; ++i) {
		c[i] = dist[0][i] + dist[1][i];
//		cout << c[i] << endl;
	}
	sort(c + 1, c + b + 1);

	for (int i = 1; i <= b; ++i)
		preSum[i] = preSum[i - 1] + c[i];

	CLR(memo, -1);
	printf("%lld", solve(b, s));
}
