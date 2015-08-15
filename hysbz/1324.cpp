/*********  最大点独立集  **********/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
const int INF = 1e9;
const int MAXN = 100 + 16;
const int MAXPOINTSIZE = 100 * 100 + 16;
const int MAXEDGESIZE =	(100 * 100) << 3;
const int dir[4][2] = {0, -1, -1, 0, 0, 1, 1, 0};

int n, m, maxVal;
int filed[MAXN][MAXN];
int s, t, edgeSize, head[MAXPOINTSIZE];
struct Edge{
	int to, cap, next_;
}es[MAXEDGESIZE];
int level[MAXPOINTSIZE], tmpHead[MAXPOINTSIZE];

inline void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

inline void AddEdge(int u, int v, int cap){
	es[edgeSize].to = v, es[edgeSize].cap = cap, es[edgeSize].next_ = head[u], head[u] = edgeSize++;
	es[edgeSize].to = u, es[edgeSize].cap = 0, es[edgeSize].next_ = head[v], head[v] = edgeSize++;
}

inline bool InFiled(int x, int y){
	return (x >= 0 && x < n && y >= 0 && y < m);
}

void MakeGraph(){
	InitEdge();
	s = n * m, t = s + 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if((i + j) & 1){
				AddEdge(s, i * m + j, filed[i][j]);
				for(int k = 0; k < 4; k++){
					int xx = i + dir[k][0];
					int yy = j + dir[k][1];
					if(InFiled(xx, yy)){
						AddEdge(i * m + j, xx * m + yy, INF);
					}
				}
			}else{
				AddEdge(i * m + j, t, filed[i][j]);
			}
		}
	}
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
				level[es[i].to]  = level[nowSite] + 1;
				que.push(es[i].to);
			}
		}
	}
	return level[t] != -1;
}

int Dfs(int s, int f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_){
		if(es[i].cap > 0 && level[es[i].to] > level[s]){
			int tmpF = Dfs(es[i].to, min(f, es[i].cap));
			if(tmpF > 0){
				es[i].cap -= tmpF;
				es[i ^ 1].cap += tmpF;
				return tmpF;
			}
		}
	}
	return 0;
}

int MaxFlow(){
	int flow = 0;
	while(Bfs()){
		int f;
		memcpy(tmpHead, head, sizeof(head));
		while((f = Dfs(s, INF)) > 0)
			flow += f;
	}
	return flow;
}

int Solve(){
	MakeGraph();
	return maxVal - MaxFlow();
}

int main(){
	scanf("%d %d", &n, &m);
	maxVal = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%d", &filed[i][j]);
			maxVal += filed[i][j];
		}
	}
	printf("%d\n", Solve());
	return 0;
}