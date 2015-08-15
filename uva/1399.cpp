/*************  AC自动机 + 记忆化搜索  ***************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int kPatternLen = 50 + 6;
const int kNodeNext = 26;
const int kNodeSize = kPatternLen * 1000;

struct Node{
	int next_m[kNodeNext], fail;
	bool is_pattern_end;

	//状态转移，求最长不包含禁止串的字符串中用到
	bool visited;
	int max_len; //从当前节点开始往下走，可以构成的最长不包含任何禁止模式串的字符串长度
	int print_next; //下一个要输出的字符

	void Init(){
		fail = 0;
		memset(next_m, 0, sizeof(next_m));
		is_pattern_end = false;
		
		visited = false;
		max_len = -1;
		print_next = -1;
	}
};

int n, s;
char pattern_str[kPatternLen];
int node_size;
Node node[kNodeSize];

inline int ChangeToInt(char ch){
	return ch - 'A';
}

inline void InitTrie(){
	node_size = 0;
	node[node_size++].Init();
}

void InsertTrie(){
	int now_sit = 0;
	for(int i = 0; pattern_str[i]; i++){
		int ch_val = ChangeToInt(pattern_str[i]);

		if(node[now_sit].next_m[ch_val] == 0){
			node[node_size].Init();
			node[now_sit].next_m[ch_val] = node_size++;
		}
		now_sit = node[now_sit].next_m[ch_val];
	}
	node[now_sit].is_pattern_end = true;
}

void MakeFailPath(){
	queue<int> visit_que;
	visit_que.push(0);
	
	while(!visit_que.empty()){
		int now_sit = visit_que.front();
		visit_que.pop();
		
		for(int i = 0; i < n; i++){
			int next_sit = node[now_sit].next_m[i];
			if(next_sit == 0){ //状态转移，对下一个可能出现的字符一视同仁
				node[now_sit].next_m[i] = node[ node[now_sit].fail ].next_m[i];
				continue;
			}
			visit_que.push(next_sit);
			if(now_sit != 0 && next_sit != 0){
				node[next_sit].fail = node[ node[now_sit].fail ].next_m[i];
				node[next_sit].is_pattern_end |= node[ node[now_sit].fail ].is_pattern_end;
			}
		}
	}
}

int GetMaxLenStr(int root){
	if(node[root].visited == true) return -1;
	if(node[root].max_len != -1) return node[root].max_len;
	
	node[root].visited = true;
	int &result = node[root].max_len = 0;
	
	for(int i = n - 1; i >= 0; i--){
		if(node[ node[root].next_m[i] ].is_pattern_end == false){
			int tmp_len = GetMaxLenStr(node[root].next_m[i]);
			if(tmp_len == -1) return -1;
			if(tmp_len + 1 > result){
				result = tmp_len + 1;
				node[root].print_next = i;
			}
		}
	}
	node[root].visited = false;
	return result;
}

void Print(int root){
	if(node[root].print_next != -1){
		printf("%c", node[root].print_next + 'A');
		int print_next = node[root].print_next;
		if(print_next != -1)
		Print(node[root].next_m[ print_next ]);
	}
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		InitTrie();

		scanf("%d %d", &n, &s);
		for(int i = 0; i < s; i++){
			scanf("%s", pattern_str);
			InsertTrie();
		}

		MakeFailPath();

		int ans = GetMaxLenStr(0);
		if(ans <= 0){
			printf("No\n");
		}else{
			Print(0);
			printf("\n");
		}
	}
}