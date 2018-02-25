/*
If the unknown input was a movement operation then you can easily know the answer with
an equation in O(1). If, however, it was a rotation operation then you can try all possible
angles from [0,359] and simulate the input to see if you return to the original position or 
not.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)

const int MAX = 1005;

int t, n, type[MAX];
ll v[MAX];

ll toLL(string s) {
	stringstream ss;
	ss << s;
	ll ret;
	ss >> ret;
	return ret;
}
const double PI = acos(-1), EPS = 1e-2;
double toRad(int theta) {
	return theta * PI / 180;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> t;
	while (t--) {
		scanf("%d", &n);
		int q;
		for (int i = 0; i < n; ++i) {
			string s, r;
			cin >> s >> r;
			if (r == "?")
				q = i;
			else
				v[i] = toLL(r);
			if (s == "fd")
				type[i] = 1;
			else if (s == "bk")
				type[i] = 0;
			else if (s == "lt")
				type[i] = 2;
			else
				type[i] = 3;
		}
		for (int i = 0; i < n; ++i)
			if (type[i] == 3)
				v[i] = 360 - (v[i] % 360);
		if (type[q] < 2) {
			int theta = 0;
			int theta2;
			double x = 0;
			for (int i = 0; i < n; ++i) {
				if (i == q) {
					theta2 = theta;
					continue;
				}
				if (type[i] < 2)
					x += ((type[i] << 1) - 1) * v[i] * cos(toRad(theta));
				else {
					theta += v[i];
					theta %= 360;
				}
			}
			printf("%.0lf\n", fabs(-x / cos(toRad(theta2)) + 1e-8));
		} else {
			for (int a = 0; a < 360; ++a) {
				int A = a;
				v[q] = A;
				if (type[q] == 3)
					v[q] = 360 - A;
//					A = 360 - a;
				;
				double x = 0, y = 0;
				int theta = 0;
				for (int j = 0; j < n; ++j) {
					if (type[j] < 2) {
						x += ((type[j] << 1) - 1) * v[j] * cos(toRad(theta));
						y += ((type[j] << 1) - 1) * v[j] * sin(toRad(theta));
					} else {
						theta += v[j];
						theta %= 360;
					}
				}
				if (fabs(x) < EPS && fabs(y) < EPS) {
//					cout << abs(x) << ' ' << abs(y) << endl;
					printf("%d\n", A);
					break;
				}
			}
		}
	}
}
