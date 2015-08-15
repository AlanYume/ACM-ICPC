/**************  AC自动机 + 记忆化搜索 ***************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
const int kPatternLen = 10 + 6;
const int kPatternNumber = 10 + 6;
const int kPasswordLen = 25 + 1;
const int kNodeNext = 26;
const int kNodeSize = kPatternLen * kPatternNumber;

struct Node{
	int next_m[kNodeNext], fail, val; //val :=二进制状态压缩位，每一个二进制的“1”位表示对应编号的模式串

	void Init(){
		fail = val = 0;
		memset(next_m, 0, sizeof(next_m));
	}
};

int n, m;
char pattern[kPatternLen];
int node_size;
Node node[kNodeSize];

char tmp_char[kPasswordLen];
ll DP[kPasswordLen][kNodeSize][(1 << 10) + 6];

int ChangeToInt(char ch){
	return ch - 'a';
}

void InitTrie(){
	node_size = 0;
	node[node_size++].Init();
}

void InsertTrie(int id){
	int now_sit = 0;
	for(int i = 0; pattern[i]; i++){
		int ch_val = ChangeToInt(pattern[i]);

		if(node[now_sit].next_m[ch_val] == 0){
			node[node_size].Init();
			node[now_sit].next_m[ch_val] = node_size++;
		}
		now_sit = node[now_sit].next_m[ch_val];
	}
	node[now_sit].val |= id;
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
				node[next_sit].val |= node[ node[next_sit].fail ].val;
			}
		}
	}
}

ll GetAns(int len, int sit, int S, bool print){
	if(len == n){
		if(S + 1 == (1 << m)) return DP[len][sit][S] = 1;
		return DP[len][sit][S] = 0;
	}
	if(DP[len][sit][S] != -1) return DP[len][sit][S];
	ll &result = DP[len][sit][S] = 0;

	for(int i = 0; i < kNodeNext; i++){
		int next_sit = node[sit].next_m[i];
		result += GetAns(len + 1, next_sit, S | node[next_sit].val, print);
	}
	return result;
}

void PrintAns(int len, int sit, int S){
	if(len == n){
		tmp_char[len] = '\0';
		printf("%s\n", tmp_char);
		return ;
	}
	for(int i = 0; i < kNodeNext; i++){
		int next_sit = node[sit].next_m[i];
		if(DP[len + 1][next_sit][S | node[next_sit].val] > 0){
			tmp_char[len] = i + 'a';
			PrintAns(len + 1, next_sit, S | node[next_sit].val);
		}
	}
}

int main(){
	int cas = 1;
	while(~scanf("%d %d", &n, &m)){
		if(n == 0 && m == 0) break;

		InitTrie();
		for(int i = 0; i < m; i++){
			scanf("%s", pattern);
			InsertTrie(1 << i);
		}

		MakeFailPath();
		memset(DP, -1, sizeof(DP));
		ll ans = GetAns(0, 0, 0, false);

		printf("Case %d: %lld suspects\n", cas++, ans);
		if(ans <= 42){
			PrintAns(0, 0, 0);
		}
	}
	return 0;
}