/********* 栈模拟（递归） ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stack>
using namespace std;

int ans_val;
char str[2000];


int main(){
	while(~scanf("%d", &ans_val)){

		int l_cnt, r_cnt;
		int len = 0;
		do{
			gets(str + len);
			len = strlen(str);
			l_cnt = 0, r_cnt = 0;
			for(int i = 0; i < len; i++){
				if(str[i] == '('){
					l_cnt += 1;
				}else if(str[i] == ')'){
					r_cnt += 1;
				}
			}
		}while(l_cnt != r_cnt);

		stack<int> sk;
		len = strlen(str);
		int pos = 0, tmp_sum = 0;

		bool have_ans = false;
		int no_val = 0;

		int last_val = -1; //用于最后的特判
		while(pos < len){
			if(str[pos] == ' '){
				pos++;
			}else if(str[pos] == '('){
				pos++;
				no_val += 1;

				int tmp_val = 0;
				bool is_fu = false;
				if(str[pos] == '-'){
					pos++;
					is_fu = true;
				}
				while(str[pos] >= '0' && str[pos] <= '9'){
					tmp_val = tmp_val * 10 + str[pos++] - '0';
					no_val = 0;
				}
				if(is_fu){
					tmp_val = -tmp_val;
				}

				last_val = tmp_val;
				sk.push(tmp_val);
				tmp_sum += tmp_val;
			}else if(str[pos] == ')'){
				pos++;
				if(no_val == 2){
					no_val = 0;
					if(tmp_sum == ans_val){
						have_ans = true;
					}
				}
				tmp_sum -= sk.top();
				sk.pop();
			}
		}

		if(have_ans == false && ans_val == 0 && l_cnt == 1 && last_val == 0){
			have_ans = true;
		}

		printf("%s\n", have_ans ? "yes" : "no");
	}
	return 0;
}