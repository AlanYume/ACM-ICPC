/************ 模拟 ****************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

void Copy(int num[24], int tmp[24]){
	for(int i = 0; i < 24; i++) tmp[i] = num[i];
}

void Twist_0(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[0] = num[1];
	tmp_num[1] = num[3];
	tmp_num[3] = num[2];
	tmp_num[2] = num[0];

	tmp_num[22] = num[9];
	tmp_num[23] = num[8];
	tmp_num[9] = num[7];
	tmp_num[8] = num[6];
	tmp_num[7] = num[5];
	tmp_num[6] = num[4];
	tmp_num[5] = num[22];
	tmp_num[4] = num[23];
	Copy(tmp_num, num);
}

void Twist_1(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[0] = num[2];
	tmp_num[2] = num[3];
	tmp_num[3] = num[1];
	tmp_num[1] = num[0];

	tmp_num[22] = num[5];
	tmp_num[23] = num[4];
	tmp_num[5] = num[7];
	tmp_num[4] = num[6];
	tmp_num[6] = num[8];
	tmp_num[7] = num[9];
	tmp_num[8] = num[23];
	tmp_num[9] = num[22];
	Copy(tmp_num, num);
}

//void Twist_2(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[16] = num[17];
//	tmp_num[17] = num[19];
//	tmp_num[19] = num[18];
//	tmp_num[18] = num[16];
//
//	tmp_num[10] = num[12];
//	tmp_num[11] = num[13];
//	tmp_num[12] = num[14];
//	tmp_num[13] = num[15];
//	tmp_num[14] = num[21];
//	tmp_num[15] = num[20];
//	tmp_num[21] = num[10];
//	tmp_num[20] = num[11];
//	Copy(tmp_num, num);
//}
//
//void Twist_3(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[16] = num[18];
//	tmp_num[18] = num[19];
//	tmp_num[19] = num[17];
//	tmp_num[17] = num[16];
//
//	tmp_num[10] = num[21];
//	tmp_num[11] = num[20];
//	tmp_num[21] = num[14];
//	tmp_num[20] = num[15];
//	tmp_num[14] = num[12];
//	tmp_num[15] = num[13];
//	tmp_num[13] = num[11];
//	tmp_num[12] = num[10];
//	Copy(tmp_num, num);
//}

void Twist_4(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[4] = num[5];
	tmp_num[5] = num[11];
	tmp_num[11] = num[10];
	tmp_num[10] = num[4];

	tmp_num[6] = num[16];
	tmp_num[12] = num[18];
	tmp_num[16] = num[20];
	tmp_num[18] = num[22];
	tmp_num[20] = num[0];
	tmp_num[22] = num[2];
	tmp_num[0] = num[6];
	tmp_num[2] = num[12];
	Copy(tmp_num, num);
}

void Twist_5(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[4] = num[10];
	tmp_num[10] = num[11];
	tmp_num[11] = num[5];
	tmp_num[5] = num[4];

	tmp_num[6] = num[0];
	tmp_num[12] = num[2];
	tmp_num[0] = num[20];
	tmp_num[2] = num[22];
	tmp_num[20] = num[16];
	tmp_num[22] = num[18];
	tmp_num[16] = num[6];
	tmp_num[18] = num[12];
	Copy(tmp_num, num);
}

//void Twist_6(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[8] = num[9];
//	tmp_num[9] = num[15];
//	tmp_num[15] = num[14];
//	tmp_num[14] = num[8];
//
//	tmp_num[7] = num[1];
//	tmp_num[13] = num[3];
//	tmp_num[1] = num[21];
//	tmp_num[3] = num[23];
//	tmp_num[21] = num[17];
//	tmp_num[23] = num[19];
//	tmp_num[17] = num[7];
//	tmp_num[19] = num[13];
//	Copy(tmp_num, num);
//}
//
//void Twist_7(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[8] = num[14];
//	tmp_num[14] = num[15];
//	tmp_num[15] = num[9];
//	tmp_num[9] = num[8];
//
//	tmp_num[7] = num[17];
//	tmp_num[13] = num[19];
//	tmp_num[17] = num[21];
//	tmp_num[19] = num[23];
//	tmp_num[21] = num[1];
//	tmp_num[23] = num[3];
//	tmp_num[1] = num[7];
//	tmp_num[3] = num[13];
//	Copy(tmp_num, num);
//}

void Twist_8(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[20] = num[21];
	tmp_num[21] = num[23];
	tmp_num[23] = num[22];
	tmp_num[22] = num[20];

	tmp_num[18] = num[15];
	tmp_num[19] = num[9];
	tmp_num[15] = num[1];
	tmp_num[9] = num[0];
	tmp_num[1] = num[4];
	tmp_num[0] = num[10];
	tmp_num[4] = num[18];
	tmp_num[10] = num[19];
	Copy(tmp_num, num);
}

void Twist_9(int num[24]){
	int tmp_num[24];
	Copy(num, tmp_num);
	tmp_num[20] = num[22];
	tmp_num[22] = num[23];
	tmp_num[23] = num[21];
	tmp_num[21] = num[20];

	tmp_num[18] = num[4];
	tmp_num[19] = num[10];
	tmp_num[4] = num[1];
	tmp_num[10] = num[0];
	tmp_num[1] = num[15];
	tmp_num[0] = num[9];
	tmp_num[15] = num[18];
	tmp_num[9] = num[19];
	Copy(tmp_num, num);
}


//void Twist_10(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[6] = num[7];
//	tmp_num[7] = num[13];
//	tmp_num[13] = num[12];
//	tmp_num[12] = num[6];
//
//	tmp_num[8] = num[17];
//	tmp_num[14] = num[16];
//	tmp_num[17] = num[11];
//	tmp_num[16] = num[5];
//	tmp_num[11] = num[2];
//	tmp_num[5] = num[3];
//	tmp_num[2] = num[8];
//	tmp_num[3] = num[14];
//	Copy(tmp_num, num);
//}
//
//void Twist_11(int num[24]){
//	int tmp_num[24];
//	Copy(num, tmp_num);
//	tmp_num[6] = num[12];
//	tmp_num[12] = num[13];
//	tmp_num[13] = num[7];
//	tmp_num[7] = num[6];
//	
//	tmp_num[8] = num[2];
//	tmp_num[14] = num[3];
//	tmp_num[2] = num[11];
//	tmp_num[3] = num[5];
//	tmp_num[11] = num[17];
//	tmp_num[5] = num[16];
//	tmp_num[17] = num[8];
//	tmp_num[16] = num[14];
//	Copy(tmp_num, num);
//}

int GetNum(int num[24]){
	int result = 0;
	if(num[0] == num[1] && num[0] == num[3] && num[0] == num[2]) result += 1;
	if(num[4] == num[5] && num[4] == num[11] && num[4] == num[10]) result += 1;
	if(num[6] == num[7] && num[6] == num[13] && num[6] == num[12]) result += 1;
	if(num[8] == num[9] && num[8] == num[15] && num[8] == num[14]) result += 1;
	if(num[16] == num[17] && num[16] == num[19] && num[16] == num[18]) result += 1;
	if(num[20] == num[21] && num[20] == num[23] && num[20] == num[22]) result += 1;
	return result;
}

int Solve(int val[24], int n){
	int tmp_ans = GetNum(val);
	if(n > 0){
		if(tmp_ans == 6) return 6;

		int tmp_val[24];

		Copy(val, tmp_val);
		Twist_0(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		Copy(val, tmp_val);
		Twist_1(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		//Copy(val, tmp_val);
		//Twist_2(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		//if(tmp_ans == 6) return 6;


		//Copy(val, tmp_val);
		//Twist_3(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));

		Copy(val, tmp_val);
		Twist_4(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		Copy(val, tmp_val);
		Twist_5(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		//Copy(val, tmp_val);
		//Twist_6(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		//if(tmp_ans == 6) return 6;

		//Copy(val, tmp_val);
		//Twist_7(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));

		Copy(val, tmp_val);
		Twist_8(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		Copy(val, tmp_val);
		Twist_9(tmp_val);
		tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		if(tmp_ans == 6) return 6;

		//Copy(val, tmp_val);
		//Twist_10(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
		//if(tmp_ans == 6) return 6;

		//Copy(val, tmp_val);
		//Twist_11(tmp_val);
		//tmp_ans = max(tmp_ans, Solve(tmp_val, n - 1));
	}
	return  tmp_ans;
}

int main(){
	int n, val[24];

	while(~scanf("%d", &n)){
		for(int i = 0; i < 24; i++) scanf("%d", &val[i]);
		printf("%d\n", Solve(val, n));
	}
	return 0;
}