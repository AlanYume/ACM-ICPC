/*********** KM����ͼ�����Ȩƥ�䣨����ƥ��Ĭ�ϱߣ� ******************/
//��Ϊ����Ҫ�䶯��С�����Զ���ԭ�ƻ��еı�Ҫ��һЩ�����չˣ�ʹ������ƥ��ʱ����������ʹ��ԭ�ƻ��ıߣ������仯��������С���Ҳ���Ӱ��ԭƥ�䡣
//�������˼�룬���ǿ��԰�ÿ���ߵ�Ȩֵ����k����kҪ����n��Ȼ���ԭ�ƻ��ı߶�+1������ȫ�������������ϸ˵��һ�¡�
//ȫ���߶�������k��������k��n���������������������ƥ�����k�������Ȩֵ��ֻҪ����k�Ϳ��Եõ����Ȩֵ��ʵ��ԭ�ƻ��ı߼�1����������ÿ��ѡ���ʱ����Щ��� �������ƣ��ͻ�����ѡ����Щ�ߡ�����ԭ�ƻ���h���߱�ѡ��������ƥ���У�����������Ȩֵ����k�������Ȩֵ+k��ԭ�ƻ���ÿ���߶�+1��������k����n����������أ����Ƿ��ּ���ԭ�ƻ��ı�ȫ����ƥ���У�ֻ������n����n<k,���Գ���k�󲻻�Ӱ������ƥ������Ȩֵ֮�ͣ�Ȼ�����Ƕ�kȡ�࣬�����õõ������ԭ�ƻ��ıߵĸ�������ʱ������ֻ��Ҫ���ܵ���-�����ԭ�ƻ��ĵ������Ϳ��������С�䶯���ˡ�
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 1000000;
const int kMaxN = 50 + 6;

int nx, ny, edge[kMaxN][kMaxN];
int lx[kMaxN], ly[kMaxN], slack[kMaxN], link_m[kMaxN];
bool visit_x[kMaxN], visit_y[kMaxN];

bool Dfs(int x){
	visit_x[x] = true;
	for(int y = 0; y < ny; y++){
		if(visit_y[y] == true) continue;

		int tmp_val = lx[x] + ly[y] - edge[x][y];
		if(tmp_val == 0){
			visit_y[y] = true;
			if(link_m[y] == -1 || Dfs(link_m[y]) == true){
				link_m[y] = x;
				return true;
			}
		}else if(slack[y] > tmp_val){
			slack[y] = tmp_val;
		}
	}
	return false;
}

int KM(){
	memset(link_m, -1, sizeof(link_m));
	memset(ly, 0, sizeof(ly));
	for(int i = 0; i < nx; i++){
		lx[i] = -kINF;
		for(int j = 0; j < ny; j++){
			lx[i] = max(lx[i], edge[i][j]);
		}
	}

	for(int x = 0; x < nx; x++){
		for(int j = 0; j < ny; j++){
			slack[j] = kINF;
		}
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

	int res = 0;
	for(int j = 0; j < ny; j++){
		if(link_m[j] != -1){
			res += edge[link_m[j]][j];
		}
	}
	return res;
}

int main(){
	while(~scanf("%d %d", &nx, &ny)){
		int k = nx + 3;
		for(int i = 0; i < nx; i++){
			for(int j = 0; j < ny; j++){
				int w;
				scanf("%d", &w);
				edge[i][j] = w * k;
			}
		}

		int now_ans = 0;
		for(int i = 0; i < nx; i++){
			int v;
			scanf("%d", &v);
			now_ans += edge[i][v - 1];
			edge[i][v - 1] += 1;
		}
		now_ans /= k;

		int change_ans = KM();
		int x = nx - change_ans % k;
		int y = change_ans / k - now_ans;
		printf("%d %d\n", x, y);
	}
	return 0;
}