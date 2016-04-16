#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

typedef pair<int, int> P;
const int kINF = 100000000;
const int kMaxN = 5010;
const int kMaxR = 100010;

struct Edge{
	int to, len, next_;
};

int n, r;
int dist[kMaxN], dist2[kMaxN]; //最短路，次短路
int head[kMaxN], edge_size;
Edge es[kMaxR << 1];

void InitEdge(){
	edge_size = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int from, int to, int len){
	es[edge_size].to = to; 
	es[edge_size].len = len;
	es[edge_size].next_ = head[from];
	head[from] = edge_size++;
}

void Solve(){
	priority_queue<P, vector<P>, greater<P> > que;
	fill(dist, dist + n, kINF);
	fill(dist2, dist2 + n, kINF);
	dist[0] = 0;
	que.push(P(0, 0));

	while(!que.empty()){
		P now_p = que.top(); que.pop();
		int now_v = now_p.second, now_dist = now_p.first;
		if(dist2[now_v] < now_dist) continue; //当前状态点的距离比次短路都大了，则跳过 
		for(int e_id = head[now_v]; ~e_id; e_id = es[e_id].next_){ //枚举与当前点连通的每条边
			int next_v = es[e_id].to, next_len = es[e_id].len, next_dist = now_dist + next_len;
			if(dist[next_v] > next_dist){
				swap(dist[next_v], next_dist);
				que.push(P(dist[next_v], next_v));
			}
			if(dist2[next_v] > next_dist){
				dist2[next_v] = next_dist;
				que.push(P(dist2[next_v], next_v));
			}
		}
	}
	printf("%d\n", dist2[n - 1]);
}

void Read(){
	InitEdge();
	scanf("%d %d", &n, &r);
	for(int i = 0; i < r; i++){
		int u, v, l;
		scanf("%d %d %d", &u, &v, &l);
		u -= 1; v -= 1;
		AddEdge(u, v, l);
		AddEdge(v, u, l);
	}
}

int main(){
	Read();
	Solve();
	return 0;
}
