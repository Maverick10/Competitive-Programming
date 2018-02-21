#include<bits/stdc++.h>
#include <regex>
#include<ext/numeric>
#include<ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v)  (int)v.size()
#define WHITE -1
#define GREY   0
#define BLACK  1
#define CLR(a,v) memset(a,v,sizeof a)
#define PC(x) __builtin_popcount(x)
#define MP make_pair

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
//typedef unsigned int ui;

typedef complex<double> point;
//#define X real()
//#define Y imag()
//#define vec(a,b) ((b)-(a))
//#define dot(a,b) ((conj(a)*(b)).real())
//#define cross(a,b) ((conj(a)*(b)).imag())
#define colliner pointOnLine

const double PI = acos(-1.0);

int dx[] = { 0, -1, 0, 1, -1, -1, 1, 1 };
int dy[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

int DX[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
int DY[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

const int MAX = 2e5 + 5, MOD = 1e9 + 7, oo = (1 << 30), MAXLOG = 18;
const ll OO = 1ll << 60;
const double EPS = 1e-9;

int w, h, xc, yc, r;
double x, y, x2, y2, x3, y3, x4, y4;

bool inCircle(int X, int Y) {
	return abs(X - xc) * abs(X - xc) + abs(Y - yc) * abs(Y - yc) <= r * r;
}

double cross(double X, double Y, double X2, double Y2) {
	return X * Y2 - Y * X2;
}

bool allPos(int X, int Y) {
	return cross(x2 - x, y2 - y, X - x, Y - y) >= 0
			&& cross(x3 - x2, y3 - y2, X - x2, Y - y2) >= 0
			&& cross(x4 - x3, y4 - y3, X - x3, Y - y3) >= 0
			&& cross(x - x4, y - y4, X - x4, Y - y4) >= 0;
}

bool allNeg(int X, int Y) {
	return cross(x2 - x, y2 - y, X - x, Y - y) <= 0
			&& cross(x3 - x2, y3 - y2, X - x2, Y - y2) <= 0
			&& cross(x4 - x3, y4 - y3, X - x3, Y - y3) <= 0
			&& cross(x - x4, y - y4, X - x4, Y - y4) <= 0;
}

bool inSquare(int X, int Y) {
	return allPos(X, Y) || allNeg(X, Y);
}

int main() {

	scanf("%d%d%d%d%d%lf%lf%lf%lf", &w, &h, &yc, &xc, &r, &y, &x, &y3, &x3);
	double xc = (x + x3) / 2, yc = (y + y3) / 2, xd = (x - x3) / 2, yd =
			(y - y3) / 2;
	x2 = xc - yd, y2 = yc + xd, x4 = xc + yd, y4 = yc - xd;
	for (int i = 0; i < h; ++i, puts(""))
		for (int j = 0; j < w; ++j)
			if (inCircle(i, j) || inSquare(i, j))
				printf("#");
			else
				printf(".");
}
