#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

int n;

int powerMod(ll x, int n, int mod) {
	ll res = 1;
	while(n) {
		if(n & 1) res = res * x % mod;
		x = (x * x) % mod;
		n >>= 1;
	}
	return res;
}

bool isPrime(int x) {
	for(int i = 2; i * i <= x; i++) {
		if(x % i == 0) return false;
	}
	return true;
}

void Solve() {
	bool isCarmichaelNumber = true;
	if(isPrime(n)) isCarmichaelNumber = false;
	for(int i = 2; i < n && isCarmichaelNumber; i++) {
		if(i % n != powerMod(i, n, n)) isCarmichaelNumber = false;
	}
	if(isCarmichaelNumber) {
		printf("The number %d is a Carmichael number.\n", n);
	} else {
		printf("%d is normal.\n", n);
	}
}

int main() {
	while(~scanf("%d", &n)) {
		if(n == 0) return 0;
		Solve();
	}
}
