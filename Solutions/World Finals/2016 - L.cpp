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

const int MAX = 1e6 + 5;
int n;
int a[MAX], b[MAX], sizInc, sizDec;
ii Inc[MAX], Dec[MAX];

bool check(ll fs) {
	for (int i = 0; i < sizInc; ++i)
		if (fs < Inc[i].first)
			return 0;
		else
			fs += Inc[i].second - Inc[i].first;
	for (int i = 0; i < sizDec; ++i) {
		if (fs < Dec[i].first)
			return 0;
		fs += Dec[i].second - Dec[i].first;
	}
	return fs >= 0;
}

bool comp(ii f, ii s) {
	return f.second > s.second;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i], &b[i]);
		if (a[i] <= b[i])
			Inc[sizInc++] = ii(a[i], b[i]);
		else
			Dec[sizDec++] = ii(a[i], b[i]);
	}
	sort(Inc, Inc + sizInc);
	sort(Dec, Dec + sizDec, comp);
	ll l = 1, r = 1e16;
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%lld\n", l);
}
