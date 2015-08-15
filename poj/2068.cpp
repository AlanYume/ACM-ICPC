/***********״̬���Ʋ��� ***************/
//���ݱ�ʤ̬���ذ�̬���壬���ģ��жϵ�ǰ״̬����Ӯ
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

//ע�⣺����ֻ��ʹ�ü��仰����Ϊȡ�����һ��ʯ�ӵ��˻��ǲ�ȷ���ģ���ȷ�����Ƕ�0��������Ϸ��ʼʱ��һ��ȡ
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