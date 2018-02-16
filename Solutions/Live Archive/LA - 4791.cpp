/*
Forget about the fact that they are two paths, one is going from east to west and the other
from west to east. They are just two separate paths that contain the nodes 0 and n-1 at
their beginnings and ends. We can use dynamic programming to solve the problem of state
dp[i][j][k][b] => minimum distance that can be covered to the end given that we are
standing at node i, the last picked node for the first path is j, the last picked node
for the second path is k, and b is a boolean that states whether we picked a red node 
for the first path or not.
*/
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define CLR(a,v) memset(a,v,sizeof(a))
#define all(v) v.begin(),v.end()

const int MAX = 105;
int n, b1, b2, x[MAX], y[MAX], TC;
double memo[MAX][MAX][MAX][2];
vi raye7, rage3;

void init() {
	raye7.clear();
	rage3.clear();
	CLR(memo, -1);
}

double dist(int i, int j) {
	return hypot(x[i] - x[j], y[i] - y[j]);
}

double solve(int i, int j, int k, bool b) {
	if (i == n - 1)
		return dist(i, j) + dist(i, k);
	double &ret = memo[i][j][k][b];
	if (ret == ret)
		return ret;
	ret = 0;
	if (i == b2) {
		if (b)
			ret = solve(i + 1, j, i, 1) + dist(i, k);
		else
			ret = solve(i + 1, i, k, 1) + dist(i, j);
	} else
		ret = min(solve(i + 1, i, k, b || i == b1) + dist(i, j),
				solve(i + 1, j, i, b) + dist(i, k));
	return ret;
}

void buildPath(int i, int j, int k, bool b) {
	if (i == n - 1) {
		raye7.push_back(i);
		return;
	}
	if (i == b2) {
		if (b) {
			rage3.push_back(i);
			buildPath(i + 1, j, i, 1);
		} else {
			raye7.push_back(i);
			buildPath(i + 1, i, k, 1);
		}
	} else {
		double A = solve(i + 1, i, k, b || i == b1) + dist(i, j);
		double B = solve(i + 1, j, i, b) + dist(i, k);
		if (A < B) {
			raye7.push_back(i);
			buildPath(i + 1, i, k, b || i == b1);
		} else {
			rage3.push_back(i);
			buildPath(i + 1, j, i, b);
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d%d", &n, &b1, &b2) == 3 && n) {
		printf("Case %d: ", ++TC);
		init();
		if (b1 > b2)
			swap(b1, b2);
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &x[i], &y[i]);
		printf("%.2lf\n", solve(2, 1, 0, 1 == b1) + dist(0, 1));
		buildPath(2, 1, 0, 1 == b1);
		reverse(all(rage3));
		printf("0 1");
		for (auto X : raye7)
			printf(" %d", X);
		for (auto X : rage3)
			printf(" %d", X);
		puts(" 0");
	}
}
