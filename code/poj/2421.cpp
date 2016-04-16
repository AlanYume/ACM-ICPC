#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> P;
const int kMaxN = 10010;

int n;
P stop[kMaxN], now_sit;

void Solve(){
	int add_cnt = 0; //加油的次数
	sort(stop, stop + n);
	priority_queue<int> que;
	for(int i = n - 1; i >= 0; i--){
		int cost_oil = now_sit.first - stop[i].first; //到达下一个加油站需要消耗的油量
		while(now_sit.second < cost_oil){
			if(que.empty()){
				printf("-1\n");
				return ;
			}
			now_sit.second += que.top();
			que.pop();
			add_cnt++;
		}
		now_sit.second -= cost_oil;
		now_sit.first = stop[i].first;
		que.push(stop[i].second);
	}
	printf("%d\n", add_cnt);
}

void Read(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d", &stop[i].first, &stop[i].second);
	stop[n].first = 0; stop[n].second = 0; n++; //把最后的终点位置也考虑成加油站，方便判断最后一个加油站到终点的剩余油量能否到达终点
	scanf("%d %d", &now_sit.first, &now_sit.second);
}

int main(){
	Read();
	Solve();
	return 0;
}

