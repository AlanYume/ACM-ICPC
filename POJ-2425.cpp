/********* 有向图上的 SG博弈 ************/
/* 证明：http://qianmacao.blog.163.com/blog/static/203397180201234994844/
*来看一下SG函数的性质。首先：所有的terminal position所对应的顶点，
*也就是没有出边的顶点，其SG值为0，因为它的后继集合是空集。然后对于
*一个g(x) = 0的顶点x，它的所有后继 y 都满足 g(y) != 0。对于一个 
*g(x) != 0的顶点，必定存在一个后继 y 满足 g(y) = 0.
*其实细想一下，这样的SG分析就有点像PN分析了。
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