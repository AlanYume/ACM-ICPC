/*************** AC自动机 +　概率DP （推荐的ＡＣ自动机模板）*************************/
//网上博客上的代码基本出自同一个模板：在建立失败路径的时候，都是先弄个前两层特殊处理下，然后再广搜处理接下几层。
//这道题目的难点也就在建立失败路径的转移状态上了。
//抄来抄去的，不想多说什么。（我想说的，如果把特判的前两层也一起处理了，代码看起来会更加优雅些）
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int kMaxPatternLen = 20 + 6;
const int kNextSize = 10 + 26 * 2;
const int kMaxNodeSize = 20 * kNextSize + 16;
const int kMaxL = 100 + 16;

struct Node{
	int next_m[kNextSize], fail;
	bool is_pattern_end;

	void InitNode_s(){
		fail = 0;
		memset(next_m, 0, sizeof(next_m));
		is_pattern_end = false;
	}
};

int k, n, possible_str_len;
char pattern[kMaxPatternLen];
double possible[kNextSize];
int node_size;
Node node[kMaxNodeSize];
double DP[kMaxNodeSize][kMaxL]; //DP[i][j] :=当前在结点i，还要走j步，不碰到任何禁止结点的概率

inline int ChangeToInt(char ch){
	if(ch >= 'a' && ch <= 'z') return ch - 'a';
	if(ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
	if(ch >= '0' && ch <= '9') return ch - '0' + 26 * 2;
}

inline void InitNode(){
	node_size = 1;
	node[0].InitNode_s();
	memset(DP, -1, sizeof(DP));
	memset(possible, 0, sizeof(possible));
}

void InsertTire(){
	int now_sit = 0;
	for(int i = 0; pattern[i]; i++){
		int ch_val = ChangeToInt(pattern[i]);
		if(node[now_sit].next_m[ch_val] == 0){
			node[node_size].InitNode_s();
			node[now_sit].next_m[ch_val] = node_size++;
		}
		now_sit = node[now_sit].next_m[ch_val];
	}
	node[now_sit].is_pattern_end = true;
}

//注意：这里并非通常意义上的 添加失败路径
void MakeFailPath(){
	queue<int> visited_que;
	visited_que.push(0);

	while(!visited_que.empty()){
		int now_sit = visited_que.front();
		visited_que.pop();

		for(int i = 0; i < kNextSize; i++){
			int next_sit = node[now_sit].next_m[i];
			if(next_sit == 0){ //因为下一个节点不存在，所以只需从新定向next_m指向，具体的是否是禁止模式，由被指向节点决定
				node[now_sit].next_m[i] = node[ node[now_sit].fail ].next_m[i];
			}else{
				visited_que.push(next_sit);
			}
			if(now_sit != 0 && next_sit != 0){ //因为是实节点，所以必须处理齐禁止模式（禁止模式可以由其他节点的fail推的，联带性）
				node[next_sit].fail = node[ node[now_sit].fail ].next_m[i];
				node[next_sit].is_pattern_end |= node[ node[next_sit].fail ].is_pattern_end;
			}
		}
	}
}

double GetPossible(int now_sit, int l){
	if(l == 0) return 1.0;
	if(DP[now_sit][l] >= 0) return DP[now_sit][l];
	DP[now_sit][l] = 0;
	for(int i = 0; i < kNextSize; i++){
		if(possible[i] == 0) continue;
		int next_node = node[now_sit].next_m[i];
		if(node[next_node].is_pattern_end == false){
			DP[now_sit][l] += possible[i] * GetPossible(next_node, l - 1);
		}
	}

	return DP[now_sit][l];
}

int main(){
	int test;
	scanf("%d", &test);
	for(int cas = 1; cas <= test; cas++){
		scanf("%d", &k);

		InitNode();
		for(int i = 0; i < k; i++){
			scanf("%s", pattern);
			InsertTire();
		}

		MakeFailPath();


		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			char tmp_str[5];
			double tmp_possible;
			scanf("%s %lf", tmp_str, &tmp_possible);
			possible[ChangeToInt(tmp_str[0])] = tmp_possible;
		}

		scanf("%d", &possible_str_len);
		printf("Case #%d: %.6f\n", cas, GetPossible(0, possible_str_len));
	}
	return 0;
}