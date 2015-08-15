/***********   AC自动机（静态版）   **********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int kMaxPatternsLen = 70 + 16;
const int kMaxTxtLen = 1000000 + 16;
const int kNodeNext = 26;
const int kPatternsNumber = 150 + 6;
const int kNodeSize = 70 * kPatternsNumber + 16;

struct Node{
	int next_m[kMaxPatternsLen], fail;
	int end_pattern_id;
};

int n;
char patterns[kPatternsNumber][kMaxPatternsLen], txt[kMaxTxtLen];
map<string, int> map_pattern;
int node_size;
Node node[kNodeSize];
int ans_patterns[kPatternsNumber];

void InitNode(){
	node_size = 1;
	for(int i = 0; i < kNodeSize; i++){
		memset(node[i].next_m, -1, sizeof(node[i].next_m));
		node[i].fail = 0;
		node[i].end_pattern_id = -1;
	}
	node[0].fail = -1;
	memset(ans_patterns, 0, sizeof(ans_patterns));
}

void InsertTire(int id){
	int now_sit = 0;

	for(int i = 0; patterns[id][i]; i++){
		int val = patterns[id][i] - 'a';
		if(node[now_sit].next_m[val] == -1){
			node[now_sit].next_m[val] = node_size++;
		}
		now_sit = node[now_sit].next_m[val];
	}
	node[now_sit].end_pattern_id = id;
}

void MakeFailPath(){
	int now_sit = 0;
	queue<int> visit_que;
	visit_que.push(now_sit);

	while(!visit_que.empty()){
		now_sit = visit_que.front();
		visit_que.pop();

		for(int i = 0; i < kNodeNext; i++){
			if(node[now_sit].next_m[i] != -1){
				int same_sit = node[now_sit].fail; //同类节点

				while(same_sit != -1){
					if(node[same_sit].next_m[i] != -1){
						node[ node[now_sit].next_m[i] ].fail = node[same_sit].next_m[i];
						break;
					}
					same_sit = node[same_sit].fail;
				}
				if(same_sit == -1){
					node[ node[now_sit].next_m[i] ].fail = 0;
				}

				visit_que.push(node[now_sit].next_m[i]);
			}
		}
	}
}

void ACSerache(){
	int now_sit = 0;
	for(int i = 0; txt[i]; i++){
		int val = txt[i] - 'a';
		while(now_sit != 0 && node[now_sit].next_m[val] == -1){
			now_sit = node[now_sit].fail;
		}
		now_sit = (node[now_sit].next_m[val] == -1) ? 0 : node[now_sit].next_m[val];

		int tmp_sit = now_sit;
		while(tmp_sit != 0){
			if(node[tmp_sit].end_pattern_id != -1)
				ans_patterns[ node[tmp_sit].end_pattern_id ] += 1;
			tmp_sit = node[tmp_sit].fail;
		}
	}
}

int main(){
	while(~scanf("%d", &n)){
		if(n == 0) break;

		InitNode();
		map_pattern.clear();
		int cnt = 1;
		for(int i = 1; i <= n; i++){
			scanf("%s", patterns[0]);
			if(map_pattern[patterns[0]] == 0){
				map_pattern[patterns[0]] = 1;
				memcpy(patterns[cnt], patterns[0], sizeof(patterns[0]));
				InsertTire(cnt++);
			}

		}

		MakeFailPath();

		scanf("%s", txt);
		ACSerache();

		int max_cnt = 0;
		for(int i = 1; i < cnt; i++){
			max_cnt = max(max_cnt, ans_patterns[i]);
		}
		printf("%d\n", max_cnt);
		for(int i = 1; i < cnt; i++){
			if(ans_patterns[i] == max_cnt){
				printf("%s\n", patterns[i]);
			}
		}
	}
	return 0;
}