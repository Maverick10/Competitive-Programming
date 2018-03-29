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

const int MAX = 4005;
int n;
string str[MAX];
vector<string> v1, v2, holdForNow(MAX);

bool comp(string s, string t) {
	return sz(s) < sz(t);
}

bool subseq(string &s, string &t) {
	int i = 0, j = 0;
	for (; j < sz(t) && i < sz(s); ++j)
		if (t[j] == s[i])
			++i;
	return i == sz(s);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	for (int i = 0; i <= n; ++i)
		cin >> str[i];
	v1.push_back(str[0]);
	v2.push_back(str[0]);
	holdForNow[0] = str[0];
	int hfn = 1;
	sort(str + 1, str + n + 1, comp);
	for (int i = 1; i <= n; ++i) {
		if (!subseq(str[i], str[0]))
			return puts("impossible");
		bool s1 = (sz(v1) == 1) || (sz(v1) > 1 && subseq(v1.back(), str[i]));
		bool s2 = (sz(v2) == 1) || (sz(v2) > 1 && subseq(v2.back(), str[i]));
//		cout << str[i] << ' ' << v1.back() << ' ' << v2.back() << endl;
		if (!s1 && !s2)
			return puts("impossible");
		if (s1 && !s2) {
			v1.push_back(str[i]);
			for (int j = 1; j < hfn; ++j)
				v2.push_back(holdForNow[j]);
			hfn = 1;
		} else if (s2 && !s1) {
			v2.push_back(str[i]);
			for (int j = 1; j < hfn; ++j)
				v1.push_back(holdForNow[j]);
			hfn = 1;
		} else {
			if ((hfn == 1) || (hfn > 1 && subseq(holdForNow[hfn - 1], str[i])))
				holdForNow[hfn++] = str[i];
			else {
				v1.push_back(str[i]);
				for (int j = 1; j < hfn; ++j)
					v2.push_back(holdForNow[j]);
				hfn = 1;
			}
		}
	}
	for (int i = 1; i < hfn; ++i)
		v2.push_back(holdForNow[i]);

	cout << sz(v1) - 1 << ' ' << sz(v2) - 1 << endl;
	for (int i = 1; i < sz(v1); ++i)
		cout << v1[i] << endl;
	for (int i = 1; i < sz(v2); ++i)
		cout << v2[i] << endl;

}
