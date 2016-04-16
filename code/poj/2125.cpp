/************** 最小点权覆盖 *****************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
const int INF = 1e9;
const int MAXN = 100 << 3;
const int MAXM = 5000 << 3;

int n, m;
int s, t;
int edgeSize, head[MAXN];
struct Edge{
	int to, cap, next_;
}es[MAXM];
int level[MAXN], tmpHead[MAXN];

void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, int cap){
	es[edgeSize].to = v, es[edgeSize].cap = cap, es[edgeSize].next_ = head[u], head[u] = edgeSize++;
	es[edgeSize].to = u, es[edgeSize].cap = 0, es[edgeSize].next_ = head[v], head[v] = edgeSize++;
}

bool Bfs(){
	memset(level, -1, sizeof(level));
	level[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int nowSite = que.front(); que.pop();
		for(int i = head[nowSite]; i != -1; i = es[i].next_){
			if(es[i].cap > 0 && level[es[i].to] < 0){
				level[es[i].to] = level[nowSite] + 1;
				que.push(es[i].to);
			}
		}
	}
	return level[t] != -1;
}

int Dfs(int s,int f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_){
		if(es[i].cap > 0 && level[es[i].to] > level[s]){
			int tmpF = Dfs(es[i].to, min(f, es[i].cap));
			if(tmpF > 0){
				es[i].cap -= tmpF;
				es[i ^1].cap += tmpF;
				return tmpF;
			}
		}
	}
	return 0;
}

int MaxFlow(){
	int flow = 0;
	while(Bfs()){
		int f = 0;
		memcpy(tmpHead, head, sizeof(head));
		while((f = Dfs(s, INF)) > 0)
			flow += f;
	}
	return flow;
}

int main(){
	int u, v, cost;
	while(~scanf("%d %d", &n, &m)){
		InitEdge();
		s = 0, t = 2 * n + 1;
		for(int i = 1; i <= n; i++){
			scanf("%d", &cost);
			AddEdge(i + n, t, cost);
		}
		for(int i = 1; i <= n; i++){
			scanf("%d", &cost);
			AddEdge(s, i, cost);
		}
		for(int i = 1; i <= m; i++){
			scanf("%d %d", &u, &v);
			AddEdge(u, v + n, INF);
		}

		printf("%d\n", MaxFlow());
		int ans = 0;
		for(int i = 1; i <= n; i++){
			if(level[i] == -1){
				ans += 1;
			}
		}
		for(int i = n + 1; i <= 2 * n; i++){
			if(level[i] != -1){
				ans += 1;
			}
		}
		printf("%d\n", ans);
		for(int i = 1; i <= n; i++){
			if(level[i] == -1)
				printf("%d -\n", i);
		}
		for(int i = n + 1; i <= 2 * n; i++){
			if(level[i] != -1)
				printf("%d +\n", i - n);
		}
	}
	return 0;
}
