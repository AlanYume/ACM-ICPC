/**********  网络流(最小割模型）0-1分数规划 ********************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
#define MAXN 116
#define MAXM 1616
const double EPS = 1e-7;
const double INF = 1e9;

int n, m;
int head[MAXN], edgeSize;
struct Edge{
	int from, to, next_;
	double cap, decr;
	bool isCut;
}es[MAXM];
double allCost;
int level[MAXN], tmpHead[MAXN];

void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, double cap){
	es[edgeSize].from = u, es[edgeSize].to = v, es[edgeSize].cap = cap, es[edgeSize].next_ = head[u], head[u] = edgeSize++;
	es[edgeSize].from = v, es[edgeSize].to = u, es[edgeSize].cap = cap, es[edgeSize].next_ = head[v], head[v] = edgeSize++;
}

void Cpyhead(){
	memcpy(tmpHead, head, sizeof(head));
}

bool Bfs(int s, int t){
	memset(level, -1, sizeof(level));
	level[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int nowSit = que.front(); que.pop();
		for(int i = head[nowSit]; i != -1; i = es[i].next_){
			if(es[i].cap > es[i].decr && level[es[i].to] < 0){
				level[es[i].to] = level[nowSit] + 1;
				que.push(es[i].to);
			}
		}
	}
	return level[t] != -1;
}

double Dfs(int s, int t, double f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_){
		if(es[i].cap > es[i].decr && level[s] < level[es[i].to]){
			int tmpI = i;
			double tmpFlow = Dfs(es[i].to, t, min(f, es[i].cap - es[i].decr));
			if(tmpFlow > 0){
				es[tmpI].decr += tmpFlow;
				es[tmpI ^ 1].decr -= tmpFlow;
				return tmpFlow;
			}
		}
	}
	return 0;
}

double MaxFlow(int s, int t){
	double flow = 0;
	while(Bfs(s, t)){
		double f;
		Cpyhead();
		while((f = Dfs(s, t, INF)) > 0)
			flow += f;
	}
	return flow;
}

bool OK(double mid){
	double res = 0;
	for(int i = 0; i < edgeSize; i++){
		es[i].decr = mid;
		es[i].isCut = false;
		if(es[i].cap <= es[i].decr && !(i & 1)){
			res += es[i].cap - es[i].decr;
			es[i].isCut = true;
		}
	}
	res += MaxFlow(1, n);
	return res < 0;
}

void Solve(){
	double l = 0, r = allCost / m;
	while(r - l > EPS){
		double mid = (l + r) / 2;
		if(OK(mid)){
			r = mid;
		}else{
			l = mid;
		}
	}

	Bfs(1, n);
	level[1] = 1;
	queue<int> que;
	for(int i = 0; i < edgeSize; i += 2){
		if(es[i].isCut || level[es[i].from] * level[es[i].to] < 0)
			que.push((i >> 1) + 1);
	}

	printf("%d\n", que.size());
	while(!que.empty()){
		printf("%d ", que.front());
		que.pop();
	}
	printf("\n");
}

int main(){
	int u, v;
	double cap;
	bool havePut = false;
	while(~scanf("%d %d", &n, &m)){
		InitEdge();
		allCost = 0;
		for(int i = 1; i <= m; i++){
			scanf("%d %d %lf", &u, &v, &cap);
			AddEdge(u, v, cap);
			allCost += cap;
		}
		if(havePut)
			printf("\n");
		havePut = true;
		Solve();
	}
	return 0;
}