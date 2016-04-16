/************* AC自动机（动态分配和释放节点版） *******/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

const int kMaxStrLen = 70 + 16;
const int kMaxMessageLen = 1000000 +16;
const int kNodeNext = 26;
const int kMaxPatternsSize = 150 + 16;


struct Node{
	Node *next_m[kNodeNext], *fail;
	int str_end_id;
	Node(){
		str_end_id = -1;
		fail = NULL;
		memset(next_m, NULL, sizeof(next_m));
	}
};

int N, M;
char virus_str[kMaxPatternsSize][kMaxStrLen], message[kMaxMessageLen];
int ans_patterns[kMaxPatternsSize];
map<string, int> map_patterns;

void BuildTrie(Node *root, int id){
	Node *now_prt = root;
	for(int i = 0; virus_str[id][i] != '\0'; i++){
		if(now_prt->next_m[virus_str[id][i] - 'a'] == NULL){
			now_prt->next_m[virus_str[id][i] - 'a'] = new Node();
		}
		now_prt = now_prt->next_m[virus_str[id][i] - 'a'];
	}
	now_prt->str_end_id = id;
}

void BuildFailPrt(Node *root){
	queue<Node *> prt_que;
	prt_que.push(root);

	while(!prt_que.empty()){
		Node *tmp_prt = prt_que.front();
		prt_que.pop();

		for(int i = 0; i < kNodeNext; i++){
			if(tmp_prt->next_m[i] != NULL){
				Node *same_prt = tmp_prt->fail; //同类节点

				while(same_prt != NULL){
					if(same_prt->next_m[i] != NULL){
						tmp_prt->next_m[i]->fail = same_prt->next_m[i];
						break;
					}else{
						same_prt = same_prt->fail;
					}
				}
				if(same_prt == NULL){
					tmp_prt->next_m[i]->fail = root;
				}

				prt_que.push(tmp_prt->next_m[i]);
			}
		}

	}
}

int Search_AC(Node *root, char *s){
	int maxVal = 0;
	Node *now_prt = root;
	for(int i = 0; s[i] != '\0'; i++){
		while(now_prt->next_m[s[i] - 'a'] == NULL && now_prt != root){
			now_prt = now_prt->fail;
		}
		now_prt = (now_prt->next_m[s[i] - 'a'] == NULL) ? root : now_prt->next_m[s[i] - 'a'];

		Node *tmp_prt = now_prt;
		while(tmp_prt != root){
			if(tmp_prt->str_end_id != -1){
				ans_patterns[tmp_prt->str_end_id] += 1;
				maxVal = max(maxVal, ans_patterns[tmp_prt->str_end_id]);
			}
			tmp_prt = tmp_prt->fail;
		}
	}
	return maxVal;
}

void DeletedNode(Node *root){
	queue<Node *> tmp_que;
	tmp_que.push(root);
	while(!tmp_que.empty()){
		Node *tmp_prt = tmp_que.front();
		tmp_que.pop();

		for(int i = 0; i < kNodeNext; i++){
			if(tmp_prt->next_m[i] != NULL)
				tmp_que.push(tmp_prt->next_m[i]);
		}

		delete(tmp_prt);
	}
}

int main(){
	while(~scanf("%d", &N)){
		if(N == 0) break;
		memset(ans_patterns, 0, sizeof(ans_patterns));
		map_patterns.clear();

		Node *root = new Node();
		int cnt = 1;
		for(int i = 1; i <= N; i++){
			scanf("%s", virus_str[0]);
			if(map_patterns[virus_str[0]] == 0){
				map_patterns[virus_str[0]] = 1;
				memcpy(virus_str[cnt], virus_str[0], sizeof(virus_str[0]));
				BuildTrie(root, cnt++);
			}
		}

		BuildFailPrt(root);
		scanf("%s", message);
		int max_ans = Search_AC(root, message);
		printf("%d\n", max_ans);
		for(int i = 1; i < cnt; i++){
			if(ans_patterns[i] == max_ans){
				printf("%s\n", virus_str[i]);
			}
		}

		DeletedNode(root);
	}
	return 0;
}