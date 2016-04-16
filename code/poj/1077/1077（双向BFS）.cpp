/********* 双向搜索 **********/
#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

const int kMaxN = 9;
const int kMaxStatNodeSize = 3628810;
const int Dir[][2] = {0, -1, -1, 0, 0, 1, 1, 0}; //l, u, r, d
const int KangBase[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

struct StatNode{
	int blank_x, blank_y;
	char state_m[kMaxN+2];

	void MakeVal(const StatNode &node){
		blank_x = node.blank_x;
		blank_y = node.blank_y;
		memcpy(state_m, node.state_m, sizeof(state_m));
	}

	static bool InFiled(int x, int y){
		return (x >= 0 && x < 3 && y >= 0 && y < 3);
	}

	//在为StatNode赋值前先判断blank是否出界
	bool MakeStateVal(const StatNode &pre_state, int mov_id){
		blank_x = pre_state.blank_x + Dir[mov_id][0];
		blank_y = pre_state.blank_y + Dir[mov_id][1];

		if(InFiled(blank_x, blank_y) == false) return false;

		memcpy(state_m, pre_state.state_m, sizeof(state_m));
		swap(state_m[blank_x*3 + blank_y], state_m[pre_state.blank_x*3 + pre_state.blank_y]);
		return true;
	}
};

StatNode stat_node[kMaxStatNodeSize];
int mark[kMaxStatNodeSize];
int pre_kangtuo[kMaxStatNodeSize];
char ans_move[kMaxStatNodeSize];

int GetKangTuoVal(char *arr){
	int ret = 0;
	for(int i = 0; i < kMaxN; i++){
		int investion_pair = 0;
		for(int j = i + 1; j < kMaxN; j++){
			if(arr[i] > arr[j]) investion_pair++;
		}
		ret += investion_pair * KangBase[8 - i];
	}
	return ret;
}

int GetInvetionPair(char *arr){
	int invertion_pair = 0;
	for(int i = 0; i < kMaxN; i++){
		if(arr[i] != '9'){
			for(int j = i + 1; j < kMaxN; j++){
				if(arr[i] > arr[j]) invertion_pair++;
			}
		}
	}
	return invertion_pair;
}

bool Judge2(char *arr){
	int used[10] = {0};
	for(int i = 0; i < kMaxN; i++){
		used[arr[i] - '0']++;
	}
	for(int i = 1; i <= 9; i++){
		if(used[i] != 1) return false;
	}
	return true;
}

char GetDir(int mov, int oper_que){
	if (oper_que){
		switch (mov){
		case 0: return 'r';
		case 1:	return 'd';
		case 2: return 'l';
		case 3: return 'u';
		}
	}
	else{
		switch (mov){
		case 0: return 'l';
		case 1:	return 'u';
		case 2: return 'r';
		case 3: return 'd';
		}
	}
}

void Print1(int kangval){
	if(pre_kangtuo[kangval] != -1){
		Print1(pre_kangtuo[kangval]);
		printf("%c", ans_move[kangval]);
	}
}

void Print2(int kangval){
	if(pre_kangtuo[kangval] != -1){
		printf("%c", ans_move[kangval]);
		Print2(pre_kangtuo[kangval]);
	}
}

bool BidirectionalSearch(StatNode node1, StatNode node2){
	memset(mark, 0, sizeof(mark));
	int kangtuo1 = GetKangTuoVal(node1.state_m);
	int kangtuo2 = GetKangTuoVal(node2.state_m);
	
	mark[kangtuo1] = 1; mark[kangtuo2] = 2;
	pre_kangtuo[kangtuo1] = pre_kangtuo[kangtuo2] = -1;
	stat_node[kangtuo1].MakeVal(node1);
	stat_node[kangtuo2].MakeVal(node2);


	queue<int> que[2]; //que[0] 正搜， que[1] 反搜
	que[0].push(kangtuo1);
	que[1].push(kangtuo2);
	while(que[0].size() && que[0].size()){
		int oper_que; //搜索操作队列
		if(que[0].size() > que[1].size()){
			oper_que = 1;
		}else{
			oper_que = 0;
		}

		int now_kang_val = que[oper_que].front();
		que[oper_que].pop();
		for(int i = 0; i < 4; i++){
			StatNode next_node;
			if(next_node.MakeStateVal(stat_node[now_kang_val], i)){
				int next_kangval = GetKangTuoVal(next_node.state_m);
				if(mark[next_kangval] == 0){
					mark[next_kangval] = oper_que + 1;
					pre_kangtuo[next_kangval] = now_kang_val;
					ans_move[next_kangval] = GetDir(i, oper_que);
					stat_node[next_kangval].MakeVal(next_node);
					que[oper_que].push(next_kangval);
				}else if(mark[next_kangval] != oper_que + 1){
					if(oper_que) swap(now_kang_val, next_kangval);
					Print1(now_kang_val);
					printf("%c", GetDir(i, oper_que));
					Print2(next_kangval);
					printf("\n");
					return true;
				}
			}
		}
	}
	return false;
}

void Solve(StatNode statnode1){
	int statnode1_kangval = GetKangTuoVal(statnode1.state_m);
	if(statnode1_kangval == 0){
		printf("\n");
		return;
	}

	if((GetInvetionPair(statnode1.state_m) & 1) || Judge2(statnode1.state_m) == false){
		printf("unsolvable\n");
	}else{
		StatNode statenode2;
		statenode2.blank_x = statenode2.blank_y = 2;
		memcpy(statenode2.state_m, "123456789", sizeof(statenode2.state_m));

		if(BidirectionalSearch(statnode1, statenode2) == false){
			printf("unsolvable\n");
		}
	}
}

int main(){
	char str_tmp[3];
	while(~scanf("%s", str_tmp)){
		StatNode tmp_state;
		for(int i = 0; i < kMaxN; i++){
			if(i) scanf("%s", str_tmp);
			if(str_tmp[0] == 'x'){
				tmp_state.state_m[i] = '9';
				tmp_state.blank_x = i / 3;
				tmp_state.blank_y = i % 3;
			}else{
				tmp_state.state_m[i] = str_tmp[0];
			}
		}
		Solve(tmp_state);
	}
	return 0;
}