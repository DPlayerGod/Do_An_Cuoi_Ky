#include "testlib.h"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

const int N = 1e5 + 5;
const int Sz = 1e6;
const int Lim = 2e3;
int b[N], m, t, par[N];

int Rand(int l, int h) {
    return rd() % (h - l + 1) + l;
}

int main(int argc, char* argv[]) {
   	registerGen(argc, argv, 1);
   	int g1 = argc >= 2 ? stoll(argv[1],nullptr,10) : 10;
   	int g2 = argc >= 3 ? stoll(argv[2],nullptr,10) : g2;


	int n = Rand(1500, 2000);
	
	cout << n << '\n';
	
	if (g2 == 1) {
		for (int i = 1; i <= n; i++) {
			int x = Rand(1, 100000);
			while (b[x] != 0) x = Rand(1, 100000);
			b[x] = 1;
			cout << x << ' ';
		}	 
	}
	else if (g2 == 2) {
		for (int i = 1; i <= n; i++) cout << i << ' ';
	}
	else if (g2 == 3) {
		for (int i = n; i >= 1; --i) cout << i << ' ';
	}
}
