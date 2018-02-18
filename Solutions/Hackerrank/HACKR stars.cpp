/*
It's always possible to divide the plane into two parts where every point belongs to exactly
one of them. Since n is relatively small (n<=100) we can try every pair of points abd consider 
the two points to belong to different parts, and then using cross product we can determine which side
every other point is on.
*/

#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define CLR(a,v) memset(a,v,sizeof(a))
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()
typedef long long ll;
typedef pair<int, int> ii;

const int MAX = 105;

int n, x[MAX], y[MAX], w[MAX];

ll cross(int i, int j, int k) {
	int X = x[j] - x[i], Y = y[j] - y[i];
	int X2 = x[k] - x[i], Y2 = y[k] - y[i];
	return X2 * 1ll * Y - Y2 * 1ll * X;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i] >> w[i];
	int diff = 1e9, out;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			if (i == j)
				continue;
			int a = 0, b = 0;
			for (int k = 0; k < n; ++k) {
				ll v = cross(i, j, k);
				if (v > 0)
					a += w[k];
				else
					b += w[k];
			}
			if (abs(a - b) < diff)
				diff = abs(a - b), out = min(a, b);
			else if (abs(a - b) == diff)
				out = max(out, min(a, b));
		}
	cout << out;
}
