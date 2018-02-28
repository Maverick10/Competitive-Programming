#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))

const int oo = 1e9;
int n, memo[1 << 15][16][16];
vi X, Y;

int cross(int x, int y, int x2, int y2) {
	return x * y2 - y * x2;
}

int area(int a, int b, int c) {
	return abs(cross(X[b] - X[a], Y[b] - Y[a], X[c] - X[a], Y[c] - Y[a]));
}

int solve(int msk, int a, int b, int pc) {
	if (pc == n && a == n && b == n)
		return 0;
	int &ret = memo[msk][a][b];
	if (~ret)
		return ret;
	ret = oo;
	for (int i = 0; i < n; ++i) {
		if (i == a || i == b)
			continue;
		if (!((msk >> i) & 1)) {
			if (a == n)
				ret = min(ret, solve(msk | (1 << i), i, b, pc + 1));
			else if (b == n)
				ret = min(ret, solve(msk | (1 << i), a, i, pc + 1));
			else
				ret = min(ret,
						solve(msk | (1 << i), n, n, pc + 1) + area(a, b, i));
		} else {
			if (a == n)
				continue;
			if (b == n)
				ret = min(ret, solve(msk, a, i, pc));
			else
				ret = min(ret, solve(msk, n, n, pc) + area(a, b, i));
		}
	}
	return ret;
}

struct PolygonCover {
	double getArea(vector<int> x, vector<int> y) {
		n = sz(x);
		X = x, Y = y;
		CLR(memo, -1);
		int ret = solve(0, n, n, 0);
		cout << ret << endl;
		return (ret >> 1) + ((ret & 1) ? 0.5 : 0.0);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	PolygonCover p;
	cout << p.getArea( { 0, 0, 1, 1 }, { 0, 1, 0, 1 });
}
