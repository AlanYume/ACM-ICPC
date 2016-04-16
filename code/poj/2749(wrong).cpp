/***************  2-SAT（wrong） *******************/
//因为 2-sat 跑出来的答案是有多解的，而你直接找最大值，
//只是找到了其中一个解的最大值，可能并不是最优的情况
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> Poll;
typedef pair<ll, ll> Pair;
const ll kINF = 1e9;
const ll kMAXN = 500 + 16;
const ll kMAXM = 1000 + 16;

ll n, a, b;
Poll s_site[2], barn_site[kMAXN];
Pair hate_pair[kMAXN], friend_pair[kMAXM];

ll s_dist;
ll visited_poll_num[kMAXN << 1];
vector<ll> G[kMAXN << 1], rG[kMAXN << 1];
stack<ll> visited_site_num_stack;

inline ll GetDist(ll i, ll j){
	ll dist_x = s_site[i].first - barn_site[j].first;
	if(dist_x < 0) dist_x = -dist_x;
	ll dist_y = s_site[i].second - barn_site[j].second;
	if(dist_y < 0) dist_y = -dist_y;
	return dist_x + dist_y;
}

inline ll GetSiteDist(){
	ll s_dist_x = s_site[0].first - s_site[1].first;
	if(s_dist_x < 0) s_dist_x = -s_dist_x;
	ll s_dist_y = s_site[0].second - s_site[1].second;
	if(s_dist_y < 0) s_dist_y = -s_dist_y;
	return s_dist_x + s_dist_y;
}

inline void AddEdge(ll from, ll to){
	G[from].push_back(to);
	rG[to].push_back(from);
}

//void CreateGraph(ll mid){
void CreateGraph(){
	for(ll i = 0; i < 2 * n; i++){
		G[i].clear();
		rG[i].clear();
	}
	for(ll i = 0; i < a; i++){
		//牛hate_frist 和 牛hate_second 彼此讨厌，
		//所以hate_frist 和 hate_second 不能选择相同的s_site，
		//等价于 hate_frist V hate_second；
		//hate_：表示选择site1； hate_ + n：表示不选site1
		AddEdge(hate_pair[i].first, hate_pair[i].second + n);
		AddEdge(hate_pair[i].first + n, hate_pair[i].second);
		AddEdge(hate_pair[i].second, hate_pair[i].first + n);
		AddEdge(hate_pair[i].second + n, hate_pair[i].first);
	}
	for(ll i = 0; i < b; i++){
		//牛friedn_frist 和 牛friend_second 彼此友好，
		//所以friend_frist 和 friend_second 必需选择相同的s_site，
		//等价于 选择friend_frist V 不选friend_second （对site1而言）；
		//frind_：表示选择site1； friend_ + n：表示不选site1
		AddEdge(friend_pair[i].first, friend_pair[i].second);
		AddEdge(friend_pair[i].first + n, friend_pair[i].second + n);
		AddEdge(friend_pair[i].second, friend_pair[i].first);
		AddEdge(friend_pair[i].second + n, friend_pair[i].first + n);
	}
}

void Dfs(ll root){
	visited_poll_num[root] = 1;
	for(ll i = 0; i < G[root].size(); i++){
		ll to = G[root][i];
		if(visited_poll_num[to] == -1) Dfs(to);
	}
	visited_site_num_stack.push(root);
}

void rDfs(ll root, ll scc_id){
	visited_poll_num[root] = scc_id;
	for(ll i = 0; i < rG[root].size(); i++){
		ll to = rG[root][i];
		if(visited_poll_num[to] == -1) rDfs(to, scc_id);
	}
}

void Scc(){
	CreateGraph();
	memset(visited_poll_num, -1, sizeof(visited_poll_num));
	for(ll i = 0; i < 2 * n; i++){
		if(visited_poll_num[i] == -1) Dfs(i);
	}
	ll scc_id = 0;
	memset(visited_poll_num, -1, sizeof(visited_poll_num));
	while(!visited_site_num_stack.empty()){
		ll tmp = visited_site_num_stack.top();
		visited_site_num_stack.pop();
		if(visited_poll_num[tmp] == -1) rDfs(tmp, scc_id++);
	}
	for(ll i = 0; i < n; i++){
		if(visited_poll_num[i] == visited_poll_num[i + n]){
			printf("-1\n");
			return ;
		}
	}

	//枚举牛牛间两两的距离，取其最大值
	ll res = 0;
	for(ll i = 0; i < n; i++){
		for(ll j = i + 1; j < n; j++){
			if(visited_poll_num[i] > visited_poll_num[i + n] && visited_poll_num[j] > visited_poll_num[j + n]){ //i 和 j 都选择了站0
				res = max(res,GetDist(0, i) + GetDist(0, j));
			}else if(visited_poll_num[i] < visited_poll_num[i + n] && visited_poll_num[j] < visited_poll_num[j + n]){ //i 和 j都选择了站1
				res = max(res, GetDist(1, i) + GetDist(1, j));
			}else if(visited_poll_num[i] > visited_poll_num[i + n] && visited_poll_num[j] < visited_poll_num[j + n]){ // i 选0； j 选1
				res = max(res, GetDist(0, i) + GetDist(1, j) + s_dist);
			}else if(visited_poll_num[i] < visited_poll_num[i + n] && visited_poll_num[j] > visited_poll_num[j + n]){ // i 选1； j 选0
				res = max(res, GetDist(1, i) + GetDist(0, j) + s_dist);
			}
		}
	}
	printf("%I64d\n", res);
}

void Solve(){
	s_dist = GetSiteDist();
	Scc();
}

int main(){
	scanf("%I64d %I64d %I64d", &n, &a, &b);
	scanf("%I64d %I64d %I64d %I64d", &s_site[0].first, &s_site[0].second, 
		&s_site[1].first, &s_site[1].second);
	for(ll i = 0; i < n; i++){
		scanf("%I64d %I64d", &barn_site[i].first, &barn_site[i].second);
	}
	for(ll i = 0; i < a; i++){
		scanf("%I64d %I64d", &hate_pair[i].first, &hate_pair[i].second);
		hate_pair[i].first -= 1; hate_pair[i].second -= 1;
	}
	for(ll i = 0; i < b; i++){
		scanf("%I64d %I64d", &friend_pair[i].first, &friend_pair[i].second);
		friend_pair[i].first -= 1; friend_pair[i].second -= 1;
	}
	Solve();
	return 0;
}