/*
we can use dynamic programming with bitmasks, where dp[h][prevMsk][curMsk] is the number of
valid configurations that can be made when we are trying to fill the h-th level, the cells 
occupied by blocks in the previous level can be represented by 1's in prevMsk, and the cells 
occupied by blocks in current level can be represented by 1's in curMsk.

Time Complexity: O(h*w * 2^(h+w))
Memory Complexity: O(h * 2^(h+w))
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

const int MOD = 1e9 + 7;

int memo[10][1 << 10][1 << 10];
int H, W;

int add(int x, int y) {
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}

int solve(int h, int prevMsk, int curMsk) {
	if (h == H)
		return 1;
	int &ret = memo[h][prevMsk][curMsk];
	if (~ret)
		return ret;
	ret = solve(h + 1, curMsk, 0);
	int s = 0;
	for (int i = 0; i < W; ++i)
		if ((curMsk >> i) & 1)
			s = i + 1;
	for (int i = s; i < W; ++i) {
		if (!((curMsk >> i) & 1)) {
			//1*1*1
			if ((prevMsk >> i) & 1)
				ret = add(ret, solve(h, prevMsk, curMsk | (1 << i)));
			//1*1*2
			if (i < W - 1 && ((curMsk >> i) & 3) == 0
					&& ((prevMsk >> i) & 3) == 3)
				ret = add(ret, solve(h, prevMsk, curMsk | (3 << i)));
			//1*1*3
			if (i < W - 2 && ((curMsk >> i) & 7) == 0 && ((prevMsk >> i) & 1)
					&& ((prevMsk >> (i + 2)) & 1))
				ret = add(ret, solve(h, prevMsk, curMsk | (7 << i)));
		}
	}
	return ret;
}

struct SmallBricks31 {
	int countWays(int w, int h) {
		CLR(memo, -1);
		H = h, W = w;
		cout << solve(0, (1 << w) - 1, 0);
		return solve(0, (1 << w) - 1, 0);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif

}
