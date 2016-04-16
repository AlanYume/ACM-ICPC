/************ 贪心 + 模拟 *************/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

const int kMaxStrLen = 100000 + 16;
const int kMaxUnt = 1000 + 16;

struct Unit{
	int coefficient;
	bool pre; //pre =true:a在加号后面
	bool operator < (const Unit & tmp_u) const{
		return coefficient < tmp_u.coefficient;
	}
};

int a;
char str[kMaxStrLen];
int u_cnt;
Unit unts[kMaxUnt];

int main(){
	scanf("%d", &a);
	scanf("%s", str);

	int len = strlen(str);

	u_cnt = 0;
	for(int i = 0; i < len; i += 3){
		int fu = 1;
		if(str[i] == '-'){
			fu = -1;
			i++;
		}else if(str[i] == '+' && ( (i + 1 < len && str[i + 1] != '+') || (i + 2 < len && str[i + 1] == '+' && str[i + 2] == '+') ) ){
			fu = 1;
			i++;
		}

		bool have_num = false;
		int tmp_val = 0;
		while(i < len && str[i] >= '0' && str[i] <= '9'){
			have_num = true;
			tmp_val = tmp_val * 10 + str[i] - '0';
			i++;
		}

		if(have_num == false){
			tmp_val = 1;
		}

		unts[u_cnt].coefficient = fu * tmp_val;

		if(i < len && str[i] == '*'){
			i++;
		}
		if(i < len && str[i] == 'a'){
			unts[u_cnt].pre = false;
		}else{
			unts[u_cnt].pre = true;
		}
		u_cnt ++;
	}

	sort(unts, unts + u_cnt);


	int ans = 0;
	for(int i = 0; i < u_cnt; i++){
		ans += unts[i].coefficient * a;
		if(unts[i].pre == true){
			ans += unts[i].coefficient;
		}
		a++;
	}

	printf("%d\n", ans);

	return 0;
}
