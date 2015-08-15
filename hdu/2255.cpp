/************  KM匹配算法求解 最大权匹配（保证是完美匹配） *******************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 300 + 16;

int n, nx, ny;
int edge[kMaxN][kMaxN];
int link[kMaxN], lx[kMaxN], ly[kMaxN], slack[kMaxN];
bool visit_X[kMaxN], visit_Y[kMaxN];

bool Dfs(int x){ //类匈牙利算法（Hungary）
	visit_X[x] = true;
	for(int y = 0; y < ny; y++){
		if(visit_Y[y] == true) continue;
		int tmp_val = lx[x] + ly[y] - edge[x][y];
		if(tmp_val == 0){ //可行边
			visit_Y[y] = true;
			if(link[y] == -1 || Dfs(link[y])){
				link[y] = x;
				return true;
			}
		}else if(slack[y] > tmp_val){ //交错边
			slack[y] = tmp_val;
		}
	}
	return false;
}

int KM(){
	nx = ny = n;
	memset(link, -1, sizeof(link));
	for(int x = 0; x < nx; x++){
		lx[x] = -kINF;
		for(int y = 0; y < ny; y++){ //lx[x] 取边相连边权的最大值
			lx[x] = max(lx[x], edge[x][y]);
		}
	}
	memset(ly, 0, sizeof(ly)); //ly[y] 取边权值 0

	for(int x = 0; x < nx; x++){ //为点x寻找完美匹配
		fill(slack, slack + sizeof(slack) / sizeof(int), kINF);
		while(true){
			memset(visit_X, false, sizeof(visit_X)); //初始化 S、T集合为空
			memset(visit_Y, false, sizeof(visit_Y));
			if(Dfs(x)) break;  //若成功（找到了增广轨），则该点增广完成，进入下一个点的增广

			//若失败（没有找到增广轨），则需要改变一些点的标号，使得图中可行边的数量增加。
			//方法为：将所有在增广轨中（就是在增广过程中遍历到）的X方点的标号全部减去一个常数d，
			//所有在增广轨中的Y方点的标号全部加上一个常数d

			int min_d = kINF;
			for(int j = 0; j < ny; j++){ //找交错边里的最小d
				if(visit_Y[j] == false && min_d > slack[j]){
					min_d = slack[j];
				}
			}

			for(int i = 0; i < nx; i++){ //更新点标i -d
				if(visit_X[i] == true) lx[i] -= min_d;
			}
			for(int j = 0; j < ny; j++){ //更新边标y +d
				if(visit_Y[j] == true){
					ly[j] += min_d;
				}else{ //因为y不在T集合内，而s在集合内的，slack[y] = lx[x] + ly[y] - edge[x][y],此时l[x]减小了d，所以slack[y] -d
					slack[j] -= min_d;
				}
			}
		}
	}

	int res = 0;
	for(int y = 0; y < ny; y++){ //根据匹配link[y]，求最大权匹配
		if(link[y] != -1) res += edge[link[y]][y];
	}
	return res;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &edge[i][j]);
			}
		}
		int ans = KM();
		printf("%d\n", ans);
	}
	return 0;
}