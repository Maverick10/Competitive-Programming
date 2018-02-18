/*
Very simple problem. for every arrow check which it lands inside. 
*/

#include <bits/stdc++.h>
using namespace std;

int r, x, y;

int main() {
	cin >> r;
	int out = 0;
	for (int i = 0; i < 3; ++i) {
		cin >> x >> y;
		for (int j = 0; j < 10; ++j) {
			if (x * x + y * y <= (j + 1) * (j + 1) * r * r) {
				out += 10 - j;
				break;
			}
		}
	}
	cout << out;
}
