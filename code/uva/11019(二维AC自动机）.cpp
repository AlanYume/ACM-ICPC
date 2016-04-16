/*********** AC自动机 (二维块模式匹配）*******************/
// 推荐使用的 AC自动机 模板
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

const int kMatrixSize = 1000 + 16;
const int kPatternSize = 100 + 16;
const int kNodeNext = 26;
const int kNodeSize = 100 * 100 + 16;

struct Node{
	int next_m[kNodeNext], fail;
	vector<int> row_id;
	void Init(){
		fail = 0;
		memset(next_m, 0, sizeof(next_m));
		row_id.clear();
	}
};

int n, m;
char matrix[kMatrixSize][kMatrixSize];
int cnt[kMatrixSize][kMatrixSize];
int x, y;
char pattern[kPatternSize];
int node_size;
Node node[kNodeSize];

inline int ChangeToInt(char ch){
	return ch - 'a';
}

inline void InitTrie(){
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
	node[now_sit].row_id.push_back(id);
}

void MakeFailPath(){
	queue<int> visit_que;
	visit_que.push(0);

	while(!visit_que.empty()){
		int now_sit = visit_que.front();
		visit_que.pop();

		for(int i = 0; i < kNodeNext; i++){
			int next_sit = node[now_sit].next_m[i];
			if(next_sit != 0){
				visit_que.push(next_sit);
			}
			if(now_sit != 0 && next_sit != 0){
				node[next_sit].fail = node[ node[now_sit].fail ].next_m[i];
			}
		}
	}
}

void ACSearch(int id){
	int now_sit = 0;
	for(int i = 0; matrix[id][i]; i++){
		int ch_val = ChangeToInt(matrix[id][i]);
		while(now_sit != 0 && node[now_sit].next_m[ch_val] == 0){
			now_sit = node[now_sit].fail;
		}
		now_sit = node[now_sit].next_m[ch_val];

		int tmp_sit = now_sit;
		while(tmp_sit != 0){
			int row_size = node[tmp_sit].row_id.size();
			for(int j = 0; j < row_size; j++){
				int x = node[tmp_sit].row_id[j];
				if(id >= x) cnt[id - x][i] += 1;
			}
			tmp_sit = node[tmp_sit].fail;
		}
	}
}

int Solve(){
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < n; i++) ACSearch(i);

	int result = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(cnt[i][j] == x) result += 1;
		}
	}

	return result;
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%s", matrix[i]);

		InitTrie();

		scanf("%d %d", &x, &y);
		for(int i = 0; i < x; i++){
			scanf("%s", pattern);
			InsertTrie(i);
		}

		MakeFailPath();

		printf("%d\n", Solve());
	}
	return 0;
}