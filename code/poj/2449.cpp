/******* 最短路径 + A*搜索 *******/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> P;
const int kINF = 100000000;
const int kMaxN = 1000 + 16;
const int kMaxM = 100000;

struct Edge{
	int to, len;
	Edge() {}
	Edge(int to, int len) : to(to), len(len){}
};

struct Point{
	int H, visitCnt;
};

struct Path{
	int F, G, id;
	Path(){}
	Path(int F, int G, int id) : F(F), G(G), id(id) {}

	bool operator < (const Path &now_path) const{
		return this->F > now_path.F;
	};
};


int N, M;
int S, T, K;
Point ps[kMaxN];
vector<Edge> G[kMaxN];
vector<Edge> rG[kMaxN];

void Print(){
	printf("\n");
	for(int i = 0; i <= N; i++){
		printf("%d ", ps[i].H);
	}
	printf("\n");
}

void Init(){
	for(int i = 0; i <= N; i++){
		G[i].clear();
		rG[i].clear();
		ps[i].visitCnt = 0;
		ps[i].H = kINF;
	}
}

void AddEdge(int from, int to, int len){
	G[from].push_back(Edge(to, len));
	rG[to].push_back(Edge(from, len));
}

void Dijkstral(int s){
	priority_queue<P> pri_que;
	ps[s].H = 0;
	pri_que.push(P(0, s));
	while(pri_que.empty() == false){
		P tmp_p = pri_que.top();
		pri_que.pop();
		for(int i = 0; i < rG[tmp_p.second].size(); i++){
			int to = rG[tmp_p.second][i].to;
			int len = rG[tmp_p.second][i].len;
			if(ps[to].H > ps[tmp_p.second].H + len){
				ps[to].H = ps[tmp_p.second].H + len;
				pri_que.push(P(ps[to].H, to));
			}
		}
	}
}

int Astart(){
	Dijkstral(T); //获取每个点的评估值H
	//Print();
	//return  0;
	if(ps[S].H == kINF) return -1;
	priority_queue<Path> pri_que;
	pri_que.push(Path(ps[S].H, 0, S));
	while(pri_que.empty() == false){
		Path now_path = pri_que.top();
		pri_que.pop();
		ps[now_path.id].visitCnt += 1;
		if(now_path.id == T && ps[T].visitCnt == K) return now_path.F;
		for(int i = 0; i < G[now_path.id].size(); i++){
			int to = G[now_path.id][i].to;
			int len = G[now_path.id][i].len;
			if(ps[to].visitCnt >= K) continue;
			Path tmp_path;
			tmp_path.id = to;
			tmp_path.G = now_path.G + len;
			tmp_path.F = tmp_path.G + ps[to].H;
			pri_que.push(tmp_path);
		}
	}
	return -1;
}

int main(){
	scanf("%d %d", &N, &M);
	Init();
	for(int i = 0; i < M; i++){
		int from, to, len;
		scanf("%d %d %d", &from, &to, &len);
		AddEdge(from, to, len);
	}
	scanf("%d %d %d", &S, &T, &K);
	if(S == T) K++;
	printf("%d\n", Astart());
	return 0;
}