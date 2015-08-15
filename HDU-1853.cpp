/******************** KM 匹配 ************************/
//因为是环，且每个点只访问一次，所以每个点的入度和出度都是1。
//如果每个点都拆成入点和出点，对于点u，可以拆成u和u’， u是入点，u’是出点。
//若有边(u, v)，则u’ -> v连边
//则整个图转化为一个二分图。由于每个入点需要找一个出点连接，每个出点也要找一个入点连接，那么就是经典的二分图匹配问题。加上一个权值，就是二分图最优匹配问题。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
	using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 100 + 16;

int n, m;
int nx, ny, edge[kMaxN][kMaxN];
int lx[kMaxN], ly[kMaxN], link_m[kMaxN], slack[kMaxN];
bool visit_x[kMaxN], visit_y[kMaxN];

bool Dfs(int x){
	visit_x[x] = true;
	for(int j = 0; j < ny; j++){
		if(visit_y[j] == true) continue;
		int tmp_val = lx[x] + ly[j] - edge[x][j];
		if(tmp_val == 0){
			visit_y[j] = true;
			if(link_m[j] == -1 || Dfs(link_m[j])){
				link_m[j] = x;
				return true;
			}
		}else if(slack[j] > tmp_val){
			slack[j] = tmp_val;
		}
	}
	return false;
}

int KM(){
	nx = ny = n;
	memset(link_m, -1,sizeof(link_m));
	memset(ly, 0, sizeof(ly));
	for(int i = 0; i < nx; i++){
		lx[i] = -kINF;
		for(int j = 0; j < ny; j++){
			lx[i] = max(lx[i], edge[i][j]);
		}
	}

	for(int x = 0; x < nx; x++){
		fill(slack, slack + sizeof(slack) / sizeof(int), kINF);
		while(true){
			memset(visit_x, false, sizeof(visit_x));
			memset(visit_y, false, sizeof(visit_y));
			if(Dfs(x) == true) break;

			int min_d = kINF;
			for(int j = 0; j < ny; j++){
				if(visit_y[j] == false && min_d > slack[j]){
					min_d = slack[j];
				}
			}
			for(int i = 0; i < nx; i++){
				if(visit_x[i] == true) lx[i] -= min_d;
			}
			for(int j = 0; j < ny; j++){
				if(visit_y[j] == true){
					ly[j] += min_d;
				}else{
					slack[j] -= min_d;
				}
			}
		}
	}

	int ans = 0;
	for(int j = 0; j <ny; j++){
		ans += edge[link_m[j]][j];
		if(edge[link_m[j]][j] == -kINF)
			return 1;
	}
	return ans;
}

int main(){
	while(~scanf("%d %d", &n, &m)){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				edge[i][j] = -kINF;
			}
		}

		for(int i = 0; i < m; i++){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			if(-w > edge[u - 1][v - 1]) edge[u - 1][v - 1] = -w;
		}

		int ans = KM();
		printf("%d\n", -ans);
	}
	return 0;
}