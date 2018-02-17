/*
It's easy to realize that the graph is a DAG. Then we can run floyd-warshall algorithm
to determine all pairs LONGEST paths. suppose we have dist[i][j] that indicates the longest
possible distance between scripts i and j, then if this dist is exactly 1 (or -1 in this
implementation) then script i must include script j
*/
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define CLR(a,v) memset(a,v,sizeof(a))
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()

const int MAX = 55;

vi ret;
int n, dist[MAX][MAX];

void floyd() {
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

class ImportsList {
public:
	vector<int> importsCount(vector<string> requires) {
		n = sz(requires);
		ret.resize(n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				dist[i][j] = 1e9;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (requires[i][j] == 'Y')
					dist[i][j] = -1;
		floyd();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (dist[i][j] == -1)
					++ret[i];
		return ret;
	}
};

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	vector<string> v = { "NYYY", "NNYY", "NNNY", "NNNN" };
	ImportsList i;
	auto k = i.importsCount(v);
	for (auto x : k)
		cout << x << ' ';
}
