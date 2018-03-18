/*
we can use dynamic programming of state dp[i][j] which represents the maximum acorn that can be collected from the height h to the height
i if the squirrel is on the j-th tree, then dp[i][j] = max(dp[i+1][j], max(0<=k<n) dp[i+f][k]) + acorns[i][j]
problem now is if we iterate on all possible values of k this will get TLE, so we just save the best answer for every height as we 
are calculating the dp. then the formula would be dp[i][j] = max(dp[i+1][j], bst[i+f]) + acorns[i][j]
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

const int MAX = 2005;
int T, t, h, f, tree[MAX][MAX], visID, dp[MAX][MAX], bst[MAX];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cin >> T;
	while (T--) {
		CLR(tree, 0);
		CLR(dp, 0);
		CLR(bst, 0);
		scanf("%d%d%d", &t, &h, &f);
		for (int i = 0; i < t; ++i) {
			int a;
			scanf("%d", &a);
			while (a--) {
				int p;
				scanf("%d", &p);
				++tree[i][p];
			}
		}

		for (int i = h; i; --i)
			for (int j = 0; j < t; ++j) {
				dp[i][j] = dp[i + 1][j] + tree[j][i];
				if (i + f <= h)
					dp[i][j] = max(dp[i][j], bst[i + f] + tree[j][i]);
				bst[i] = max(bst[i], dp[i][j]);
			}
		printf("%d\n", bst[1]);
	}
}
