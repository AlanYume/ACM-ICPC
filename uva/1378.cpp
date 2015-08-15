/********** Sg 博弈 **********/
//注意：根据状态递推计算sg值时，i循环的方向
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 23 + 6;

int n, stons[kMaxN];
int sg[kMaxN];

//利用动态规划计算Sg值
void GetMex(){
	bool visit[kMaxN * kMaxN];

	//因为each person selects three piles of stones numbered i, j, k (i < j, j <= k and at least one stone left in pile i). Then, the person gets one stone out of pile i, and put one stone into pile j and pile k respectively.
	//所以子游戏的石子是向后转移的，最终在i = 23-1处结束游戏
	//因为是状态转移，所以从终态往前推，即：for(int i = 23 - 1; i >= 0; i--)
	for(int i = 23 - 1; i >= 0; i--){
		memset(visit, false, sizeof(visit));
		for(int j = i + 1; j < 23; j++){
			for(int k = j; k < 23; k++){
				visit[sg[j] ^ sg[k]] = true;
			}
		}

		int g = 0;
		while(visit[g] == true) g++;
		sg[i] = g;
	}
}

void Solve(){
	//这里做了一个小转换，因为是n堆石子（到游戏终态），
	//所以，把sg往后挪了23 - n位，使满足n堆石子，sg_prt = sg + 23 - n
	int *sg_prt = sg + 23 - n;

	int xor_sum = 0;
	for(int i = 0; i < n; i++){
		if(stons[i] & 1) xor_sum ^= sg_prt[i];
	}

	if(xor_sum == 0){
		printf("-1 -1 -1\n");
	}else{
		for(int i = 0; i < n; i++){
			if(stons[i] == 0) continue;
			for(int j = i + 1; j < n; j++){
				for(int k = j; k < n; k++){
					if((sg_prt[i] ^ sg_prt[j] ^ sg_prt[k] ^ xor_sum) == 0){
						printf("%d %d %d\n", i, j , k);
						return ;
					}
				}
			}
		}
	}
}

int main(){
	GetMex();

	int cas = 1;
	while(~scanf("%d", &n)){
		if(n == 0) break;
		for(int i = 0; i < n; i++){
			scanf("%d", &stons[i]);
		}

		printf("Game %d: ", cas++);
		Solve();
	}
	return 0;
}