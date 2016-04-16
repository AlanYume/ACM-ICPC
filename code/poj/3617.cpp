#include <iostream>
#include <cstdio>
using namespace std;

const int kMaxN = 2010;

int n;
char str[kMaxN];

void Solve(){
	int a  = 0, b = n - 1, cnt = 0;
	while(a <= b){
		bool left = false;
		for(int i = 0; a + i <= b; i++){
			if(str[a + i] < str[b - i]){
				left = true;
				break;
			}else if(str[a + i] > str[b - i]){
				left = false;
				break;
			}
		}
		if(left){
			putchar(str[a++]);
		}else{
			putchar(str[b--]);
		}
		cnt++;
		if(cnt % 80 == 0) putchar('\n');
	}
	if(cnt % 80) putchar('\n');
}

int main(){
	scanf("%d\n", &n);
	for(int i = 0; i < n; i++) scanf("%c\n", &str[i]);
	str[n] = '\0';
	Solve();
	return 0;
}
