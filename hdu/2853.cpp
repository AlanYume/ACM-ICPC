/*********** KM二部图，最大权匹配（优先匹配默认边） ******************/
//因为我们要变动最小，所以对在原计划中的边要有一些特殊照顾，使得最优匹配时，尽量优先使用原计划的边，这样变化才能是最小的且不会影响原匹配。
//根据这个思想，我们可以把每条边的权值扩大k倍，k要大于n。然后对原计划的边都+1。精华全在这里。我们来详细说明一下。
//全部边都扩大了k倍，而且k比n大，这样，我们求出的最优匹配就是k倍的最大权值，只要除以k就可以得到最大权值。实现原计划的边加1，这样，在每次选择边时，这些变就 有了优势，就会优先选择这些边。假如原计划的h条边被选入了最优匹配中，这样，最优权值就是k倍的最大权值+k（原计划的每条边都+1）。但是k大于n的用意何在呢？我们发现假如原计划的边全部在匹配中，只会增加n，又n<k,所以除以k后不会影响最优匹配的最大权值之和，然后我们对k取余，就正好得到加入的原计划的边的个数。这时，我们只需要用总点数-加入的原计划的点数，就可以求得最小变动数了。
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