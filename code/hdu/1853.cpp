/******************** KM ƥ�� ************************/
//��Ϊ�ǻ�����ÿ����ֻ����һ�Σ�����ÿ�������Ⱥͳ��ȶ���1��
//���ÿ���㶼������ͳ��㣬���ڵ�u�����Բ��u��u���� u����㣬u���ǳ��㡣
//���б�(u, v)����u�� -> v����
//������ͼת��Ϊһ������ͼ������ÿ�������Ҫ��һ���������ӣ�ÿ������ҲҪ��һ��������ӣ���ô���Ǿ���Ķ���ͼƥ�����⡣����һ��Ȩֵ�����Ƕ���ͼ����ƥ�����⡣

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