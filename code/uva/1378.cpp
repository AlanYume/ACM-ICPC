/********** Sg ���� **********/
//ע�⣺����״̬���Ƽ���sgֵʱ��iѭ���ķ���
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 23 + 6;

int n, stons[kMaxN];
int sg[kMaxN];

//���ö�̬�滮����Sgֵ
void GetMex(){
	bool visit[kMaxN * kMaxN];

	//��Ϊeach person selects three piles of stones numbered i, j, k (i < j, j <= k and at least one stone left in pile i). Then, the person gets one stone out of pile i, and put one stone into pile j and pile k respectively.
	//��������Ϸ��ʯ�������ת�Ƶģ�������i = 23-1��������Ϸ
	//��Ϊ��״̬ת�ƣ����Դ���̬��ǰ�ƣ�����for(int i = 23 - 1; i >= 0; i--)
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
	//��������һ��Сת������Ϊ��n��ʯ�ӣ�����Ϸ��̬����
	//���ԣ���sg����Ų��23 - nλ��ʹ����n��ʯ�ӣ�sg_prt = sg + 23 - n
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