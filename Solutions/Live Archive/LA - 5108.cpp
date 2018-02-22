/*
Let's think of a solution of complexity O(N*Q) per test case. In each query we can calculate
the area of the polygon which contain the vertices in the interval [ai, bi]. Then the answer
to query i will be the minimum between the area that we just calculated and the difference
between the total area of the polygon and the area just calculated. Since this solution will
yield TLE, we can sort the queries according to MO's algorithm which will guarantee a solution
of complexity O((N+Q)*sqrt(N)) per test case, which should be enough to get the AC.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()

const int MAX = 5e4 + 5, BLOCK = 230;

struct query {
	int l, r, i;
	query(int l = 0, int r = 0, int i = 0) :
			l(l), r(r), i(i) {
	}
	bool operator <(const query& q) {
		return l / BLOCK < q.l / BLOCK || (l / BLOCK == q.l / BLOCK && r < q.r);
	}
} Q[MAX];

int n, q, x[MAX], y[MAX];
ll ans[MAX];

ll calc(int i, int j, int k) {
	int X = x[j] - x[i], Y = y[j] - y[i], X2 = x[k] - x[i], Y2 = y[k] - y[i];
	return abs(X * 1ll * Y2 - X2 * 1ll * Y);
}

bool b;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	while (scanf("%d%d", &n, &q) == 2 && n) {
		if (b)
			puts("");
		b = 1;
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &x[i], &y[i]);
		for (int i = 0; i < q; ++i)
			scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].i = i;
		sort(Q, Q + q);
		ll A = 0;
		for (int i = 1; i < n - 1; ++i)
			A += calc(0, i, i + 1);
//		cout << "DEBUG: " << A << endl;

		int curL = Q[0].l, curR = Q[0].r;
		ll a = 0;
		for (int i = curL + 1; i < curR; ++i)
			a += calc(curL, i, i + 1);
		ans[Q[0].i] = min(a, A - a);
//		cout << a << endl;
		for (int i = 1; i < q; ++i) {
			int l = Q[i].l, r = Q[i].r, idx = Q[i].i;
			while (curL > l) {
				a += calc(curR, curL, curL - 1);
				curL--;
				if (!a)
					curL = l, curR = l + 1;
			}
			while (curL < l) {
				a -= calc(curR, curL, curL + 1);
				curL++;
				if (!a)
					curL = l, curR = l + 1;
			}
			while (curR > r) {
				a -= calc(curL, curR, curR - 1);
				curR--;
				if (!a)
					curR = r;
			}
			while (curR < r) {
				a += calc(curL, curR, curR + 1);
				curR++;
				if (!a)
					curR = r;
			}
			ans[idx] = min(a, A - a);
		}
		for (int i = 0; i < q; ++i)
			printf("%lld.%d\n", (ans[i] >> 1), (ans[i] & 1) ? 5 : 0);
	}
}
