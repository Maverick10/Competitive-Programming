/*
we can use dynamic programming of state {idx, msk} which represents the maximum size of subset
that can be chosen where all numbers are relatively prime, starting from index idx to the 
last index. Since numbers are not greater than 100 therefore the number different prime 
divisors can be no greater than 25, then msk represents the bitmask of the prime divisors
that we added to the current subset, so when choosing a number to add to the subset we take
care that this number is not divisible by any of the currently used prime divisors (those
indicated by msk). Problem is memory complexity will now be O(2^25 * n) which will not fit
but we can easily realize that we don't need to keep track of any prime divisor greater than
50, let a prime number greater than 50 be a divisor of a number x, since x is not greater
than 100, this implies that x is a prime number and is in fact that prime divisor we are talking
about. so we will only need to keep track of the prime numbers less than 50. and they are
15 of them.

Memory complexity: O(2^15 * n)
Time complexity: O(2^15 * n * 15)
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

const int MAX = 55;
int p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
int memo[MAX][1 << 15], n;
vi s;

int solve(int idx, int msk) {
	if (idx == n)
		return 0;
	int &ret = memo[idx][msk];
	if (~ret)
		return ret;
	ret = solve(idx + 1, msk);
	int MSK = 0;
	for (int i = 0; i < 15; ++i)
		if (s[idx] % p[i] == 0)
			MSK |= (1 << i);
	if (MSK & msk)
		return ret;
	return ret = max(ret, solve(idx + 1, msk | MSK) + 1);
}

struct RelativelyPrimeSubset {
	int findSize(vector<int> S) {
		s = S;
		n = sz(s);
		CLR(memo, -1);
		return solve(0, 0);
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif

}
