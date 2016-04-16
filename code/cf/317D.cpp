/*********** Sg ���� *********/
//ѯ��ĳţ��˼·��http://www.cnblogs.com/Mathics/p/3950154.html#3074141
//���Է��֣����ڸò�����Ϸ������Ϸ��x��1~k���ݣ��������������µĲ��ġ�
//������Ϸ��SGֵֻ������йأ���x��ֵ�޹ء���k���ֻ��30���ʿ��Դ��
//����Ϸ���ս������������Ϸ���ֵ��
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

/* Ԥ������power�����

const int kMaxPower = 30;
const int kMaxN = 1 << kMaxPower;

int n;
char power_sg[kMaxN + 16];
int sg[kMaxPower + 6];

int GetPowerSg(int S){
	if(power_sg[S] != -1) return power_sg[S];
	
	bool visit[kMaxPower + 6];
	memset(visit, false, sizeof(visit));
	for(int i = 1; i <= kMaxPower; i++){ //ö��2^i,��i== 1����Sȫ����ȥ
		if(S >> (i - 1) & 1){
			int tmpS = S;
			for(int j = i; j <= kMaxPower; j += i){ //��ȥ2^k��
				if(tmpS >> (j - 1) & 1){
					tmpS &= ~(1 << (j - 1));
				}
			}
			visit[GetPowerSg(tmpS)] = true;
		}
	}

	int g = 0;
	while(visit[g] == true) g++;
	return power_sg[S] = g;
}

int main(){
	memset(power_sg, -1, sizeof(power_sg));
	GetPowerSg((1 << kMaxPower) - 1);
	for(int i = 1; i <= kMaxPower; i++){
		sg[i] = power_sg[(1 << i) - 1];
	}
	for(int i = 0; i <= kMaxPower; i++){
		printf("%d ,", sg[i]);
	}
	printf("\n");
}
*/

typedef long long ll;
const int kMaxN = 100000; //sqrt(1000000000)

int n;
int sg[] = {0 ,1 ,2 ,1 ,4 ,3 ,2 ,1 ,5 ,6 ,2 ,1 ,8 ,7 ,5 ,9 ,8 ,7 ,3 ,4 ,7 ,4 ,2 ,1 ,10 ,9 ,3 ,6 ,11 ,12 ,14};
bool visit[kMaxN + 16];

int Win(){
	memset(visit, false, sizeof(visit));

	int one_cnt = n, xor_sum = 0;
	for(int i = 2; i * i <= n; i++){
		if(visit[i] == false){
			int cnt = 0;
			for(ll j = i; j <= n; j *= i){
				if(j <= kMaxN) visit[j] = true;
				cnt += 1;
			}
			xor_sum ^= sg[cnt];
			one_cnt -= cnt;
		}
	}
	return xor_sum ^ (one_cnt & 1);
}

int main(){
	scanf("%d", &n);
	printf("%s\n", Win() ? "Vasya" : "Petya");
	return 0;
}