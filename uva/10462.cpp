//this is wrong
//git test
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 110;
const int kMaxM = 440;

struct Edge{
	int to, next_, len;
};

int n, m;
int head[kMaxN], edge_size;
Edge edge[kMaxM];
int min_cost[kMaxN];
bool visit[kMaxN], used[kMaxM];
int max_edge[kMaxN][kMaxN];
int pre[kMaxN]; //pre[i] := 最小生成树上节点i的前趋边
int cost_tree[2];

void InitEdge(){
	edge_size = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int from, int to, int len){
	edge[edge_size].to = to;
	edge[edge_size].len = len;
	edge[edge_size].next_ = head[from];
	head[from] = edge_size++;
}

void Read(){
	InitEdge();
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		if(u != v){
			AddEdge(u, v, c);
			AddEdge(v, u, c);
		}
	}
}

bool Prim(){
	memset(visit, false, sizeof(visit));
	memset(used, false, sizeof(used));
	memset(max_edge, 0, sizeof(max_edge));
	memset(pre, -1, sizeof(pre));
	for(int i = 1; i <= n; i++) min_cost[i] = kINF;
	min_cost[1] = 0;
	cost_tree[0] = 0;
	for(int i = 1; i <= n; i++){
		int u = -1;
		for(int v = 1; v <= n; v++){
			if(visit[v] == false && (u == -1 || min_cost[v] < min_cost[u])) u = v;
		}
		if(min_cost[u] == kINF) return false;
		//printf("now_id :: %d  min_cost %d\n", u, min_cost[u]);
		cost_tree[0] += min_cost[u];
		if(pre[u] != -1) used[pre[u]] = used[pre[u] ^ 1] = true;
		for(int e_id = head[u]; ~e_id; e_id = edge[e_id].next_){
			int to = edge[e_id].to;
			if(visit[to]){
				max_edge[to][u] = max_edge[u][to] = max(max_edge[to][edge[pre[u] ^ 1].to], min_cost[u]);
			}else{
				if(min_cost[to] > edge[e_id].len){
					min_cost[to] = edge[e_id].len;
					pre[to] = e_id;
				}
			}
		}
		visit[u] = true;
	}
	return true;
}

bool MST(){
	cost_tree[1] = kINF;
	for(int i = 1; i <= n; i++){
		for(int e_id = head[i]; ~e_id; e_id = edge[e_id].next_){
			if(!used[e_id]){
				cost_tree[1] = min(cost_tree[1], cost_tree[0] - max_edge[i][edge[e_id].to] + edge[e_id].len);
			}
		}
	}
	return cost_tree[1] != kINF;
}

void Solve(){
	if(Prim() == false){
		printf("No way\n");
	}else if(MST() == false){
		printf("No second way\n");
	}else{
		printf("%d\n", cost_tree[1]);
	}
}

int main(){
	int test;
	scanf("%d", &test);
	for(int cas = 1; cas <= test; cas++){
		Read();
		printf("Case #%d : ", cas);
		Solve();
	}
	return 0;
}
