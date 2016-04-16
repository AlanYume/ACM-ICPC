/********* hash + BFS ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <queue>
using namespace std;

typedef long long ll;
const int MOD = 100000007;
const int kMaxN = 4;
const int kMaxM = 8;

struct State{
	int step;
	pair<int, int> space[kMaxN];
	int num[kMaxN][kMaxM];

	int GetHash(){
		ll hash_sum = 0;
		ll base = 1;
		for(int i = 0; i < kMaxN; i++){
			for(int j = 0; j < kMaxM; j++){
				hash_sum = (hash_sum + num[i][j] * base) % MOD;
				base <<= 1;
			}
		}
		return hash_sum;
	}

	static int GetAnsHash(){
		ll res_hash = 0;
		ll base = 1;
		for(int i = 0; i < kMaxN; i++){
			for(int j = 0; j < kMaxM; j++){
				int tmp_val = (i+1)*10+j+1;
				if(j+1 == kMaxM) tmp_val = 0;
				res_hash = (res_hash + tmp_val * base) % MOD;
				base <<= 1;
			}
		}
		return res_hash;
	}
};

//hashMap版本1：set存储hash值
struct HashMap{
	set<int> my_set;

	void Init(){
		my_set.clear();
	}

	bool Insert(int val){
		if(my_set.find(val) == my_set.end()){
			my_set.insert(val);
			return true;
		}else{
			return false;
		}
	}
};

//hashMap版本2：数组存储hash值
/*struct HashMap{
	int hash_map[MOD];
	Init(){
		memset(hash_map, -1, sizeof(hash_map));
	}

	bool Insert(int val){
		int insert_id = val;
		while(hash_map[insert_id] != -1 && hash_map[insert_id] != val){ //哈系地址冲突，再散列
			insert_id = (insert_id + 10) % MOD;
		}
		if(hash_map[insert_id] == -1){
			hash_map[insert_id] = val;
			return true;
		}else{
			return false;
		}
	}
};
*/

int hash_ans;
State input_state;
HashMap my_hash_map;

int GetAnsMinSteps(){
	my_hash_map.Insert(hash_ans);
	if(my_hash_map.Insert(input_state.GetHash()) == false) return 0;

	queue<State> my_que;
	input_state.step = 0;
	my_que.push(input_state);
	while(!my_que.empty()){
		State now_state = my_que.front();
		my_que.pop();
		for(int k = 0; k < kMaxN; k++){
			int xx = now_state.space[k].first;
			int yy = now_state.space[k].second;
			int pre_space_val = now_state.num[xx][yy - 1];

			if(pre_space_val % 10 == 7) continue;
			State next_state = now_state;
			for(int i = 0; i < kMaxN; i++){
				for(int j = 1; j < kMaxM; j++){
					if(pre_space_val + 1 == now_state.num[i][j]){
						next_state.num[xx][yy] = pre_space_val + 1;
						next_state.num[i][j] = 0;
						next_state.space[k] = make_pair(i,j);
						next_state.step = now_state.step + 1;

						int next_hash_val = next_state.GetHash();
						if(my_hash_map.Insert(next_hash_val)){
							my_que.push(next_state);
						}else if(next_hash_val == hash_ans){
							return next_state.step;
						}
					}
				}
			}
		}
	}
	return -1;
}

int main(){
	hash_ans = State::GetAnsHash();

	int test;
	scanf("%d", &test);
	while(test--){
		my_hash_map.Init();

		for(int i = 0; i < kMaxN; i++){
			for(int j = 1; j < kMaxM; j++){
				scanf("%d", &input_state.num[i][j]);
				if(input_state.num[i][j] % 10 == 1){
					int tmp_row = input_state.num[i][j] / 10;
					input_state.space[tmp_row - 1] = make_pair(i, j);
					input_state.num[tmp_row - 1][0] = input_state.num[i][j];
					input_state.num[i][j] = 0;
				}
			}
		}

		printf("%d\n", GetAnsMinSteps());
	}
	return 0;
}

