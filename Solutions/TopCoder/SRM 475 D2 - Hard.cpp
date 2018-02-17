#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define CLR(a,v) memset(a,v,sizeof(a))
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()
typedef long long ll;
typedef pair<int, int> ii;

const int MAX = 55;
const ll oo = 1ll << 50;

vector<ll> a, b, adjList[MAX * 3], ao, bo, ae, be;
ll dist[MAX * 3], n, LJ;

bool can(int u, int v, int odd) {
	if (!odd) {
		ll si = a[u], ei = b[u];
		if (si % 2)
			si++;
		if (ei % 2)
			ei--;
		ll sj = a[v], ej = b[v];
		if (sj % 2 == 0)
			sj++;
		if (ej % 2 == 0)
			ej--;
		if (si > ei || sj > ej)
			return 0;
		return max(si + LJ, sj) <= min(ei + LJ, ej)
				|| max(si, sj + LJ) <= min(ei, ej + LJ);
	} else {
		ll si = a[u], ei = b[u];
		if (si % 2 == 0)
			si++;
		if (ei % 2 == 0)
			ei--;
		ll sj = a[v], ej = b[v];
		if (sj % 2)
			sj++;
		if (ej % 2)
			ej--;
		if (si > ei || sj > ej)
			return 0;
		return max(si + LJ, sj) <= min(ei + LJ, ej)
				|| max(si, sj + LJ) <= min(ei, ej + LJ);
	}
}

void bfs() {
	for (int i = 0; i < MAX * 3; ++i)
		dist[i] = oo;
	dist[0] = 0;
	queue<ii> q;
	q.push( { 0, 0 });
	while (!q.empty()) {
		int u = q.front().first, odd = q.front().second;
		q.pop();
		for (int v = 0; v < n; ++v)
			if (can(u / 2, v, odd) && dist[v * 2 + 1 - odd] > dist[u] + 1)
				dist[v * 2 + 1 - odd] = dist[u] + 1, q.push(
						{ v * 2 + 1 - odd, 1 - odd });
	}
}

class RabbitJumping {
public:
	int getMinimum(vector<int> h, int largeJump) {
		vector<ll> holes;
		for (auto x : h)
			holes.push_back(x);
		LJ = largeJump;
		if (!(largeJump & 1))
			return -1;
		a.push_back(-oo), b.push_back(holes[0] - 1);
		holes.push_back(oo);
		for (int i = 1; i < sz(holes); i += 2)
			if (holes[i] + 1 <= holes[i + 1] - 1)
				a.push_back(holes[i] + 1), b.push_back(holes[i + 1] - 1);

		n = sz(a);
		bfs();
		return dist[sz(a) * 2 - 1] == oo ? -1 : dist[sz(a) * 2 - 1];
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	RabbitJumping r;
	cout << r.getMinimum( { 101557142, 210995878, 245344736, 257981537,
			314968406, 363946193, 424279117, 435779304, 441820162, 498117144,
			507089544, 553226276, 612496883, 675096026, 730940846, 819627580,
			861535050, 862716271 }, 123866101);
}
