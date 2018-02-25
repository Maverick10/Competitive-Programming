/*
consider the first planet, you can get its coordinates easily by calculating its current positive
angle from x-axis (theta = 2*PI*T/t0), then its coordinates will be (r0*cos(theta), r0*sin(theta))
Now consider that planet as the sun for the next planet, in other words, translating the 
origin to the coordinates of this planet, then we can easily get the second planet's
coordinates. and so on
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)

typedef complex<double> point;
#define vec(a,b) ((b)-(a))
#define rotate(v,t) (polar(v,t))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define rotateabout(v,t,a)  (rotate(vec(a,v),t)+(a))
#define X real()
#define Y imag()
#define normalize(p) ((p)/length(p))
#define length(v) ((double)hypot((v).Y,(v).X))

const int MAX = 55;
int n;
double T, r, t;
const double PI = acos(-1);

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%d%lf", &n, &T) == 2) {

		double x = 0, y = 0;
		for (int i = 0; i < n; ++i) {
			if (i)
				printf(" ");
			scanf("%lf%lf", &r, &t);
			double theta = T * 2 * PI / t;
			x += r * cos(theta);
			y += r * sin(theta);
			printf("%.4lf", hypot(x, y));
		}
		puts("");
	}
}
