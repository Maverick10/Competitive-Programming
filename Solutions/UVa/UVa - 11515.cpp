/*
Remove circles with radius zero as they doesn't affect the answer in any way. Since they are only 15 circles we can brute force
on all possible subsets to find out which circles intersect with each others. We can use bitmasks for brute force.
*/
using namespace std;
using namespace __gnu_cxx;

#define sz(v) (int)v.size()
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))

typedef long long ll;
typedef vector<int> vi;

const int MAX = 20;
const double EPS = 1e-9;

int t, n, x[MAX], y[MAX], r[MAX], msk[MAX];

double dist(int X, int Y, int X2, int Y2) {
	return hypot(X - X2, Y - Y2);
}

int doubleCompare(double x, double y) {
	if (fabs(x - y) < EPS)
		return 0;
	return ((x > y) << 1) - 1;
}

bool intersect(int i, int j) {
	double d = dist(x[i], y[i], x[j], y[j]);
	int diff = abs(r[i] - r[j]);
	int dc1 = doubleCompare(diff, d);
	int sum = r[i] + r[j];
	int dc2 = doubleCompare(sum, d);
	return dc1 >= 0 || dc2 >= 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	cin >> t;
	while (t--) {
		CLR(msk, 0);
		int B = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d", &x[i], &y[i], &r[i]);
			if (!r[i])
				--i, --n;
		}
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if (intersect(i, j))
					msk[i] |= (1 << j), msk[j] |= (1 << i);

		for (int i = 0; i < (1 << n); ++i) {
			int cur = 0;
			bool ok = 1;
			for (int j = 0; ok && j < n; ++j)
				if ((i >> j) & 1) {
					if (msk[j] & i) {
						ok = 0;
						break;
					}
					cur += r[j] * r[j];
				}
			if (ok)
				B = max(B, cur);
		}
		printf("%d\n", B);
	}
}
