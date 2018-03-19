/*
let's first assume that we don't remove any magnet, then the answer will be the rectangle that passes through the centers of the extreme
magnets (whose centers have the maximum x, minimum x, maximum y or minimum y). if we want to remove any magnet, we should remove one that
lies on the boundary of the refrigerator, thus making the boundaries move toward the center of the rectangle, which will minimize the area.
since k <= 10 we can brute force on the vertical boundaries to see which magnets to remove, and for every possible subset we brute force
on the horizontal boundaries to see which magnets to remove from there as well, and every time we minimize the area that we get.

Complexity: O(k* 2^k + nlogn)
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
int n, k, sizX, sizY, used[MAX], visID;
map<ii, vi> x, y;
pair<ii, vi> xVec[MAX], yVec[MAX];

ii getY(int msk, int i) {
	int up = PC(msk);
	int down = i - up;
	int d = 0;
	int cnt = 0;
	while (cnt < down) {
		bool c = 0;
		for (auto a : yVec[d].second) {
			if (used[a] == visID) {
				if (a == yVec[d].second.back())
					c = 1;
				continue;
			}
			++cnt;
			used[a] = visID;
			if (a == yVec[d].second.back())
				c = 1;
			if (cnt == down)
				break;
		}
		if (c)
			++d;
	}

	int u = sizY - 1;
	cnt = 0;
	while (cnt < up) {
		bool c = 0;
		for (auto a : yVec[u].second) {
			if (used[a] == visID) {
				if (a == yVec[u].second.back())
					c = 1;
				continue;
			}
			++cnt;
			used[a] = visID;
			if (a == yVec[u].second.back())
				c = 1;
			if (cnt == up)
				break;
		}
		if (c)
			--u;
	}
	return {u,d};
}

void fix(int& f, int& s, pair<ii, vi>* vec) {
	bool b = 1;
	while (b) {
		for (auto a : vec[f].second)
			if (used[a] != visID) {
				b = 0;
				break;
			}
		if (b)
			++f;
	}
	b = 1;
	while (b) {
		for (auto a : vec[s].second)
			if (used[a] != visID) {
				b = 0;
				break;
			}
		if (b)
			--s;
	}
}

ll calc(ii X1, ii X2, ii Y1, ii Y2) {
	return (max(1, X2.first - X1.first + (X2.second ^ X1.second))) * 1ll
			* max(1, (Y2.first - Y1.first + (Y2.second ^ Y1.second)));
}

void mapToVec() {
	int i = 0;
	for (auto it : x) {
		xVec[i].first = it.first;
		for (auto a : it.second)
			xVec[i].second.push_back(a);
		i++;
	}
	sizX = i;
	i = 0;
	for (auto it : y) {
		yVec[i].first = it.first;
		for (auto a : it.second)
			yVec[i].second.push_back(a);
		i++;
	}
	sizY = i;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		int X, Y, X2, Y2;
		scanf("%d%d%d%d", &X, &Y, &X2, &Y2);
		x[ { (X + X2) / 2, ((X ^ X2) & 1) }].push_back(i);
		y[ { (Y + Y2) / 2, ((Y ^ Y2) & 1) }].push_back(i);
	}
	mapToVec();
	ll out = 5e18;
	int counter = 0;
	for (int i = 0; i <= k; ++i) {
		for (int j = 0; j < (1 << i); ++j) {
			for (int m = 0; m < (1 << (k - i)); ++m) {
				visID++;
//				printf("%d\n", counter++);
				int right = PC(j);
				int left = i - right;
				int l = 0;
				int cnt = 0;
				while (cnt < left) {
					bool c = 0;
					for (auto a : xVec[l].second) {
						used[a] = visID;
						++cnt;
						if (a == xVec[l].second.back())
							c = 1;
						if (cnt == left)
							break;
					}
					if (c)
						++l;
				}
				int r = sizX - 1;
				cnt = 0;
				while (cnt < right) {
					bool c = 0;
					for (auto a : xVec[r].second) {
						used[a] = visID;
						++cnt;
						if (a == xVec[r].second.back())
							c = 1;
						if (cnt == right)
							break;
					}
					if (c)
						--r;
				}

				ii ret = getY(m, k - i);
				int u = ret.first, d = ret.second;
				fix(l, r, xVec);
				fix(d, u, yVec);
				out = min(out,
						calc(xVec[l].first, xVec[r].first, yVec[d].first,
								yVec[u].first));

			}
		}
	}
	printf("%lld\n", out);
}
