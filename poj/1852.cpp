#include <iostream>
#include <cstdio>
using namespace std;

const int kMaxN = 1000010;
int len, n, sit[kMaxN];

int main(){
	int cas;
	scanf("%d", &cas);
	while(cas--){
		scanf("%d %d", &len, &n);
		for(int i = 0; i < n; i++) scanf("%d", &sit[i]);
		int min_ans = 0, max_ans = 0;
		for(int i = 0; i  < n; i++){
			min_ans = max(min_ans, min(len - sit[i], sit[i]));
			max_ans = max(max_ans, max(len - sit[i], sit[i]));
		}
		printf("%d %d\n", min_ans, max_ans);
	}
	return 0;
}
