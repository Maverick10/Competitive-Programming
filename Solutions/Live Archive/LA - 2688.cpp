/*
Used solution explained in this tutorial
https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/LiveArchive/LiveArchive_2688.txt
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

double A, B, C, D, E;
double b, y, a;

void init() {
	if (A > B)
		swap(A, B);
	if (A > C)
		swap(A, C);
	if (B > C)
		swap(B, C);
	if (D > E)
		swap(D, E);
}

bool check() {
	if (A <= D && B <= E)
		return 1;
	if (D < A)
		return 0;
	C = hypot(A, B);
	b = asin(D / C);
	y = asin(A / C);
	a = b - y;
	double l1 = B * cos(a);
	double l2 = A * sin(a);
	return l1 + l2 <= E;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%lf%lf%lf%lf%lf", &A, &B, &C, &D, &E) == 5) {
		init();
		puts(check() ? "YES" : "NO");
	}
}
