#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int kMaxN = 20010;

int n, woods[kMaxN];

void Solve()
{
	ll ans = 0;
	while(n > 1){
		int min1 = 0, min2 = 1;
		if(woods[min1] > woods[min2]) swap(min1, min2);
		for(int i = 2; i < n; i++){
			if(woods[i] < woods[min1]){
				min2 = min1;
				min1 = i;
			}else if(woods[i] < woods[min2]){
				min2 = i;
			}
		}
		//将两块木板合并
		int t = woods[min1] + woods[min2];
		ans += t;
		if(min1 == n - 1) swap(min1, min2);
		woods[min1] = t;
		woods[min2] = woods[n - 1];
		n--;
	}
	printf("%lld\n", ans);
}

int main()
{
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; i++) scanf("%d", &woods[i]);
		Solve();
	}
	return 0;
}
