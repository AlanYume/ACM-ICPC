#include <iostream>
#include <cstdio>
using namespace std;

const int kMaxN = 110;

int n, m;
char filed[kMaxN][kMaxN];

void Dfs(int x, int y){
	filed[x][y] = '.';
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			int nx = x + i, ny = y + j;
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && filed[nx][ny] == 'W') Dfs(nx, ny);
		}
	}
}

int Solve(){
	int cnt = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; filed[i][j]; j++){
			if(filed[i][j] == 'W'){
				cnt++;
				Dfs(i, j);
			}
		}	
	}
	return cnt;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", filed[i]);
	int ans = Solve();
	printf("%d\n", ans);
	return 0;
}
