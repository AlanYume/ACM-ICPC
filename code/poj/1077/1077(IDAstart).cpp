/******** IDA* *******/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 3;
const int dir[4][2] = {0, -1, -1, 0, 1, 0, 0, 1}; //l, u, d, r;
char char_dir[6] = "ludr";

bool have_ans;
int puzzle[kMaxN*kMaxN];
char ans_move[110];
int limit_step;

inline int Abs(int val){
	return val > 0 ? val : -val;
}

inline bool InPuzzle(int x, int y){
	return (x >= 0 && x < kMaxN && y >= 0 && y < kMaxN);
}

int EvenODDJudge(){
	int ret = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(puzzle[i]){
			for(int j = i+1; j < kMaxN*kMaxN; j++){
				if(puzzle[j] && puzzle[i] > puzzle[j]){
					ret++;
				}
			}
		}	
	}
	return ret&1;
}

int GetManHanTanDist(){
	int ret = 0;
	for(int i = 0; i < kMaxN*kMaxN; i++){
		if(puzzle[i]){
			ret += Abs((puzzle[i]-1)/kMaxN - i/kMaxN) + Abs((puzzle[i]-1)%kMaxN - i%kMaxN);
		}
	}
	return ret;
}

int IDAstart(int x, int y, int dep, int pre_dir){
	int h_step = GetManHanTanDist();
	if(dep + h_step > limit_step) return dep + h_step;
	if(h_step == 0){
		have_ans = true;
		ans_move[dep] = '\0';
		return dep;
	}

	int step = kINF;
	for(int i = 0; i < 4; i++){
		if(i + pre_dir == 3) continue;
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if(InPuzzle(nx, ny)){
			ans_move[dep] = char_dir[i];
			swap(puzzle[nx*kMaxN+ny], puzzle[x*kMaxN+y]);
			int tmp_step = IDAstart(nx, ny, dep+1, i);
			if(have_ans) return tmp_step;
			step = min(step, tmp_step);
			swap(puzzle[x*kMaxN+y], puzzle[nx*kMaxN+ny]);
		}
	}
	return step;
}

void Solve(int row_id){
	if(EvenODDJudge()){
		printf("unsolvable\n");
	}else{
		have_ans = false;
		limit_step = GetManHanTanDist();
		while(!have_ans && limit_step <= 100){
			limit_step = IDAstart(row_id / kMaxN, row_id % kMaxN, 0, -10);	
		}
		if(have_ans){
			printf("%s\n", ans_move);
		}else{
			printf("unsolvable\n");
		}
	}
}

int main(){
	char tmp_str[5];
	while(~scanf("%s", tmp_str)){
		int row_id;
		for(int i = 0; i < kMaxN*kMaxN; i++){
			if(i) scanf("%s", tmp_str);
			if(tmp_str[0] >= '0' && tmp_str[0] <= '9'){
				puzzle[i] = tmp_str[0]-'0';
			}else{
				puzzle[i] = 0;
				row_id = i;
			}
		}
		Solve(row_id);
	}
	return 0;
}
