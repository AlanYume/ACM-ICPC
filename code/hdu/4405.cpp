/************* ����DP �����������ƣ� *****************/
//��������������
//������������֮��ɸ��ݹ�ϵ�������㣨���Ͻ�����⣩�� 
//���Ϊ���ǽ��һ���������⣬����ת��Ϊ���������������⣬����ת����һ����֪�������ϡ�
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