/****** Bfs + DP *******/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;
const int kMaxN = 100 + 16;
const int kMaxM = kMaxN * kMaxN;

struct Edge{
	int to, next_;
};

struct Point{
	int head, level;
	ll in, out;
};

int V, E;
Point ps[kMaxN];
int edge_size;
Edge es[kMaxM];

void InitGrap(){
	edge_size = 0;
	for(int i = 0; i <= V; i++){
		ps[i].head = -1;
		ps[i].level = -1;
		ps[i].in = ps[i].out = 0;
	}
}

void AddEdge(int from, int to){
	es[edge_size].to = to;
	es[edge_size].next_ = ps[from].head;
	ps[from].head = edge_size++;
}

void Bfs(){
	bool visit[kMaxN];
	memset(visit, false, sizeof(visit));

	queue<int> que;
	ps[1].level = 0;
	ps[1].in = 1;
	visit[1] = true;
	que.push(1);
	while(!que.empty()){
		int now_sit = que.front();
		que.pop();
		for(int i = ps[now_sit].head; ~i; i = es[i].next_){
			int to = es[i].to;
			if(ps[to].level == -1 || ps[to].level == ps[now_sit].level + 1){
				ps[to].level = ps[now_sit].level + 1;
				ps[to].in += ps[now_sit].in;
				if(visit[to] == false){
					que.push(to);
					visit[to] = true;
				}
			}
		}
	}
}

void rBfs(){
	bool visit[kMaxN];
	memset(visit, false, sizeof(visit));

	queue<int> que;
	ps[V].out = 1;
	visit[V] = true;
	que.push(V);
	while(!que.empty()){
		int now_sit = que.front();
		que.pop();
		for(int i = ps[now_sit].head; ~i; i = es[i].next_){
			int to = es[i].to;
			if(ps[to].level + 1 == ps[now_sit].level){
				ps[to].out += ps[now_sit].out;
				if(visit[to] == false){
					que.push(to);
					visit[to] = true;
				}
			}
		}
	}
}

void Solve(){
	Bfs();
	rBfs();
	
	ll max_safe = max(ps[1].in * ps[1].out, ps[V].in * ps[V].out);
	for(int i = 2; i < V; i++){
		max_safe = max(max_safe, ps[i].in * ps[i].out * 2);
	}
	printf("%.12f\n", 1.0 * max_safe / ps[1].out);
}

int main(){
	scanf("%d %d", &V, &E);
	InitGrap();
	for(int i = 0; i < E; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
	Solve();
	return 0;
}