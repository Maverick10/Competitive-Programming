/*
we can use dynamic programming using bitmasks of state dp[msk][curScare], the problem is 
curScare can increase to the point that the solution will not fit in memory limit.
but we can realize that if we choose x1,x2,...,xm as the movies we currently watched,
then curScare = 74-sum(length[x[i]])+47*m.

Time Complexity : O(n * 2^n)
Memory Complexity: O(2^n)
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

int n, memo[1 << 20], mx;
vi l, s, out;

int solve(int msk, int pc) {
	if (pc == n)
		return 0;
	int &ret = memo[msk];
	if (~ret)
		return ret;
	ret = 0;
	int scare = 74;
	for (int i = 0; i < n; ++i)
		if ((msk >> i) & 1)
			scare += 47 - l[i];
	for (int i = 0; i < n; ++i)
		if (!((msk >> i) & 1) && scare >= s[i] && scare + 47 >= l[i])
			ret = max(ret, solve(msk | (1 << i), pc + 1) + 1);
	return ret;
}

void buildPath(int msk, int pc) {
	if (pc == n)
		return;

	int ret = memo[msk], scare = 74;
	for (int i = 0; i < n; ++i)
		if ((msk >> i) & 1)
			scare += 47 - l[i];
	for (int i = 0; i < n; ++i)
		if (!((msk >> i) & 1) && scare >= s[i] && scare + 47 >= l[i]) {
			if (solve(msk | (1 << i), pc + 1) + 1 == ret) {
				buildPath(msk | (1 << i), pc + 1);
				out.push_back(i);
				break;
			}
		}
}

bool Find(int i) {
	return find(all(out), i) != out.end();
}

struct TheMoviesLevelTwoDivOne {
	vector<int> find(vector<int> length, vector<int> scary) {
		l = length, s = scary, n = sz(length);
		CLR(memo, -1);
		mx = solve(0, 0);
		cout << mx << endl;
		buildPath(0, 0);
		for (int i = 0; i < n; ++i)
			if (!Find(i))
				out.push_back(i);
//		for (int i = 0; i < n; ++i)
//			cout << out[i] << endl;
		return out;
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	TheMoviesLevelTwoDivOne t;
	t.find( { 100, 50 }, { 1, 1 });
}
