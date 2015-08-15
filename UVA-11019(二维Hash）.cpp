/*************** Hash ¿éÄ£Ê½Æ¥Åä ************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

typedef unsigned long long ull;
const int kMaxSize = 1000 + 16;

int n, m;
char field[kMaxSize][kMaxSize];
int x, y;
char pattern[kMaxSize][kMaxSize];

ull hash_m[kMaxSize][kMaxSize], tmp[kMaxSize][kMaxSize];

void ComputeHash(char a[kMaxSize][kMaxSize], int n, int m){
	const ull B1 = 9973;
	const ull B2 = 100000007;

	ull t1 = 1;
	for(int j = 0; j < y; j++) t1 *= B1;
	for(int i = 0; i < n; i++){
		ull e = 0;
		for(int j = 0; j < y; j++) e = e * B1 + a[i][j];
		for(int j = 0; j + y <= m; j++){
			tmp[i][j] = e;
			if(j + y < m) e = e * B1 - t1 * a[i][j] + a[i][j + y];
		}
	}

	ull t2 = 1;
	for(int i = 0; i < x; i++) t2 *= B2;
	for(int j = 0; j + x <= n; j++){
		ull e = 0;
		for(int i = 0; i < x; i++) e = e * B2 + tmp[i][j];
		for(int i = 0; i + x <= n; i++){
			hash_m[i][j] = e;
			if(i + x < n) e = e * B2 - t2 * tmp[i][j] + tmp[i + x][j];
		}
	}
}

int Solve(){
	ComputeHash(pattern, x, y);
	ull pattern_hash_val = hash_m[0][0];
	
	int result = 0;
	ComputeHash(field, n, m);
	for(int i = 0; i + x <= n; i++){
		for(int j = 0; j + y <= m; j++){
			if(hash_m[i][j] == pattern_hash_val) result += 1;
		}
	}
	return result;
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%s", field[i]);
		scanf("%d %d", &x, &y);
		for(int i = 0; i < x; i++) scanf("%s", pattern[i]);
		printf("%d\n", Solve());
	}
	return 0;
}