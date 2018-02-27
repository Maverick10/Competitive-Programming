/*
We can use disjoint set union to join between shapes that intersect, or subsume each other.
to determine intersection we check if any edge from polygon i intersects any other edge from
polygon j. to determine subsumption, it's sufficient to check if any point from polygon i
is inside polygon j.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()

typedef complex<long double> point;
#define cross(a,b) ((conj(a)*(b)).imag())
#define vec(a,b) ((b)-(a))
#define X real()
#define Y imag()
#define dot(a,b) ((conj(a)*(b)).real())
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define lengthSqr(v) (dot(v,v))

const int MAX = 50;
const double EPS = 1e-9;

int n, p[MAX], siz[MAX];
vector<vector<point> > polygon;
string s;

void init() {
	polygon.clear();
	for (int i = 0; i < n; ++i)
		p[i] = i, siz[i] = 1;
}

int findSet(int x) {
	return p[x] == x ? x : p[x] = findSet(p[x]);
}

bool sameSet(int u, int v) {
	return findSet(u) == findSet(v);
}

void unionSet(int u, int v) {
	if (sameSet(u, v))
		return;
	int s1 = findSet(u), s2 = findSet(v);
	siz[s1] += siz[s2];
	p[s2] = s1;
}

bool intersect(const point &a, const point &b, const point &p, const point &q,
		point &ret) {

	//handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

	long double d1 = cross(p - a, b - a);
	long double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}

void inXY(vector<point>& v) {
	stringstream ss;
	ss << s;
	int x, y;
	while (ss >> x >> y) {
		if (!v.empty() && v.back().X == x && v.back().Y == y)
			continue;
		v.push_back(point(x, y));
	}
}

enum STATE {
	IN, OUT, BOUNDRY
};

bool pointOnLine(const point& a, const point& b, const point& p) {
	// degenerate case: line is a point
	double c = fabs(cross(vec(a,b), vec(a,p)));
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
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

bool polygonInPolygon(int i, int j) {
	for (int k = 0; k < sz(polygon[i]); ++k) {
		STATE pip = pointInPolygon(polygon[j], polygon[i][k]);
		if (pip != OUT)
			return 1;
	}
	return 0;
}

bool intersect2(const point &a, const point &b, const point &p, const point &q,
		point &ret) {

	//handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

	long double d1 = cross(p - a, b - a);
	long double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS && pointOnSegment(a, b, ret)
			&& pointOnSegment(p, q, ret))
		return 1;
	return 0;
}

bool polygonIntersect(const vector<point>& p, const vector<point>& q) {
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		for (int k = 0; k < sz(q); ++k) {
			int l = (k + 1) % sz(q);
			point pnt;
			if (intersect2(p[i], p[j], q[k], q[l], pnt))
				return 1;
		}
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (getline(cin, s)) {
		if (s == "0")
			break;
		sscanf(s.c_str(), "%d", &n);
		init();
		for (int i = 0; i < n; ++i) {
			vector<point> v;
			getline(cin, s);
			inXY(v);
			polygon.push_back(v);
		}
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				bool b1 = polygonIntersect(polygon[i], polygon[j]);
				bool b2 = polygonInPolygon(i, j);
				bool b3 = polygonInPolygon(j, i);
				if (b1 || b2 || b3)
					unionSet(i, j);
			}

		int out = 0;
		for (int i = 0; i < n; ++i)
			if (findSet(i) == i)
				++out;
		printf("%d\n", out);
	}
//	point r;
//	intersect(point(6702, 4518), point(8166, -2840), point(-8997, 4048),
//			point(-8996, 4048), r);
//	cout << pointOnLine(point(6702, 4518), point(8166, -2840), r);
}
