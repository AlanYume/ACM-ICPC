/****** A* ********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef unsigned long long ull;
typedef pair<ull, int> P;
const int kMaxN = 3;
const int kMaxM = 50 + 4;

int manhanttan_dist[kMaxN*kMaxN][kMaxN*kMaxN];
ull hash_base[kMaxN*kMaxN];
short ans_moves[kMaxM], tmp_moves[4];
ull ans_hash_val;

struct Dir{
	static const int NOMOVE = 0;
	static const int LEFT = -1;
	static const int RIGTH = 1;
	static const int UP = -kMaxN;
	static const int DOWN = kMaxN;
}dir;

struct Node{
	int depth, hg_val, blanck_id;
	ull hash_val;
	vector<short> state;
	short moves[kMaxM];

	bool operator < (const Node &tmp_node) const{
		return hg_val > tmp_node.hg_val;
	}
};

inline int Abs(int val){
	return val > 0 ? val : -val;
}

void GetManHantTanDist(){
	for(int i = 0; i < kMaxN*kMaxN; i++){
		for(int j = 0; j < kMaxN*kMaxN; j++){
			manhanttan_dist[i][j] = Abs(i/kMaxN - j/kMaxN) + Abs(i%kMaxN - j%kMaxN);
		}
	}
}

void GetHashBase(){
	hash_base[0] = 1;
	for(int i = 1; i < kMaxN*kMaxN; i++){
		hash_base[i] = hash_base[i-1]*9;
	}
}

void AnsHashVal(){
	ans_hash_val = 0;
	for(int i = 0; i + 1 < kMaxN*kMaxN; i++){
		ans_hash_val += hash_base[i]*(i+1);
	}
}

ull GetStateHashVal(const vector<short> &state, int &blanck_id){
	ull state_hash = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		state_hash += hash_base[i] * state[i];
		if(state[i] == 0) blanck_id = i;
	}
	return state_hash;
}

bool HaveAns(const vector<short> &state){
	int inversion_pair = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(state[i]){
			for(int j = i + 1; j < kMaxN*kMaxN; j++){
				if(state[i] > state[j] && state[j]) inversion_pair++;
			}
		}
	}
	return !(inversion_pair&1);
}

int GetHgVal(const Node &tmp_node){
	int hg_val = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(tmp_node.state[i]){
			hg_val += manhanttan_dist[tmp_node.state[i]-1][i];
		}
	}
	return hg_val + tmp_node.depth;
}

void NowNodeNextMoves(const Node &tmp_node){
	memset(tmp_moves, dir.NOMOVE, sizeof(tmp_moves));

	short last_move = 0;
	if(tmp_node.depth){
		last_move = tmp_node.moves[tmp_node.depth-1];
	}

	if(tmp_node.blanck_id % kMaxN && last_move != dir.RIGTH){
		tmp_moves[0] = dir.LEFT;
	}
	if(tmp_node.blanck_id % kMaxN + 1 != kMaxN && last_move != dir.LEFT){
		tmp_moves[1] = dir.RIGTH;
	}
	if(tmp_node.blanck_id / kMaxN && last_move != dir.DOWN){
		tmp_moves[2] = dir.UP;
	}
	if(tmp_node.blanck_id / kMaxN + 1 != kMaxN && last_move != dir.UP){
		tmp_moves[3] = dir.DOWN;
	}
}

Node Excete(const Node &now_node, int move){
	Node next_node;
	next_node.depth = now_node.depth + 1;
	next_node.blanck_id = now_node.blanck_id + move;
	next_node.hash_val = now_node.hash_val + (hash_base[now_node.blanck_id] - hash_base[next_node.blanck_id]) * now_node.state[next_node.blanck_id];
	memcpy(next_node.moves, now_node.moves, sizeof(now_node.moves));
	next_node.moves[now_node.depth] = move;
	next_node.state = now_node.state;
	next_node.state[next_node.blanck_id] = 0;
	next_node.state[now_node.blanck_id] = now_node.state[next_node.blanck_id];
	next_node.hg_val = GetHgVal(next_node);
	return next_node;
}

bool Astart(const vector<short> &state){
	Node now_node;
	now_node.state = state;
	memset(now_node.moves, dir.NOMOVE, sizeof(now_node.moves));
	now_node.depth = 0;
	now_node.hash_val = GetStateHashVal(state, now_node.blanck_id);
	now_node.hg_val = GetHgVal(now_node);

	priority_queue<Node> open;
	open.push(now_node);
	map<ull, int > closed;
	while(!open.empty()){
		now_node = open.top();
		open.pop();
		closed.insert(P(now_node.hash_val, now_node.hg_val));

		if(now_node.hash_val == ans_hash_val){
			memcpy(ans_moves, now_node.moves, sizeof(now_node.moves));
			return true;
		}

		NowNodeNextMoves(now_node);
		for(int i = 0; i < 4; i++){
			if(tmp_moves[i] != dir.NOMOVE){
				Node next_node = Excete(now_node, tmp_moves[i]);
				map<ull, int> :: iterator it = closed.find(next_node.hash_val);
				if(it != closed.end() && next_node.hg_val >= (*it).second){
					continue;
				}
				open.push(next_node);
			}
		}
	}
	return false;
}

void SolvePuzzle(const vector<short> &state){
	if(Astart(state)){
		for(int i = 0; i < kMaxM; i++){
			if(ans_moves[i] == dir.NOMOVE){
				break;
			}else if(ans_moves[i] == dir.LEFT){
				printf("l");
			}else if(ans_moves[i] == dir.RIGTH){
				printf("r");
			}else if(ans_moves[i] == dir.UP){
				printf("u");
			}else if(ans_moves[i] == dir.DOWN){
				printf("d");
			}
		}
		printf("\n");
	}else{
		printf("unsolvable\n");
	}
}

int main(){
	GetManHantTanDist();
	GetHashBase();
	AnsHashVal();


	char tmp_str[5];
	while(~scanf("%s", &tmp_str)){
		vector<short> filed;
		for(int i = 0; i < 9; i++){
			if(i) scanf("%s", tmp_str);
			if(tmp_str[0] >= '1' && tmp_str[0] <= '9'){
				filed.push_back(tmp_str[0] - '0');
			}else{
				filed.push_back(0);
			}

		}
		if(HaveAns(filed)){
			SolvePuzzle(filed);
		}else{
			printf("unsolvable\n");
		}
	}
	return 0;
}