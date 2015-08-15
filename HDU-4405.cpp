/************* 概率DP 求期望（到推） *****************/
//期望的线性性质
//简单理解就是期望之间可根据关系，简单运算（不严谨的理解）。 
//这就为我们解决一个期望问题，不断转化为解决另外的期望问题，最终转化到一个已知的期望上。
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 100000 + 16;
const int kMaxM = 100000 + 16;

int n, m;
int next_sit[kMaxM];
double DP[kMaxN];

int main(){
	while(~scanf("%d %d", &n, &m)){
		if(n == 0 && m == 0) break;

		memset(next_sit, -1, sizeof(next_sit));
		for(int i = 0; i < m; i++){
			int from, to;
			scanf("%d %d", &from, &to);
			next_sit[from] = to;
		}

		memset(DP, 0, sizeof(DP));
		for(int i = n - 1; i >= 0; i--){
			if(next_sit[i] != -1){
				DP[i] = DP[ next_sit[i] ];
			}else{
				for(int j = 1; j <= 6; j++){
					DP[i] += DP[i + j] / 6.0;
				}
				DP[i] += 1;
			}
		}

		printf("%.4f\n", DP[0]);
	}
	return 0;
}