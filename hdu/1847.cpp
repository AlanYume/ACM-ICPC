/*********** Sg函数 ************/
//利用动态规划计算grundy
#include <iostream>
#include <cstring>
#include <string>
#include <set>
using namespace std;

const int kMaxN = 1000 + 16;

int n;
int grund[kMaxN];

void GetGrund(){
	grund[0] = 0;
	for(int j = 1; j <= 1000; j++){
		set<int> s;
		for(int i = 1; ; i *= 2){
			if(i <= j){
				s.insert(grund[j - i]);
			}else{
				break;
			}
		}
		int g = 0;
		while(s.count(g) != 0) g++;
		grund[j] = g;
	}
}

int main(){
	GetGrund();
	while(~scanf("%d", &n)){
		printf("%s\n", grund[n] ? "Kiki" : "Cici");
	}
	return 0;
}