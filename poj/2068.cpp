/***********状态递推博弈 ***************/
//根据必胜态、必败态定义，对拍，判断当前状态的输赢
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

const int kMaxPerson = 20 + 4;
const int kMaxN = (1 << 13) + 16;

int n, s;
int players[kMaxPerson];
int win[kMaxPerson][kMaxN];

//注意：这里只能使用记忆话，因为取走最后一颗石子的人还是不确定的，能确定的是对0号人在游戏开始时第一个取
int Solve(int person_id, int ston_cnt){
    if(win[person_id][ston_cnt] != -1) return win[person_id][ston_cnt];
    if(ston_cnt == 0) return win[person_id][ston_cnt] = 1;
    win[person_id][ston_cnt] = 0;
    for(int i = 1; i <= players[person_id] && i <= ston_cnt; i++){
        if(Solve((person_id + 1) % n, ston_cnt - i) == false){
            return win[person_id][ston_cnt] = 1;
        }
    }
    return win[person_id][ston_cnt];
}

int main(){
	while(~scanf("%d", &n)){
		if(n == 0) break;
		n <<= 1;

		scanf("%d", &s);
		for(int i = 0; i < n; i++){
			scanf("%d", &players[i]);
		}

		memset(win, -1, sizeof(win));
		printf("%d\n", Solve(0, s));
	}
	return 0;
}