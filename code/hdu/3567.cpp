/******* IDA* ********/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 3;
const int dir[4][2] = {1, 0, 0, -1, 0, 1, -1, 0}; //d?l?r?u
char char_dir[6] = "dlru";

char start_state[16], end_state[16];
int end_postion[16];
char ans_move[200];

inline bool InFiled(int x, int y){
	return (x >= 0 && x < kMaxN && y >= 0 && y < kMaxN);
}

void MakeEndPostion(){
	for(int i = 0; i < kMaxN*kMaxN; i++){
		end_postion[end_state[i] - '0'] = i;
	}
}

inline int Abs(int val){
	return val > 0 ? val : -val;
}

int ChangToInt(char c){
	return c - '0';
}

int GetManHantTamDist(){
	int ret = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(start_state[i] == '9') continue;
		int now_val = ChangToInt(start_state[i]);
		ret += Abs(i / kMaxN - end_postion[now_val] / kMaxN) + Abs(i % kMaxN - end_postion[now_val] % kMaxN);
	}
	return ret;
}

int GetBlankId(){
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(start_state[i] == '9') return i;
	}
}

bool have_ans;
int limit_step;
int IDAstart(int blank_id, int dep, int pre_mov){
	int now_min_step = GetManHantTamDist();
	if(dep + now_min_step > limit_step){
		return dep + now_min_step;
	}else if(now_min_step == 0){
		have_ans = true;
		ans_move[dep] = '\0';
		return dep;
	}else{
		int next_step = kINF;
		for(int i = 0; i < 4; i++){
			if(i + pre_mov == 3) continue;
			int next_x = blank_id / kMaxN + dir[i][0];
			int next_y = blank_id % kMaxN + dir[i][1];
			if(InFiled(next_x, next_y)){
				int next_blank = next_x*kMaxN + next_y;
				swap(start_state[blank_id], start_state[next_blank]);
				ans_move[dep] = char_dir[i];
				int temp_step = IDAstart(next_blank, dep+1, i);
				if(have_ans) return temp_step;
				swap(start_state[blank_id], start_state[next_blank]);
				next_step = min(next_step, temp_step);
			}
		}
		return next_step;
	}
}

void Solve(){
	MakeEndPostion();
	have_ans = false;
	int blank_id = GetBlankId();
	limit_step = GetManHantTamDist();
	while(have_ans == false){
		limit_step = IDAstart(blank_id, 0, 10);
	}
	printf("%d\n", limit_step);
	printf("%s\n", ans_move);
}

int main(){
	//freopen("E:\\data2.out","w",stdout);
	//freopen("E:\\data1.in","r",stdin);
	int test;
	scanf("%d", &test);
	for(int cas = 1; cas <= test; cas++){
		scanf("%s", start_state);
		scanf("%s", end_state);
		for(int j = 0; j < kMaxN*kMaxN; j++){
			if(start_state[j] == 'X') start_state[j] = '9';
			if(end_state[j] == 'X') end_state[j] = '9';
		}
		printf("Case %d: ", cas);
		Solve();
	}
	return 0;
}

/*
1
7536X1284
5318246X7

*/