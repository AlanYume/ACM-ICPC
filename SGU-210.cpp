/******** ̰�� + ����������ƥ�� �����⣩ **********/
//���ȣ���һӡ���Ƿ�������������ϸһ��ʱ�� 0.25s�� Ҫ��ʱ�ĸо�
//������С��˵ KM ƥ�����������ûѧ���������ѧ�Ĳ���ˣ�����о��Ƿǳ�ģ��ģ�ֻҪ˼·���ˣ��������������ô�Ķ���
//����KM ����ͼ�����/СȨƥ�� ʱ�临���O(n^3) �� ��������O(n^2logM������ˡ��������˵��������������������Դ��������Ҳ���࣬����KM�����ģ�������Ҳ����
//
//�ع����⣺������濴������KM��⣬��ʱ�临�Ӷ�O(400^4)��ʱ�ޣ�0.25s��������TL��
//˵˵����� ͨ��������KMƥ�������
//ͨ��KM �������/СȨƥ�� ���� ����ͼS-T���ϼ�����ߵ�Ȩֵ���кܶ���ģ�ÿ���ߵ�Ȩֵ�����Բ�ͬ����
//�����⣬�Ǹ�����������ͼ�д�S������һ�������������T���ϵ�����һ���ߵ�Ȩֵ����һ���ġ�
//���ԣ���Ϊ���⣬���Դ��������֡�ֱ�Ӵ�S������ Ȩֵ��� �ĵ㿪ʼ ������ƥ�䡣
//�����ݣ�1.ÿ��Ů��ֻ��ƥ��һ���к�����ͬһ��Ů���ж���к�����ƥ��ʱ������ƥ��Ȩֵ����Ǹ���
//2.�������㷨ÿ��Ѱ�ҽ����Ļ���ǰ����ƥ��Ľڵ�������ٶ�ʧƥ�䣩
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int kMaxN = 400 + 16;

struct Son{
	int id, love_val;
	bool operator < (const Son &tmp_s) const{
		return love_val > tmp_s.love_val;
	}
};

int n;
Son son[kMaxN];
bool visit[kMaxN];
int link_m[kMaxN];
vector<int> G[kMaxN];

bool Dfs(int x){
	visit[x] = true;
	for(int i = 0; i < G[x].size(); i++){
		int u = G[x][i], w = link_m[u];
		if(w == -1 || !visit[w] && Dfs(w) == true){
			link_m[u] = x;
			return true;
		}
	}
	return false;
}

void  BipartiteMathcing(){
	memset(link_m, -1, sizeof(link_m));
	for(int i = 1; i <= n; i++){
		memset(visit, false, sizeof(visit));
		Dfs(son[i].id);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		son[i].id = i;
		scanf("%d", &son[i].love_val);
	}
	
	for(int i = 1; i <= n; i++){
		int num;
		scanf("%d", &num);
		while(num--){
			int tmp;
			scanf("%d", &tmp);
			G[i].push_back(tmp);
		}
	}

	sort(son  + 1, son + n + 1);
	BipartiteMathcing();

	int love_girle[kMaxN];
	memset(love_girle, 0, sizeof(love_girle));
	for(int i = 1; i <= n; i++){
		if(link_m[i] != -1){
			love_girle[link_m[i]] = i;
		}
	}
	
	for(int i = 1; i <= n; i++){
		printf("%d%c", love_girle[i], i == n ? '\n' : ' ');
	}

	return 0;
}