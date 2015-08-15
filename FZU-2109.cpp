/***********  数位DP + 记忆化搜索  *****************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 10 + 6;

int digit[kMaxN];
int dp[kMaxN][10][2]; //dp[i][j][k]: 当前是第i位，前一位的值为j，从没有前导0开始算是奇数位还是偶数位
                      //在没有限制条件下可以达到的最大符合Mountain Number数的个数

//求【0，val】间Mountain Number数的个数
//now_sit:当前处理的位置；
//pre_val:前一位使用的数字;
//now_odd_even:从非前导零位开始，当前为属于奇数位（true）还是偶数位（false）
//pre_zero_sit:标记当前位是否仍是前导零位
//be_limited:标记当前可以构成的数是否仍然被digit位限制
int Dfs(int now_sit, int pre_val, bool now_odd_even, bool pre_zero_sit, bool be_limited){
	if(now_sit < 0) return 1;
	if(be_limited == false && dp[now_sit][pre_val][now_odd_even] != -1){ //没被限制，且有值，直接返回
		return dp[now_sit][pre_val][now_odd_even];
	}

	int res = 0;
	int now_max_val = be_limited ? digit[now_sit] : 9;
	for(int i = 0; i <= now_max_val; i++){
		if(i == 0 && pre_zero_sit == true){ //当前为仍被限制，且当前位仍使用零填充
			res += Dfs(now_sit - 1, 9, false, true, false);
		}else if(now_odd_even && i >= pre_val){ //当前位为奇数位，则能填充该位的数必须 大于等于 前一个数pre_val
			res += Dfs(now_sit - 1, i, !now_odd_even, false, be_limited && i == now_max_val);
		}else if(!now_odd_even && i <= pre_val){ //当前位为偶数位，则能填充该位的数必须 小于等于 前一个数pre_val
			res += Dfs(now_sit - 1, i, !now_odd_even, false, be_limited && i == now_max_val);
		}
	}
	if(be_limited == false){ //如果从该位开始，之后的数值全部没有约束，则其值存入dp数组，记忆化
		dp[now_sit][pre_val][now_odd_even] = res;
	}
	return res;
}

//计算【0，val】间的符合Mountain的数的个数
int Cal(int val){
	int pos = 0;
	while(val){
		digit[pos++] = val % 10;
		val /= 10;
	}
	//Dfs(int now_sit, int pre_val, bool now_odd_even, bool pre_zero_sit, bool be_limited)
	//pre_val = 9，now_odd_even = false, pre_zero_sit = true, be_limited = true
	//因为左边第一个非零数为0号位，所以其值的范围可以是【1，digit[now_sit]】，pre_val 存9， 使now_max_vla只被digit[now_sit]约束，
	//now_odd_even = false，表示当前为就是偶数位， 方便处理
	return Dfs(pos - 1, 9, false, true, true);
}

int main(){
	int test;
	scanf("%d", &test);

	memset(dp, -1, sizeof(dp));
	while(test--){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", Cal(r) - Cal(l - 1));
	}

	return 0;
}
