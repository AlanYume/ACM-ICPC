#include <iostream>
#include <cstdio>
using namespace std;

const int kMaxN = 50010;
const int kMaxK = 100010;

int n, k, t[kMaxK], x[kMaxK], y[kMaxK];
int par[3 * kMaxN], rank[3 * kMaxN];

void InitBin(){
	for(int i = 0; i < 3*n; i++){
		par[i] = i;
		rank[i] = 0;
	}
}

int FindBin(int x){
	if(par[x] == x){
		return x;
	}else{
		return par[x] = FindBin(par[x]);
	}
}

void UniteBin(int x, int y){
	x = FindBin(x);
	y = FindBin(y);
	if(x == y) return;
	if(rank[x] < rank[y]){
		par[x] = y;
	}else{
		par[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}

bool SameBin(int x, int y){
	return FindBin(x) == FindBin(y);
}

void Solve(){
	InitBin();
	int wrong_cnt = 0;
	for(int i = 0; i < k; i++){
		int t_now = t[i], x_now = x[i] - 1, y_now = y[i] - 1;
		if(x_now < 0 || x_now >= n || y_now < 0 || y_now >= n){
			wrong_cnt++;
			continue;
		}
		if(t_now == 1){
			if(SameBin(x_now, y_now + n) || SameBin(x_now, y_now + 2*n)){
				wrong_cnt++;
			}else{
				UniteBin(x_now, y_now);
				UniteBin(x_now + n, y_now + n);
				UniteBin(x_now + 2*n, y_now + 2*n);
			}
		}else{
			if(SameBin(x_now, y_now) || SameBin(x_now, y_now + 2*n)){
				wrong_cnt++;
			}else{
				UniteBin(x_now, y_now + n);
				UniteBin(x_now + n, y_now + 2*n);
				UniteBin(x_now + 2*n, y_now);
			}
		}
	}
	printf("%d\n", wrong_cnt);
}

void Read(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < k; i++) scanf("%d %d %d", &t[i], &x[i], &y[i]);
}

int main(){
	Read();
	Solve();
	return 0;
}
