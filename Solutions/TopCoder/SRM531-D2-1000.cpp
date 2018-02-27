/*
Let's consider that we have multiple connected components in our graph. What we want to do
is actually choose the heaviest edges in a component and keep them in order to make that
component a tree. It's actually quite similar to finding the MST of a graph. Once we have
done this for all components, we end up with a forest that we want to make it one single tree
so we choose the lightest edges to connect between different trees.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()

typedef complex<long double> point;
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define length(v) ((long double)hypot((v).Y,(v).X))
#define angle(v) (atan2((v).Y,(v).X))

const int MAX = 5005;
const long double EPS = 1e-9, PI = acos(-1);

int n, m, x[MAX], y[MAX];
int x2, y2;

bool pointOnLine(const point& a, const point& b, const point& p) {
	// degenerate case: line is a point
	return fabs(cross(vec(a, b), vec(a, p))) < EPS;
}

bool pointOnRay(const point& a, const point& b, const point& p) {
	//IMP NOTE: a,b,p must be collinear
	return dot(vec(a, p), vec(a, b)) > -EPS;
}

bool pointOnSegment(const point& a, const point& b, const point& p) {
	if (!pointOnLine(a, b, p))
		return 0;
	return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

void fix(long double &ret) {
	if (ret < 0)
		ret = 2 * PI + ret;
}

long double findAngle(point a, point b, point c, point d) {
	long double theta1 = angle(vec(c,d));
	long double theta2 = angle(vec(a,b));
	fix(theta1), fix(theta2);
	long double cr = cross(vec(a,b), vec(c,d));
	int sign = cr > 0 ? 1 : -1;
	return sign * min(2 * PI - fabs(theta1 - theta2), fabs(theta1 - theta2));
}

int doubleCompare(long double _x, long double _y) {
	if (fabs(_x - _y) < EPS)
		return 0;
	return ((_x > _y) << 1) - 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
		if (i && x[i] == x[i - 1] && y[i] == y[i - 1])
			--i, --n;
	}
	if (x[0] == x[n - 1] && y[0] == y[n - 1])
		--n;
	cin >> m;
	while (m--) {
		scanf("%d%d", &x2, &y2);
		bool e = 0;
		for (int i = 0; i < n; ++i)
			if (pointOnSegment(point(x[i], y[i]),
					point(x[(i + 1) % n], y[(i + 1) % n]), point(x2, y2))) {
				puts("EDGE");
				e = 1;
				break;
			}
		if (e)
			continue;
		long double ang = 0;
		int rev = 0;
		for (int i = 0; i < n; ++i) {
			int j = (i + 1) % n;
			ang += findAngle(point(x2, y2), point(x[i], y[i]), point(x2, y2),
					point(x[j], y[j]));
			if (doubleCompare(ang, 2 * PI) >= 0)
				++rev, ang -= 2 * PI;
			else if (doubleCompare(ang, -2 * PI) <= 0)
				--rev, ang += 2 * PI;
//			cout << ang << endl;
		}
		printf("%d\n", rev);
	}
}
