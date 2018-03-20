/*
This code gives WA.
Input:
10.2 1.5 10.9 6.6 9.6

My Output:
NO

Correct Output:
YES

Problem is I can't solve this case even by hand. so I can't figure out if I just have a bug in my code or if the idea is completely wrong.
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

#define EPS 1e-15

double a[3], d, e;

int doubleComp(double x, double y) {
	if (fabs(x - y) < EPS)
		return 0;
	return ((x > y) << 1) - 1;
}

bool canFit(double A, double B, double C, double D) {
	if (doubleComp(A, C) <= 0 && doubleComp(B, D) <= 0)
		return 1;
	double diag = hypot(C, D);
	double d = B / 2;
	double x = d * D / C;
	double x2 = d * C / D;
	if (doubleComp(2 * max(x, x2), diag) == 1)
		return 0;
	if (doubleComp(x, x2) >= 0) {
		double y = hypot(x, d);
		if (doubleComp(y, D) == 1)
			return 0;
		return doubleComp(A, diag - 2 * x) <= 0;
	} else {
		double z = hypot(x2, d);
		if (doubleComp(z, C) == 1)
			return 0;
		return doubleComp(A, diag - 2 * x2) <= 0;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%lf%lf%lf%lf%lf", &a[0], &a[1], &a[2], &d, &e) == 5) {
		bool b = 0;
//		if (doubleComp(d, e) == 1)
//			swap(d, e);
		for (int i = 0; !b && i < 3; ++i)
			for (int j = 0; j < 3; ++j) {
				if (i == j)
					continue;
				if (canFit(a[i], a[j], d, e) || canFit(a[i], a[j], e, d)) {
					b = 1;
					break;
				}
			}
		puts(b ? "YES" : "NO");
	}
}
