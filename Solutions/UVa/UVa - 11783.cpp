/*
We can use O(n^2) solution to find the number of nails. for every piece i we check if any 
piece j (i<j) intersects with it, if so we increment the answer by 1. if a piece i doesn't
intersect with any other piece in the input, we increment the answer by 2 for it must be
nailed to the ground.
*/

#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point;
#define cross(a,b) ((conj(a)*(b)).imag())
#define dot(a,b) ((conj(a)*(b)).real())
#define vec(a,b) ((b)-(a))

const int MAX = 1005;
const double EPS = 1e-9;
point p[MAX], p2[MAX];
int inter[MAX], aID, n;

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

bool pointOnLine(const point& a, const point& b, const point& p) {
	// degenerate case: line is a point
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}

bool pointOnRay(const point& a, const point& b, const point& p) {
	//IMP NOTE: a,b,p must be collinear
	return dot(vec(a,p), vec(a,b)) > -EPS;
}

bool pointOnSegment(const point& a, const point& b, const point& p) {
	if (!pointOnLine(a, b, p))
		return 0;
	return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		++aID;
		for (int i = 0; i < n; ++i) {
			int x, y, x2, y2;
			scanf("%d%d%d%d", &x, &y, &x2, &y2);
			p[i] = point(x, y);
			p2[i] = point(x2, y2);
		}
		int out = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				point r;
				if (intersect(p[i], p2[i], p[j], p2[j], r)
						&& pointOnSegment(p[i], p2[i], r)
						&& pointOnSegment(p[j], p2[j], r)) {
					++out;
					inter[i] = inter[j] = aID;
				}
			}
			if (inter[i] != aID)
				out += 2;
		}
		printf("%d\n", out);
	}
}

