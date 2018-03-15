/*
For every point, we have to check whether it's inside a given polygon or not. If it's inside multiple polygons, we can get the desired
one by checking which of them has the smallest area.
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
#define cross(a,b) ((conj(a)*(b)).imag())
#define dot(a,b) ((conj(a)*(b)).real())
#define vec(a,b) ((b)-(a))
#define EPS 1e-9
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define Y imag()
#define lengthSqr(v) (dot(v,v))

int t, nc, np;
vi idxC;
vector<vector<point> > polygon;
vector<pair<int, point> > points;

long double polygonArea(const vector<point>&p) {
	long double res = 0;
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		res += cross(p[i], p[j]);
	}
	return fabs(res) / 2;
}

enum STATE {
	IN, OUT, BOUNDRY
};

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

bool intersect(const point &a, const point &b, const point &p, const point &q,
		point &ret) {

	//handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}

STATE pointInPolygon(const vector<point>& p, const point &pnt) {
	point p2 = pnt + point(1, 0);
	int cnt = 0;
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		if (pointOnSegment(p[i], p[j], pnt))
			return BOUNDRY;
		point r;
		if (!intersect(pnt, p2, p[i], p[j], r))
			continue;
		if (!pointOnRay(pnt, p2, r))
			continue;
		if (same(r, p[i]) || same(r, p[j]))
			if (fabs(r.Y - min(p[i].Y, p[j].Y)) < EPS)
				continue;
		if (!pointOnSegment(p[i], p[j], r))
			continue;
		cnt++;
	}
	return cnt & 1 ? IN : OUT;
}

bool comp(pair<int, point> p1, pair<int, point> p2) {
	return p1.first < p2.first;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> t;
	while (t--) {
		scanf("%d", &nc);
		idxC.resize(nc);
		polygon.resize(nc);
		for (int i = 0; i < nc; ++i) {
			polygon[i].clear();
			scanf("%d", &idxC[i]);
			char c;
			while (scanf("%c", &c) == 1 && c != '\n') {
				double x, y;
				scanf("%lf%lf", &x, &y);
				polygon[i].push_back(point(x, y));
			}
		}

		scanf("%d", &np);
		points.resize(np);
		for (int i = 0; i < np; ++i) {
			double x, y;
			scanf("%d%lf%lf", &points[i].first, &x, &y);
			points[i].second = point(x, y);
		}
		sort(all(points), comp);
//		cout << np << endl;
		for (int i = 0; i < np; ++i) {
			printf("%d ", points[i].first);
			int out = 0;
			double a = 1e18;
			for (int j = 0; j < nc; ++j)
				if (pointInPolygon(polygon[j], points[i].second) != OUT) {
					double A = polygonArea(polygon[j]);
					if (A < a)
						a = A, out = idxC[j];
				}
			printf("%d\n", out);
		}
		if (t)
			puts("");
	}
}
