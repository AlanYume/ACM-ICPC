/************ 2-SAT + 二分 *****************/
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

typedef pair<int, int> Point;
typedef pair<int, int> Pair;
const int kINF = 1e9;
const int kMAXN = 500 + 16;
const int kMAXM = 1000 + 16;

int n, a, b;
Point s_site[2], barn_site[kMAXN];
Pair hate_pair[kMAXN], friend_pair[kMAXM];

int s_dist;
int visited_point_num[kMAXN << 1];
vector<int> G[kMAXN << 1], rG[kMAXN << 1];
stack<int> visited_site_num_stack;

inline int GetDist(int i, int j){
	int dist_x = s_site[i].first - barn_site[j].first;
	if(dist_x < 0) dist_x = -dist_x;
	int dist_y = s_site[i].second - barn_site[j].second;
	if(dist_y < 0) dist_y = -dist_y;
	return dist_x + dist_y;
}

inline int GetSiteDist(){
	int s_dist_x = s_site[0].first - s_site[1].first;
	if(s_dist_x < 0) s_dist_x = -s_dist_x;
	int s_dist_y = s_site[0].second - s_site[1].second;
	if(s_dist_y < 0) s_dist_y = -s_dist_y;
	return s_dist_x + s_dist_y;
}

inline void AddEdge(int from, int to){
	G[from].push_back(to);
	rG[to].push_back(from);
}

void CreateGraph(int mid){
	for(int i = 0; i < 2 * n; i++){
		G[i].clear();
		rG[i].clear();
	}
	for(int i = 0; i < a; i++){
		//牛hate_frist 和 牛hate_second 彼此讨厌，
		//所以hate_frist 和 hate_second 不能选择相同的s_site，
		//等价于 hate_frist V hate_second；
		//hate_：表示选择site1； hate_ + n：表示不选site1
		AddEdge(hate_pair[i].first, hate_pair[i].second + n);
		AddEdge(hate_pair[i].first + n, hate_pair[i].second);
		AddEdge(hate_pair[i].second, hate_pair[i].first + n);
		AddEdge(hate_pair[i].second + n, hate_pair[i].first);
	}
	for(int i = 0; i < b; i++){
		//牛friedn_frist 和 牛friend_second 彼此友好，
		//所以friend_frist 和 friend_second 必需选择相同的s_site，
		//等价于 选择friend_frist V 不选friend_second （对site1而言）；
		//frind_：表示选择site1； friend_ + n：表示不选site1
		AddEdge(friend_pair[i].first, friend_pair[i].second);
		AddEdge(friend_pair[i].first + n, friend_pair[i].second + n);
		AddEdge(friend_pair[i].second, friend_pair[i].first);
		AddEdge(friend_pair[i].second + n, friend_pair[i].first + n);
	}
	for(int i = 0; i + 1 < n; i++){
		for(int j = i + 1; j < n; j++){
			if(GetDist(0, i) + GetDist(0, j) > mid){
				AddEdge(i, j + n);
				AddEdge(j, i + n);
			}
			if(GetDist(1, i) + GetDist(1, j) > mid){
				AddEdge(i + n, j);
				AddEdge(j + n, i);
			}
			if(GetDist(0, i) + GetDist(1, j) + s_dist > mid){
				AddEdge(i, j);
				AddEdge(j + n, i + n);
			}
			if(GetDist(1, i) + GetDist(0, j) + s_dist > mid){
				AddEdge(i + n, j + n);
				AddEdge(j, i);
			}
		}
	}
}

void Dfs(int root){
	visited_point_num[root] = 1;
	for(int i = 0; i < G[root].size(); i++){
		int to = G[root][i];
		if(visited_point_num[to] == -1) Dfs(to);
	}
	visited_site_num_stack.push(root);
}

void rDfs(int root, int scc_id){
	visited_point_num[root] = scc_id;
	for(int i = 0; i < rG[root].size(); i++){
		int to = rG[root][i];
		if(visited_point_num[to] == -1) rDfs(to, scc_id);
	}
}

bool Scc(int mid){
	CreateGraph(mid);
	memset(visited_point_num, -1, sizeof(visited_point_num));
	for(int i = 0; i < 2 * n; i++){
		if(visited_point_num[i] == -1) Dfs(i);
	}
	int scc_id = 0;
	memset(visited_point_num, -1, sizeof(visited_point_num));
	while(!visited_site_num_stack.empty()){
		int tmp = visited_site_num_stack.top();
		visited_site_num_stack.pop();
		if(visited_point_num[tmp] == -1) rDfs(tmp, scc_id++);
	}
	for(int i = 0; i < n; i++){
		if(visited_point_num[i] == visited_point_num[i + n]) return false;
	}
	return true;
}

int Solve(){
	s_dist = GetSiteDist();
	int left = 0, right = kINF;
	while(right > left + 1){
		int mid = (right + left) >> 1;
		if(Scc(mid)){
			right = mid;
		}else{
			left = mid;
		}
	}
	if(right == kINF){
		return -1;
	}else{
		return right;
	}
}

int main(){
	scanf("%d %d %d", &n, &a, &b);
	scanf("%d %d %d %d", &s_site[0].first, &s_site[0].second, 
		&s_site[1].first, &s_site[1].second);
	for(int i = 0; i < n; i++){
		scanf("%d %d", &barn_site[i].first, &barn_site[i].second);
	}
	for(int i = 0; i < a; i++){
		scanf("%d %d", &hate_pair[i].first, &hate_pair[i].second);
		hate_pair[i].first -= 1; hate_pair[i].second -= 1;
	}
	for(int i = 0; i < b; i++){
		scanf("%d %d", &friend_pair[i].first, &friend_pair[i].second);
		friend_pair[i].first -= 1; friend_pair[i].second -= 1;
	}
	printf("%d\n", Solve());
	return 0;
}
