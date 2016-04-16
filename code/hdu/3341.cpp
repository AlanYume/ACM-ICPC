/************ AC自动机 + hash + 状态压缩DP （难点是构造hash函数） *******************/
//PS： 用个内敛函数（inline）也挺费时间的。
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int kNodeNext = 4;
const int kPatternLen = 10 + 6;
const int kNodeSize = 50 * kPatternLen;
const int kGeneLen = 41 + 6;

struct Node{
	int next_m[kNodeNext], fail;
	int is_pattern_end_cnt;

	void Init(){
		fail = 0;
		memset(next_m, 0, sizeof(next_m));
		is_pattern_end_cnt = 0;
	}
};

int N, char_num[4];
char patter[kPatternLen];
char gene[kGeneLen];
int node_size;
Node node[kNodeSize];
int hash_m[41][41][41][41];
int DP[kNodeSize][15000 + 16]; //DP[sit][num] :=表示当前在节点sit,使用'A'a个，'C'b个,'G'c个,'T'd个，可以最多匹配的模式个数。（后一位进制压缩。num = a*41^0 + b*41^1 + c*41^2 + d*41^3）

inline int ChangToInt(char ch){
	if(ch == 'A') return 0;
	if(ch == 'C') return 1;
	if(ch == 'G') return 2;
	if(ch == 'T') return 3;
}

void InitTire(){
	node_size = 0;
	node[node_size++].Init();
}

void InsertTire(){
	int now_sit = 0;
	for(int i = 0; patter[i]; i++){
		int ch_val = ChangToInt(patter[i]);

		if(node[now_sit].next_m[ch_val] == 0){
			node[node_size].Init();
			node[now_sit].next_m[ch_val] = node_size++;
		}
		now_sit = node[now_sit].next_m[ch_val];
	}
	node[now_sit].is_pattern_end_cnt += 1;
}

void MakeFailPath(){
	queue<int> visit_que;
	visit_que.push(0);

	while(!visit_que.empty()){
		int now_sit = visit_que.front();
		visit_que.pop();

		for(int i = 0; i < kNodeNext; i++){
			int next_sit = node[now_sit].next_m[i];

			if(next_sit == 0){
				node[now_sit].next_m[i] = node[ node[now_sit].fail ].next_m[i];
				continue;
			}
			visit_que.push(next_sit);
			if(now_sit != 0 && next_sit != 0){
				node[next_sit].fail = node[ node[now_sit].fail ].next_m[i];
				node[next_sit].is_pattern_end_cnt += node[ node[ node[now_sit].fail ].next_m[i] ].is_pattern_end_cnt;
			}
		}
	}
}

void Hash(){
	int id = 0;
	for(int i = 0; i <= char_num[0]; i++){
		for(int j = 0; j <= char_num[1]; j++){
			for(int k = 0; k <= char_num[2]; k++){
				for(int l = 0; l <= char_num[3]; l++){
					hash_m[i][j][k][l] = id++;
				}
			}
		}
	}
}

//int GetAns(int sit, int a, int b, int c, int d){
//	int hash_val = hash_m[a][b][c][d];
//	if(a == 0 && b == 0 && c == 0 && d == 0) return DP[sit][hash_val] = 0;
//	if(DP[sit][hash_val] != -1) return DP[sit][hash_val];
//
//	int &result = DP[sit][hash_val] = 0;
//	//使用一个'T'
//	if(d){
//		int next_sit = node[sit].next_m[3];
//		result = max(result, GetAns(next_sit, a, b, c, d - 1) + node[next_sit].is_pattern_end_cnt);
//	}
//	//使用一个'G'
//	if(c){
//		int next_sit = node[sit].next_m[2];
//		result = max(result, GetAns(next_sit, a, b, c - 1, d) + node[next_sit].is_pattern_end_cnt);
//	}
//	//使用一个'C'
//	if(b){
//		int next_sit = node[sit].next_m[1];
//		result = max(result, GetAns(next_sit, a, b - 1, c, d) + node[next_sit].is_pattern_end_cnt);
//	}
//	//使用一个'A'
//	if(a){
//		int next_sit = node[sit].next_m[0];
//		result = max(result, GetAns(next_sit, a - 1, b, c, d) + node[next_sit].is_pattern_end_cnt);
//	}
//
//	return result;
//}

int GetAns(){
	int ans = 0;
	DP[0][0] = 0;
	for(int i = 0; i <= char_num[0]; i++){
		for(int j = 0; j <= char_num[1]; j++){
			for(int k = 0; k <= char_num[2]; k++){
				for(int l = 0; l <= char_num[3]; l++){
					if(i + j + k + l == 0) continue;
					int hash_1 = hash_m[i][j][k][l];
					for(int now_sit = 0; now_sit < node_size; now_sit++){
						for(int chose = 0; chose < 4; chose++){
							int hash_2 = -1;
							if(chose == 0 && i > 0) hash_2 = hash_m[i - 1][j][k][l];
							if(chose == 1 && j > 0) hash_2 = hash_m[i][j - 1][k][l];
							if(chose == 2 && k > 0) hash_2 = hash_m[i][j][k - 1][l];
							if(chose == 3 && l > 0) hash_2 = hash_m[i][j][k][l - 1];
							if(hash_2 == -1 || DP[now_sit][hash_2] == -1) continue;
							int next_sit = node[now_sit].next_m[chose];
							DP[next_sit][hash_1] = max(DP[next_sit][hash_1], DP[now_sit][hash_2] + node[next_sit].is_pattern_end_cnt);
							if(DP[next_sit][hash_1] > ans) ans = DP[next_sit][hash_1];
						}
					}
				}
			}
		}
	}
	return ans;
}

int main(){
	int cas = 1;
	while(~scanf("%d", &N)){
		if(N == 0) break;
		InitTire();

		for(int i = 0; i < N; i++){
			scanf("%s", patter);
			InsertTire();
		}

		MakeFailPath();

		scanf("%s", gene);
		memset(char_num, 0, sizeof(char_num));
		for(int i = 0; gene[i]; i++){
			int ch_val = ChangToInt(gene[i]);
			char_num[ch_val] += 1;
		}

		Hash();
		memset(DP, -1, sizeof(DP));
		printf("Case %d: %d\n", cas++, GetAns());
	}
	return 0;
}
