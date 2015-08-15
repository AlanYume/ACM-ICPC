/************ KMP *************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int kINF = 0x3f3f3f;
const int kMaxStrLen = 1000000 + 16;

char str[3][kMaxStrLen];
int len[3];
int next_m[3][kMaxStrLen];

inline void GetNext(int id){
	next_m[id][0] = -1;
	for(int i = 1, j = -1; i < len[id]; i++){
		while(j >= 0 && str[id][i] != str[id][j + 1]) j = next_m[id][j];
		if(str[id][i] == str[id][j + 1]) j++;
		next_m[id][i] = j;
	}
}

//原串 strpid_yuan], 模式串 str[id_cmp]
inline int KMP(int id_yuan, int id_cmp){
	GetNext(id_cmp);
	
	int len_yuan = len[id_yuan];
	int len_cmp = len[id_cmp];

	for(int i = 0, j = 0; true; i++){
		if(j == len_cmp || i == len_yuan) return j;
		while(j > 0 && str[id_yuan][i] != str[id_cmp][j]) j = next_m[id_cmp][j - 1] + 1;
		if(str[id_yuan][i] == str[id_cmp][j]) j++;
	}
}

inline void InitAllNext(){
	for(int i = 0; i < 3; i++) GetNext(i);
}

void GetStrLen(){
	for(int i = 0; i < 3; i++) len[i] = strlen(str[i]);
}

int Solve(){
	GetStrLen();
	InitAllNext();

	int ans = kINF;

	//全排列3个字符串顺序,计算最大可重叠的长度
	int num[3] = {0, 1, 2};
	do{
		int overlap = KMP(num[0], num[1]);
		int tmp = len[num[0]] + len[num[1]] - overlap;
		if(overlap == len[num[1]]){
			tmp = tmp + len[num[2]] - KMP(num[0], num[2]);
		}else{
			tmp = tmp + len[num[2]] - KMP(num[1], num[2]);
		}
		ans = min(ans, tmp);
	}while(next_permutation(num, num + 3));

	return ans;
}

int main(){
	scanf("%s %s %s", str[0], str[1], str[2]);
	printf("%d\n", Solve());
	return 0;
}