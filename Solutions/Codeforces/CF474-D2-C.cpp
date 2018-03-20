/*
solution is straight-forward, you just have to implement what's written in the statement.
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

typedef complex<double> point;
#define polar(r,t) ((r)*exp(point(0,(t))))
#define rotateabout(v,t,a)  (rotate(vec(a,v),t)+(a))
#define rotate(v,t) (polar(v,t))
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define EPS 1e-9

int n, x[4], y[4], a[4], b[4];
const double PI = acos(-1);

bool samePts(point p, point q) {
	return fabs(p.X - q.X) < EPS && fabs(p.Y - q.Y) < EPS;
}

double getDist(point p, point q) {
	return hypot(p.X - q.X, p.Y - q.Y);
}

bool same(double s, double t) {
	return fabs(s - t) < EPS;
}

bool square(point p0, point p1, point p2, point p3) {
	if (samePts(p0, p1) || samePts(p0, p2) || samePts(p0, p3) || samePts(p1, p2)
			|| samePts(p1, p3) || samePts(p2, p3))
		return 0;
	double s = getDist(p0, p1);
	double s2 = getDist(p0, p3);
	double s3 = getDist(p1, p2);
	double s4 = getDist(p2, p3);
	double d = getDist(p0, p2);
	return same(s, s2) && same(s, s3) && same(s, s4) && same(getDist(p1, p3), d);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j)
			scanf("%d%d%d%d", &x[j], &y[j], &a[j], &b[j]);
		int out = 100;
		for (int A = 0; A < 4; ++A)
			for (int B = 0; B < 4; ++B)
				for (int C = 0; C < 4; ++C)
					for (int D = 0; D < 4; ++D) {
						point p0 = rotateabout(point(x[0], y[0]), PI * A / 2,
								point(a[0], b[0]));
						point p1 = rotateabout(point(x[1], y[1]), PI * B / 2,
								point(a[1], b[1]));
						point p2 = rotateabout(point(x[2], y[2]), PI * C / 2,
								point(a[2], b[2]));
						point p3 = rotateabout(point(x[3], y[3]), PI * D / 2,
								point(a[3], b[3]));

						if (square(p0, p1, p2, p3) || square(p0, p2, p1, p3)
								|| square(p0, p1, p3, p2)) {
							cnt++;
							out = min(out, A + B + C + D);
//							if (out == 1)
//								cout << A << ' ' << B << ' ' << C << ' ' << D
//										<< endl;
						}
					}
		printf("%d\n", out == 100 ? -1 : out);
	}
}
