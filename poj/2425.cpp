/********* ����ͼ�ϵ� SG���� ************/
/* ֤����http://qianmacao.blog.163.com/blog/static/203397180201234994844/
*����һ��SG���������ʡ����ȣ����е�terminal position����Ӧ�Ķ��㣬
*Ҳ����û�г��ߵĶ��㣬��SGֵΪ0����Ϊ���ĺ�̼����ǿռ���Ȼ�����
*һ��g(x) = 0�Ķ���x���������к�� y ������ g(y) != 0������һ�� 
*g(x) != 0�Ķ��㣬�ض�����һ����� y ���� g(y) = 0.
*��ʵϸ��һ�£�������SG�������е���PN�����ˡ�
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 1000 + 16;

int n;
bool filed[kMaxN][kMaxN];
int sg[kMaxN];

int GetMex(int from){
	if(sg[from] != -1) return sg[from];

	bool visit[kMaxN];
	memset(visit, false, sizeof(visit));
	for(int i = 0; i < n; i++){
		if(filed[from][i]){
			visit[GetMex(i)] = true;
		}
	}

	for(int i = 0; ; i++){
		if(visit[i] == false){
			return sg[from] = i;
		}
	}
}

int main(){
	while(~scanf("%d", &n)){

		memset(filed, false, sizeof(filed));
		for(int i = 0; i < n; i++){
			int du, to;
			scanf("%d", &du);
			for(int j = 0; j < du; j++){
				scanf("%d", &to);
				filed[i][to] = true;
			}
		}

		int stons_cnt;
		memset(sg, -1, sizeof(sg));
		while(~scanf("%d", &stons_cnt)){
			if(stons_cnt == 0) break;

			int xor_sum = 0;
			for(int i = 0; i < stons_cnt; i++){
				int now_sit;
				scanf("%d", &now_sit);
				xor_sum ^= GetMex(now_sit);
			}

			printf("%s\n", xor_sum ? "WIN" : "LOSE");
		}
	}
	return 0;
}