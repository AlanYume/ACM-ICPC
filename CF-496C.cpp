/******链表 + 模拟*****/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 100 + 16;

int n, m;
char str[kMaxN][kMaxN];
int L[kMaxN], R[kMaxN];

void Init(){
	for(int i = 0; i <= m; i++){
		L[i] = i - 1;
		R[i] = i + 1;
	}
	L[0] = R[m] = -1;
};

bool Compare(int str_id_1, int str_id_2, int max_len){
	for(int c = R[0]; c < max_len; c = R[c]){
		if(str[str_id_1][c] < str[str_id_2][c]){
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", str[i] + 1);

	int delete_cnt = 0;
	Init();
	for(int c = 1; c <= m; c++){ //判断当前列是否要删除
		for(int r = 1; r < n; r++){
			if(str[r - 1][c] > str[r][c] && Compare(r - 1, r, c)){
				R[L[c]] = R[c];
				L[R[c]] = L[c];
				delete_cnt++;
				break;
			}
		}
	}
	printf("%d\n", delete_cnt);
	return 0;
}
