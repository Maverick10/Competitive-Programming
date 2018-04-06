#include<bits/stdc++.h>
using namespace std;

#define sz(v) (int)v.size()
typedef pair<int, int> ii;
typedef vector<ii> vii;

const int MAX = 1e5 + 5;
int n, k, a[MAX], c[MAX], sA;

bool lb(int x, int i, int d) {
	return d * 1ll * a[i] / sA == x;
}

int whenLb(int x, int i) {
	return (x * 1ll * sA + a[i] - 1) / a[i];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out2.txt", "w", stdout);
#endif
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		sA += a[i];
	}
	for (int i = 0; i < k; ++i) {
		int x;
		scanf("%d", &x);
		++c[x];
	}
	priority_queue<ii, vii, greater<ii> > q1, q2;
	int lim = (k / sA + 1) * sA;
	for (int i = 1; i <= n; ++i)
		if (lb(c[i], i, k)) {
			int D = whenLb(c[i] + 1, i);
			if (D <= lim)
				q1.push(make_pair(D, i));
		} else {
			int D = whenLb(c[i], i);
			if (D <= lim)
				q2.push(make_pair(D, i));
		}

	int curD = k;
	while (sz(q1)) {
		int i = q1.top().second;
		int d = q1.top().first;
		q1.pop();
		if (d <= curD) {
			printf("%d\n", d - k - 1);
			return 0;
		}
		++curD;
		++c[i];
		if (lb(c[i], i, curD)) {
			int D = whenLb(c[i] + 1, i);
			if (D <= lim)
				q1.push(make_pair(D, i));
		} else {
			int D = whenLb(c[i], i);
			if (D <= lim)
				q2.push(make_pair(D, i));
		}
		while (sz(q2)) {
			int d2 = q2.top().first;
			if (d2 != curD)
				break;
			int i2 = q2.top().second;
			q2.pop();
			int D = whenLb(c[i2] + 1, i2);
			if (D <= lim)
				q1.push(make_pair(D, i2));
		}
	}
	puts("forever");
}

