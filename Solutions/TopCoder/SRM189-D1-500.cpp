/*
We can use dynamic programming using bitmasks. let i be the mask of programs that we currently
executed, then in[i] will be the minimum time that these programs finished using the input, 
and out[i] will be the minimum time that they finished using the output. so the answer will 
be out[(1<<n)-1]

Time Complexity: O(n * 2^n)
Space Complexity: O(2^n)
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()

const int oo = 1e9;
int n, in[1 << 20], out[1 << 20];

struct ScheduleResources {
	int schedule(vector<int> A, vector<int> B) {
		n = sz(A);
		for (int i = 0; i < (1 << n); ++i)
			in[i] = out[i] = oo;
		in[0] = out[0] = 0;
		for (int i = 0; i < (1 << n) - 1; ++i)
			for (int j = 0; j < n; ++j) {
				if ((i >> j) & 1)
					continue;
				int _in = in[i] + A[j];
				int _out = max(_in, out[i]) + B[j];
				if (_out < out[i | (1 << j)])
					out[i | (1 << j)] = _out, in[i | (1 << j)] = _in;
				else if (_out == out[i | (1 << j)])
					in[i | (1 << j)] = min(_in, in[i | (1 << j)]);
			}
		for (int i = 0; i < (1 << n); ++i)
			cout << out[i] << endl;
		return out[(1 << n) - 1];
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	ScheduleResources s;
	cout << s.schedule( { 7, 6, 3 }, { 9, 7, 3 });
}
