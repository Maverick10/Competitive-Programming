#include<bits/stdc++.h>
#include<ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define sz(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))

typedef long long ll;
typedef vector<int> vi;

const int MAX = 255;
const double EPS = 1e-9;

int n, m, mat[2][MAX][MAX], vis[MAX][MAX], visID, dx;
int DX[] = { -1, -1, 1, 1, -2, -2, 2, 2 };
int DY[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

struct point {
	double x, y;
	point(double x = 0, double y = 0) :
			x(x), y(y) {
	}

	bool operator ==(point p) {
		return fabs(p.x - x) < EPS && fabs(p.y - y) < EPS;
	}
};

struct line {
	double a, b, c;
	point p1, p2;
	line(point P1, point P2) {
		p1 = P1, p2 = P2;
		if (p1.x == p2.x)
			a = 1, b = 0, c = -p1.x;
		else {
			a = -(p1.y - p2.y) * 1.0 / (p1.x - p2.x);
			b = 1;
			c = -(a * p1.x) - p1.y;
		}
	}
};

vector<line> lines[2];

bool valid(int x, int y) {
	return x >= 0 && x <= n && y >= 0 && y <= n;
}

bool areParallel(line l1, line l2) {
	return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool between(double x, double y, double z) {
	return x >= min(y, z) && x <= max(y, z);
}

double dot(point a, point b, point c, point d) {
	return (b.x - a.x) * (d.x - c.x) + (b.y - a.y) * (d.y - c.y);
}

bool pointOnRay(point a, point b, point p) {
	return dot(a, p, a, b) > -EPS;
}

bool pointOnLine(line l, point p) {
	if (p == l.p1 || p == l.p2)
		return 0;
	double X = p.x - l.p1.x, Y = p.y - l.p1.y;
	double X2 = l.p2.x - l.p1.x, Y2 = l.p2.y - l.p1.y;
	return fabs(X * Y2 - Y * X2) < EPS && pointOnRay(l.p1, l.p2, p)
			&& pointOnRay(l.p2, l.p1, p);
}

bool areIntersect(line l1, line l2) {
	point p;
	if (areParallel(l1, l2))
		return 0;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

	if (fabs(l1.b) > EPS)
		p.y = -(l1.a * p.x + l1.c);
	else
		p.y = -(l2.a * p.x + l2.c);
	return pointOnLine(l1, p) && pointOnLine(l2, p);
}

bool intersect(line l) {
	for (auto L : lines[0])
		if (areIntersect(l, L))
			return 1;
	for (auto L : lines[1])
		if (areIntersect(l, L))
			return 1;
	return 0;
}

bool dfs(int x, int y) {
	vis[x][y] = visID;
	if (x == dx)
		return 1;
	int ret = 0;
	for (int i = 0; i < 8; ++i) {
		int nx = x + DX[i], ny = y + DY[i];

		if (valid(nx, ny) && mat[0][nx][ny] == visID && vis[nx][ny] != visID) {
			line l(point(x, y), point(nx, ny));
			if (!intersect(l))
				ret |= dfs(nx, ny);
		}
	}
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) == 2 && n) {
		lines[0].clear();
		lines[1].clear();
		++visID;

		for (int i = 0; i < m; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			mat[i & 1][x][y] = visID;
			for (int j = 0; j < 8; ++j) {
				int nx = x + DX[j], ny = y + DY[j];
				if (mat[i & 1][nx][ny] != visID)
					continue;
				line l(point(x, y), point(nx, ny));
				if (!intersect(l))
					lines[i & 1].push_back(l);
			}
		}
		bool ret = 0;
		dx = n;
		for (int i = 0; i <= n; ++i)
			if (mat[0][0][i] == visID && vis[0][i] != visID)
				ret |= dfs(0, i);

		puts(ret ? "yes" : "no");
	}
}
