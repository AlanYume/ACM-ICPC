//胡伯涛论文4.2节 初步算法，复杂度：O(logN * MaxFlow(n + m, n + m))


#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const int MAXN = 1000 << 1;
const int MAXM = 1000 << 3;
const double INF = 1e9;
const double EPS = 1e-6;

int n, m;
P p[1000 + 16];
int s, t, Num;
int edgeSize, head[MAXN];
struct Edge{
	int to, next_;
	double cap;
}es[MAXM];
int level[MAXN], tmpHead[MAXN];

void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, double cap){
	es[edgeSize].to = v, es[edgeSize].cap = cap, es[edgeSize].next_ = head[u], head[u] = edgeSize++;
	es[edgeSize].to = u, es[edgeSize].cap = 0, es[edgeSize].next_ = head[v], head[v] = edgeSize++;
}

void MakeGraph(double g){
	InitEdge();
	for(int i = 1; i <= n; i++)
		AddEdge(i, t, g);
	for(int i = 1; i <= m; i++){
		AddEdge(s, n + i, 1.0);
		AddEdge(n + i, p[i].first, INF);
		AddEdge(n + i, p[i].second, INF);
	}
}

bool Bfs(){
	memset(level, -1, sizeof(level));
	level[s] = 0;
	Num = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int nowSit = que.front(); que.pop();
		for(int i = head[nowSit]; i != -1; i = es[i].next_){
			if(es[i].cap > 0 && level[es[i].to] < 0){
				level[es[i].to] = level[nowSit] + 1;
				que.push(es[i].to);
				if(es[i].to <= n)
					Num += 1;
			}
		}
	}
	return level[t] != -1;
}

double Dfs(int s, double f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_){
		if(es[i].cap > 0 && level[es[i].to] > level[s]){
			double tmpF = Dfs(es[i].to, min(f, es[i].cap));
			if(tmpF > 0){
				es[i].cap -= tmpF;
				es[i ^ 1].cap += tmpF;
				return tmpF;
			}
		}
	}
	return 0;
}

bool H_g(){
	double flow = m;
	while(Bfs()){
		double f;
		memcpy(tmpHead, head, sizeof(head));
		while((f = Dfs(s, INF)) > 0)
			flow -= f;
	}
	return flow <= 0;
}

void Solve(){
	s = 0, t = n + m + 1;
	double l = 0, r = 1.0 * m;
	while(r - l >= 1.0 / (n * n)){
		double mid = (l + r) / 2;
		MakeGraph(mid);
		if(H_g())
			r = mid;
		else
			l = mid;
	}

	//注意：二分求出的g还是存在进度问题，必须还得从新用g求一次最大权闭合子图。。。丧心病狂Orz~
	MakeGraph(l);
	H_g();
	printf("%d\n", Num);
	for(int i = 1; i <= n; i++){
		if(level[i] > 0)
			printf("%d\n", i);
	}
}

int main(){
	while(~scanf("%d %d", &n, &m)){
		for(int i = 1; i <= m; i++)
			scanf("%d %d", &p[i].first, &p[i].second);
		if(m == 0)
			printf("1\n1\n");
		else
			Solve();
	}
	return 0;
}