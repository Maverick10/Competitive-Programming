/*
It will be hard to keep track of where every vertex is. so we can keep track of where vertex
A is only, and then determine if we need a flip or a rotation to restore vertex A to position
0.
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()

const int MAX = 105;

int n, m, k;

int main() {

	cin >> n >> m;
	int cur = 0;
	bool flip = 0;
	while (m--) {
		int t;
		scanf("%d%d", &t, &k);
		if (t == 1) {
			cur += k;
			cur %= n;
		} else {
			flip = 1 - flip;
			int target;
			if (n & 1) {
				if (k & 1) {
					target = n / 2 + k / 2 + 1;
					if (target == cur)
						continue;
					cur = ((2 * target) - cur + n) % n;
				} else {
					target = k / 2;
					if (target == cur)
						continue;
					cur = ((2 * target) - cur + n) % n;
				}
			} else {
				if (k & 1) {
					cur = (k - cur + n) % n;
				} else {
					target = k / 2;
					if (target == cur || (target + n / 2) % n == cur)
						continue;
					cur = ((2 * target) - cur + n) % n;
				}
			}
		}
	}
	if (flip) {
		cout << 2 << ' ';
		for (int k = 0; k < n; ++k) {
			int target, fin = cur;
			if (n & 1) {
				if (k & 1) {
					target = n / 2 + k / 2 + 1;
					if (target != cur)
						fin = ((2 * target) - cur + n) % n;
				} else {
					target = k / 2;
					if (target != cur)
						fin = ((2 * target) - cur + n) % n;
				}
			} else {
				if (k & 1) {
					target = k / 2;
					fin = (k - cur + n) % n;
				} else {
					target = k / 2;
					if (target != cur && (target + n / 2) % n != cur)
						fin = ((2 * target) - cur + n) % n;
				}
			}
			if (fin == 0)
				return printf("%d\n", k), 0;
		}
	} else
		cout << 1 << ' ' << (n - cur) % n;
}
