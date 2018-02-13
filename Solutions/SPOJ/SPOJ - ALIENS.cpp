#include<bits/stdc++.h>
#include<ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define sz(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))

typedef long long ll;
typedef vector<int> vi;

const int MAX = 1e5 + 5;
const double EPS = 1e-9;

typedef complex<double> point;
#define mid(a,b) (((a)+(b))/point(2,0))
#define vec(a,b) ((b)-(a))
#define X real()
#define Y imag()
#define length(v) ((long double)hypot((v).Y,(v).X))
#define perp(a) (point(-(a).Y,(a).X))
#define cross(a,b) ((conj(a)*(b)).imag())
#define lengthSqr(v) (dot(v,v))
#define dot(a,b) ((conj(a)*(b)).real())

point p[MAX], r[3], cen;
int ps, rs;
long double rad;

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

void circle2(const point& p1, const point& p2, point& cen, long double& r) {
	cen = mid(p1, p2);
	r = length(vec(p1, p2)) / 2;
}

bool circle3(const point& p1, const point& p2, const point& p3, point& cen,
		long double& r) {
	point m1 = mid(p1, p2);
	point m2 = mid(p2, p3);
	point perp1 = perp(vec(p1, p2));
	point perp2 = perp(vec(p2, p3));
	bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
	r = length(vec(cen, p1));
	return res;
}

enum STATE {
	IN, OUT, BOUNDRY
};

STATE circlePoint(const point & cen, const long double & r, const point& p) {
	long double lensqr = lengthSqr(vec(cen, p));
	if (fabs(lensqr - r * r) < EPS)
		return BOUNDRY;
	if (lensqr < r * r)
		return IN;
	return OUT;
}

void mec() {
	if (rs == 3) {
		circle3(r[0], r[1], r[2], cen, rad);
		return;
	}
	if (rs == 2 && ps == 0) {
		circle2(r[0], r[1], cen, rad);
		return;
	}
	if (!ps) {
		cen = r[0];
		rad = 0;
		return;
	}
	ps--;
	mec();
	if (circlePoint(cen, rad, p[ps]) == OUT) {
		r[rs++] = p[ps];
		mec();
		rs--;
	}
	ps++;

}

int TC;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d", &ps);
		for (int i = 0; i < ps; ++i) {
			double x, y;
			scanf("%lf%lf", &x, &y);
			p[i]= {x,y};
		}
		mec();
		printf("%.2Lf\n%.2lf %.2lf\n", rad, cen.X, cen.Y);
	}
}
