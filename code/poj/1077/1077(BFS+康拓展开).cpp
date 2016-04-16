/********* BFS（康拓展开 判重）********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int kMaxN = 9;
const int kMaxM = 3628810;
const int kantuoBase[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const int dir[4][2] = {0, -1, -1, 0, 0, 1, 1, 0}; //l, u, r, d

struct Node{
	int x, y, state[kMaxN], kantuo_val;
};

int puzzle[kMaxN] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

bool mark[kMaxM];
int pre[kMaxM];
char ans_move[kMaxM];

int GetKanTuo(int *a){
	int ret = 0;
	for(int i = 0; i < kMaxN; i++){
		int inversion_pair = 0;
		for(int j = i + 1; j < kMaxN; j++){
			if(a[i] > a[j]) inversion_pair++;
		}
		ret += inversion_pair * kantuoBase[kMaxN - i - 1];
	}
	return ret;
}

bool Infiled(int x, int y){
	return (x >= 0 && x < 3 && y >= 0 && y < 3);
}

void BFS(){
	memset(mark, false, sizeof(mark));
	memset(pre, -1, sizeof(pre));
	Node now_sit, next_sit;
	now_sit.x = now_sit.y = 2;
	memcpy(now_sit.state, puzzle, sizeof(puzzle));
	now_sit.kantuo_val = GetKanTuo(puzzle);
	mark[now_sit.kantuo_val] = true;

	queue<Node> que;
	que.push(now_sit);
	while(!que.empty()){
		now_sit = que.front();
		que.pop();
		for(int i = 0; i < 4; i++){
			next_sit.x = now_sit.x + dir[i][0];
			next_sit.y = now_sit.y + dir[i][1];
			if(Infiled(next_sit.x, next_sit.y)){
				memcpy(next_sit.state, now_sit.state, sizeof(now_sit.state));
				swap(next_sit.state[next_sit.x*3 + next_sit.y], next_sit.state[now_sit.x*3 + now_sit.y]);
				next_sit.kantuo_val = GetKanTuo(next_sit.state);
				if(mark[next_sit.kantuo_val] == false){
					mark[next_sit.kantuo_val] = true;
					pre[next_sit.kantuo_val] = now_sit.kantuo_val;
					switch(i){
						case 0:
							ans_move[next_sit.kantuo_val] = 'r'; break;
						case 1:
							ans_move[next_sit.kantuo_val] = 'd'; break;
						case 2:
							ans_move[next_sit.kantuo_val] = 'l'; break;
						case 3:
							ans_move[next_sit.kantuo_val] = 'u'; break;
					}
					que.push(next_sit);
				}
			}
		}
	}
}

int main(){
	char tmp_str[3];
	BFS();
	while(~scanf("%s", tmp_str)){
		for(int i = 0; i < 9; i++){
			if(i) scanf("%s", tmp_str);
			puzzle[i] = tmp_str[0] == 'x' ? 9 : tmp_str[0] - '0';
		}
		int tmp_kan_tuo_val = GetKanTuo(puzzle);
		if(mark[tmp_kan_tuo_val] == false){
			printf("unsolvable\n");
		}else{
			do{
				printf("%c", ans_move[tmp_kan_tuo_val]);
				tmp_kan_tuo_val = pre[tmp_kan_tuo_val];
			}while(pre[tmp_kan_tuo_val] != -1);
			printf("\n");
		}
	}
	return 0;
}

