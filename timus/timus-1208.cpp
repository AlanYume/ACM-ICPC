/*** ����ͼ�� �����������⣨NP-hard����������С������λ���㱩����� ****/
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
vector<int> person[kMaxN * 3]; //person[i] :=��i���˲μӵ����ж���
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

	for(int k = n; k >= 1; k--){ //ö�ټ��ϵ�Ԫ�صĴ�С
		int comb = (1 << k) - 1; //ѡ�����ļ���
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
	for (int i = 0; i < n; i++) { //������ÿ�����飬�ߴ���ÿ���˲μӵ����ж���
		AddTeam(i);
		AddTeam(i);
		AddTeam(i); //�Ѷ�����ӵ����ڸöӵ�ÿ����Ա
	}

	printf("%d\n", Solve());

	return 0;
}
