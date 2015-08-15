/****** 基础Sg ********/
//(因为数据量n=2*10 ^18太大，先打Nim表，找规律，之后在构造Sg函数）
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;
const int kMaxN = 100 + 16;

int n;
ll stons[kMaxN];

ll GetMex(ll x){
	return x % 2 ? GetMex(x >> 1) : (x >> 1);
}

ll Win(){
	ll xor_sum = 0;
	for(int i = 0; i < n; i++){
		xor_sum ^= GetMex(stons[i]);
	}
	return xor_sum;
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%lld", &stons[i]);
		}

		printf("%s\n", Win() ? "YES" : "NO");
	}
	return 0;
}