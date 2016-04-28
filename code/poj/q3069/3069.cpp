#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int kMaN = 1010;

int r, n, sit[kMaN];

void Solve(){
	sort(sit, sit + n);
	int i = 0, ans = 0;
	while(i < n){
		int s = sit[i++];
		while(i < n && sit[i] <= s + r) i++; //被选取的点的左区间
		int p = sit[i - 1]; //被选取的点
		while(i < n && sit[i] <= p + r) i++; //被选取的点的右区间
		ans++;
	}
	printf("%d\n", ans);
}

bool Read(){
	scanf("%d %d", &r, &n);
	if(r == -1 && n == -1) return false;
	for(int i = 0; i < n; i++) scanf("%d", &sit[i]);
	return true;
}

int main()
{
	while(Read()){
		Solve();
	}
	return 0;
}
