/******** 贪心 + 匈牙利二分匹配 （好题） **********/
//首先，第一印象是费用流，后来仔细一看时限 0.25s， 要超时的感觉
//后来，小对说 KM 匹配可以做，表没学过（额，现在学的差不多了，总体感觉是非常模板的，只要思路对了，代码基本不用怎么改动）
//另外KM 二部图的最大/小权匹配 时间复查度O(n^3) 和 网络流的O(n^2logM）差不多了。而相对来说，网络流更灵活，所以其可以处理的问题也更多，基本KM能做的，网络流也能做
//
//回归正题：这题表面看可以用KM求解，但时间复杂度O(400^4)、时限：0.25s，估计是TL的
//说说这题和 通常所做的KM匹配的区别。
//通常KM 二部最大/小权匹配 的是 二部图S-T集合间的连边的权值是有很多个的（每条边的权值都可以不同），
//而这题，是个特例，二部图中从S集合中一个点出发的连向T集合的任意一条边的权值都是一样的。
//所以，因为特殊，所以从这里入手。直接从S集合中 权值最大 的点开始 匈牙利匹配。
//（依据：1.每个女孩只能匹配一个男孩，当同一个女孩有多个男孩可以匹配时，优先匹配权值大的那个；
//2.匈牙利算法每次寻找交错轨的话，前面已匹配的节点绝不会再丢失匹配）
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int kMaxN = 400 + 16;

struct Son{
	int id, love_val;
	bool operator < (const Son &tmp_s) const{
		return love_val > tmp_s.love_val;
	}
};

int n;
Son son[kMaxN];
bool visit[kMaxN];
int link_m[kMaxN];
vector<int> G[kMaxN];

bool Dfs(int x){
	visit[x] = true;
	for(int i = 0; i < G[x].size(); i++){
		int u = G[x][i], w = link_m[u];
		if(w == -1 || !visit[w] && Dfs(w) == true){
			link_m[u] = x;
			return true;
		}
	}
	return false;
}

void  BipartiteMathcing(){
	memset(link_m, -1, sizeof(link_m));
	for(int i = 1; i <= n; i++){
		memset(visit, false, sizeof(visit));
		Dfs(son[i].id);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		son[i].id = i;
		scanf("%d", &son[i].love_val);
	}
	
	for(int i = 1; i <= n; i++){
		int num;
		scanf("%d", &num);
		while(num--){
			int tmp;
			scanf("%d", &tmp);
			G[i].push_back(tmp);
		}
	}

	sort(son  + 1, son + n + 1);
	BipartiteMathcing();

	int love_girle[kMaxN];
	memset(love_girle, 0, sizeof(love_girle));
	for(int i = 1; i <= n; i++){
		if(link_m[i] != -1){
			love_girle[link_m[i]] = i;
		}
	}
	
	for(int i = 1; i <= n; i++){
		printf("%d%c", love_girle[i], i == n ? '\n' : ' ');
	}

	return 0;
}