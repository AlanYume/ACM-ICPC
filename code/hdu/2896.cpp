/***************  AC自动机  ******************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int kMaxStrLen = 200 + 16;
const int kMaxMessageLen = 10000 +16;
const int kNodeNext = 128;

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
char virus_str[kMaxStrLen], message[kMaxMessageLen];

void BuildTrie(Node *root, char *s, int id){
	Node *now_prt = root;
	for(int i = 0; s[i] != '\0'; i++){
		if(now_prt->next_m[s[i]] == NULL){
			now_prt->next_m[s[i]] = new Node();
		}
		now_prt = now_prt->next_m[s[i]];
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

vector<int> Search_AC(Node *root, char *s){
	vector<int> result;
	Node *now_prt = root;
	for(int i = 0; s[i] != '\0'; i++){
		while(now_prt->next_m[s[i]] == NULL && now_prt != root){
			now_prt = now_prt->fail;
		}
		now_prt = (now_prt->next_m[s[i]] == NULL) ? root : now_prt->next_m[s[i]];

		Node *tmp_prt = now_prt;
		while(tmp_prt != root){
			if(tmp_prt->str_end_id != -1) result.push_back(tmp_prt->str_end_id);
			tmp_prt = tmp_prt->fail;
		}
	}

	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

int main(){
	scanf("%d", &N);
	Node *root = new Node();
	for(int i = 1; i <= N; i++){
		scanf("%s", virus_str);
		BuildTrie(root, virus_str, i);
	}

	BuildFailPrt(root);

	int web_size = 0;
	scanf("%d", &M);
	for(int i = 1; i <= M; i++){
		scanf("%s", message);
		vector<int> virus_id = Search_AC(root, message);
		int virus_id_size = virus_id.size();
		if(virus_id_size != 0){
			printf("web %d:", i);
			for(int j = 0; j < virus_id_size; j++){
				printf(" %d", virus_id[j]);
			}
			printf("\n");
			web_size += 1;
		}
	}

	printf("total: %d\n", web_size);
	return 0;
}
