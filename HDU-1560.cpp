/********* IDA* *********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int INF = 0x3f3f3f3f;
const int kMaxLen = 50;
const char mei_char[] = "ACGT";

int n, limit_len;
bool used[50][10];
int used_prt[10][2], need_char_cnt[10][4];
char str[10][10];
int hash_map[90]; //把字符映射成整数

int GetNeedMinLen(){
	int ret = 0;
	for(int i = 0; i < 4; i++){
		int now_need_char_cnt = 0;
		for(int j = 0; j < n; j++){
			now_need_char_cnt = max(now_need_char_cnt, need_char_cnt[j][i]);
		}
		ret += now_need_char_cnt;
	}
	return ret;
}

void InitUsedChar(){
	for(int i = 0; i < n; i++){
		used_prt[i][0] = 0;
		used_prt[i][1] = strlen(str[i]);
		for(int j = 0; j < used_prt[i][1]; j++){
			need_char_cnt[i][hash_map[str[i][j]]]++;
		}
	}
}

bool Jin(int enume_id, int dep){
	bool have_use = false;
	memset(used[dep], false, sizeof(used[dep]));
	for(int i = 0; i < n; i++){
		if(str[i][used_prt[i][0]] == mei_char[enume_id]){
			used[dep][i] = true;
			used_prt[i][0]++;
			need_char_cnt[i][enume_id]--;
			have_use = true;
		}
	}
	return have_use;
}

void Tui(int enume_id, int dep){
	for(int i = 0; i < n; i++){
		if(used[dep][i]){
			used[dep][i] = false;
			used_prt[i][0]--;
			need_char_cnt[i][enume_id]++;
		}
	}
}

bool have_ans;
int IDAstart(int dep){
	int need_len = GetNeedMinLen();
	if(need_len + dep > limit_len) return need_len + dep;
	if(need_len == 0){
		have_ans = true;
		return dep;
	}

	int ret_min_len = INF;
	for(int i = 0; i < 4; i++){
		if(Jin(i, dep)){
            int tmp_len = IDAstart(dep + 1);
            if(have_ans){
                return tmp_len;
            }else{
                Tui(i, dep);
                ret_min_len = min(tmp_len, ret_min_len);
            }
		}
	}
	return ret_min_len;
}

void Solve(){
    have_ans = false;
	InitUsedChar();
	limit_len = GetNeedMinLen();
	while(have_ans == false){
     //  printf("%d\n", limit_len);
		limit_len = IDAstart(0);
	}
	//printf("over\n");
	printf("%d\n", limit_len);
}

int main(){
	hash_map['A'] = 0, hash_map['C'] = 1, hash_map['G'] = 2, hash_map['T'] = 3;

	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%s", str[i]);
		}
		Solve();
	}
	return 0;
}

/*

1
8
AAAAA
CCCCC
TTTTT
GGGGG
CACAC
AGGGA
TTTTT
GAGGA

*/

