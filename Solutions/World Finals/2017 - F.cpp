#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))
typedef pair<int, int> ii;
typedef vector<ii> vii;

const int MAX = 400;

int d, k, p[MAX], L[MAX][MAX], MD[MAX][MAX], R[MAX][MAX];
ll preSum[MAX][MAX];

void initPreSum() {
	for (int i = 0; i < 256; ++i) {
		for (int j = 0; j < 256; ++j)
			preSum[i][j] = (j - i) * (j - i) * 1ll * p[j];
		for (int j = 1; j < 256; ++j)
			preSum[i][j] += preSum[i][j - 1];
	}
}

ll calc(int i, int j) {
	return (j - i) * (j - i) * 1ll * p[j];
}

void initIntervals() {
	for (int i = 0; i < MAX; ++i)
		for (int j = 0; j < MAX; ++j)
			L[i][j] = MD[i][j] = R[i][j] = MAX - 10;
	for (int i = 0; i < 256; ++i)
		for (int j = i + 1; j < 256; ++j)
			for (int k = i; k <= j; ++k)
				if (p[k]) {
					if (calc(i, k) < calc(j, k)) {
						L[i][j] = min(L[i][j], k);
						MD[i][j] = R[i][j] = k;
					} else {
						MD[i][j] = min(MD[i][j], k - 1);
						R[i][j] = k;
					}
				}
}

ll memo[258][258][258];
const ll OO = 1ll << 50;

ll calcPre(int i, int l, int r) {
	return preSum[i][r] - ((l > 0) ? (preSum[i][l - 1]) : (0));
}

ll solve(int cur, int remK, int lastChosen) {
	if (!remK)
		return calcPre(lastChosen, lastChosen, 255);
	if (cur == 256)
		return OO;
	ll &ret = memo[cur][remK][lastChosen];
	if (~ret)
		return ret;
	ret = solve(cur + 1, remK, lastChosen);
	if (remK == k)
		ret = min(ret, solve(cur + 1, remK - 1, cur) + calcPre(cur, 0, cur));
	else {
		ret = min(ret,
				solve(cur + 1, remK - 1, cur)
						+ calcPre(lastChosen, L[lastChosen][cur],
								MD[lastChosen][cur])
						+ calcPre(cur, MD[lastChosen][cur] + 1,
								R[lastChosen][cur]));
	}
	return ret;
}

int main() {

	cin >> d >> k;
	for (int i = 0; i < d; ++i) {
		int r;
		scanf("%d", &r);
		scanf("%d", &p[r]);
	}
	initPreSum();
	initIntervals();
	CLR(memo, -1);
	printf("%lld\n", solve(0, k, 0));
}
