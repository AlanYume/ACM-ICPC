/*** 无向图的 最大独立集问题（NP-hard），数据量小，采用位运算暴力求解 ****/
//http://acm.timus.ru/problem.aspx?space=1&num=1208
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
using namespace std;

const int kMaxN = 20;

int n;
int person_size;
vector<int> person[kMaxN * 3]; //person[i] :=第i个人参加的所有队伍
vector<int> G[kMaxN];

map<string, int> hash_;
void AddTeam(int n) {
	char str[24];
	scanf("%s", str);
	if (hash_[str] == 0)
		hash_[str] = ++person_size;
	person[hash_[str]].push_back(n);
}

void MakeGraph() {
	for (int i = 1; i <= person_size; i++) {
		for (vector<int>::iterator it1 = person[i].begin(); it1
			!= person[i].end(); it1++) {
				for (vector<int>::iterator it2 = person[i].begin(); it2
					!= person[i].end(); it2++) {
						G[*it1].push_back(*it2);
						G[*it2].push_back(*it1);
				}
		}
	}
}

bool visited[kMaxN];
bool Judge(int set){
	memset(visited, false, sizeof(visited));

	for(int i = 0; i < n; i++){
		if(set & (1 << i)) visited[i] = true;
	}

	for(int i = 0; i < n; i++){
		if(set & (1 << i)){
			for(vector<int> :: iterator it = G[i].begin(); it != G[i].end(); it++){
					if(*it != i && visited[*it] == true) return false;
			}
		}
	}
	return true;
}

int Solve(){
	MakeGraph();

	for(int k = n; k >= 1; k--){ //枚举集合的元素的大小
		int comb = (1 << k) - 1; //选择队伍的集合
		while(comb < 1 << n){
			if(Judge(comb)) return k;
			int x = comb & -comb, y = comb + x;
			comb = ((comb & ~y) / x >> 1) | y;
		}
	}
	return 0;
}

int main() {
	scanf("%d", &n);

	person_size = 0;
	for (int i = 0; i < n; i++) { //边输入每个队伍，边处理每个人参加的所有队伍
		AddTeam(i);
		AddTeam(i);
		AddTeam(i); //把队伍添加到属于该队的每个成员
	}

	printf("%d\n", Solve());

	return 0;
}
