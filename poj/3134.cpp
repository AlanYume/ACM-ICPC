/********* IDA*(迭代加深搜索） ********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 1000;

int n;
int limit_dep, dep_num[kMaxN + 16];

bool IDASTART(int now_dep){
	if(now_dep > limit_dep || (dep_num[now_dep] << (limit_dep - now_dep)) < n) return false;
	if(dep_num[now_dep] == n) return true;
	for(int i = 0; i <= now_dep; i++){
		//乘
		dep_num[now_dep+1] = dep_num[now_dep] + dep_num[i];
		if(dep_num[now_dep+1] < (n << 1)){
			if(IDASTART(now_dep+1)) return true;
		}

		//除
		dep_num[now_dep+1] = dep_num[now_dep] - dep_num[i];
		if(dep_num[now_dep+1] < 0) dep_num[now_dep+1] = -dep_num[now_dep+1];
		if(dep_num[now_dep+1] != 0){
			if(IDASTART(now_dep+1)) return true;
		}
	}
	return false;
}

int main(){
	dep_num[0] = 1;
	while(~scanf("%d", &n)){
		if(n == 0) break;
		limit_dep = 0;
		while(!IDASTART(0)){
			limit_dep++;
		}
		printf("%d\n", limit_dep);
	}
	return 0;
}

