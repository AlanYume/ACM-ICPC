/************* 矩阵的幂 ****************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;
const ll MOD = 1000000007;
const int kMaxN = 8 + 2;

int n, r, k;
ll s[kMaxN], a[kMaxN];

mat Mul(mat &A, mat &B){
	mat C(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); i++){
		for(int k = 0; k < B.size(); k++){
			if(A[i][k] == 0) continue;
			for(int j = 0; j < B[0].size(); j++){
				if(B[k][j] == 0) continue;
				C[i][j] = (C[i][j] +A[i][k] * B[k][j]) % MOD;
			}
		}
	}
	return C;
}

mat Pow(mat A, ll n){
	mat B(A.size(), vec(A[0].size()));
	for(int i = 0; i < A.size(); i++){
		B[i][i] = 1;
	}
	while(n > 0){
		if(n & 1) B = Mul(B, A);
		A = Mul(A, A);
		n >>= 1;
	}
	return B;
}

ll Solve(){
	//构造 A^k 矩阵
	mat mat_a(9, vec(9));
	for(int i = 1; i < 8; i++){
		mat_a[i][i - 1] = 1;
	}
	for(int i = 0; i < 8; i++){
		mat_a[i][8 - 1] = a[8 - i - 1];
	}
	mat_a = Pow(mat_a, k);

	//构造求和矩阵
	mat_a[8][8] = mat_a[k - 1][8] = 1;
	mat_a = Pow(mat_a, n);

	//构造求和S[k] 矩阵
	mat mat_sum(1, vec(9));
	for(int i = r; i < 8; i++){
		s[i] = 0;
		for(int j = 0; j < r; j++){
			s[i] = (s[i] + s[i - j - 1] * a[j]) % MOD;
		}
	}
	for(int i = 0; i < 8; i++){
		mat_sum[0][i] = s[i];
	}
	mat_sum = Mul(mat_sum, mat_a);

	return mat_sum[0][8];
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d %d %d", &n, &r, &k);
		for(int i = 0; i < r; i++){
			scanf("%lld", &s[i]);
		}
		memset(a, 0, sizeof(a));
		for(int i = 0; i < r; i++){
			scanf("%lld", &a[i]);
		}

		printf("%lld\n", Solve());
	}
	return 0;
}