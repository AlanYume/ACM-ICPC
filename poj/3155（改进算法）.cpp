//胡伯涛论文4.4节 改进方法实现，复杂度：O(logN * MaxFlow(n, n + m))

#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const double INF = 1e10;
const double EPS = 1e-8;
const int MAXN = 100 << 1;
const int MAXM = 1000 << 3;

int n, m;
P p[1100];
int du[MAXN];
int s, t, num, edgeSize, head[MAXN];
struct Edge{
	int to, next_m;
	double cap;
}es[MAXM];
int level[MAXN], tmpHead[MAXN];

void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, double cap){
	es[edgeSize].to = v, es[edgeSize].cap = cap, es[edgeSize].next_m = head[u], head[u] = edgeSize++;
	es[edgeSize].to = u, es[edgeSize].cap = 0, es[edgeSize].next_m = head[v], head[v] = edgeSize++;
}

void MakeGraph(double g){
	InitEdge();
	for(int i = 1; i <= n; i++){
		AddEdge(s, i, m);
		AddEdge(i, t, m + 2 * g - du[i]);
	}
	for(int i = 1; i <= m; i++){
		AddEdge(p[i].first, p[i].second, 1);
		AddEdge(p[i].second, p[i].first, 1);
	}
}

bool Bfs(){
	memset(level, -1, sizeof(level));
	level[s] = 0;
	num = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int nowSite = que.front(); que.pop();
		for(int i = head[nowSite]; i != -1; i = es[i].next_m){
			if(es[i].cap > 0 && level[es[i].to] < 0){
				level[es[i].to] = level[nowSite] + 1;
				que.push(es[i].to);
				num += 1;
			}
		}
	}
	return level[t] != -1;
}

double Dfs(int s, double f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_m){
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
	double flow = 1.0 * m * n;
	while(Bfs()){
		memcpy(tmpHead, head, sizeof(head));
		double f;
		while((f = Dfs(s, INF)) > 0)
			flow -= f;
	}
	return (flow / 2) > 0;
}

void Solve(){
	s = 0, t = n + 1;

	double l = 0, r = m;
	while(r - l > EPS){ //胡伯涛的论文给出了证明,不同解之间误差的精度不超过1/(n*n）
		double mid = (l + r) / 2;
		MakeGraph(mid);
		if(H_g())
			l = mid;
		else
			r = mid;
	}

	MakeGraph(l);
	H_g();
	printf("%d\n", num);
	for(int i = 1; i <= n; i++)
		if(level[i] > 0)
			printf("%d\n", i);
}

int main(){
	while(~scanf("%d %d", &n,&m)){
		memset(du, 0, sizeof(du));
		for(int i = 1; i <= m; i++){
			scanf("%d %d", &p[i].first, &p[i].second);
			du[p[i].first] += 1, du[p[i].second] += 1;
		}
		if(m == 0)
			printf("1\n1\n");
		else
			Solve();
	}
	return 0;
}