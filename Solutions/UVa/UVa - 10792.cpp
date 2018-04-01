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

int n, r, d, h1;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> r >> d >> h1;
		double theta = asin((r - d) * 1.0 / r);
		double ab = 2 * r * cos(theta);
		double gamma = asin((r - h1) * 1.0 / r);
		double alpha = gamma - theta;
		printf("Case %d: %.4lf\n", i, ab * sin(alpha) + h1);
	}
}
