/*************  ������(��С��ģ�ͣ�0-1�����滮 + ��λ���� ***********************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
using namespace std;
typedef pair<int, int> P;
const int MAXN = 500 + 16;
const int MAXM = 3000 << 2;
const int INF = 1e9;

int n, m, k;
P p[MAXN];
int ans[MAXN];
int head[MAXN], edgeSize;
struct Edge{
	int to, cap, next_;
}es[MAXM];
int saveHead[MAXN], saveEdgeSize;
int tmpHead[MAXN], level[MAXN];

void InitEdge(){
	edgeSize = 0;
	memset(head, -1, sizeof(head));
}

void AddEdge(int u, int v, int cost){
	es[edgeSize].to = v, es[edgeSize].cap = cost, es[edgeSize].next_ = head[u], head[u] = edgeSize++;
	es[edgeSize].to = u, es[edgeSize].cap = cost, es[edgeSize].next_ = head[v], head[v] = edgeSize++;
}

void ResaveGraph(){
	edgeSize = saveEdgeSize;
	memcpy(head, saveHead, sizeof(head));
	for(int i = 0; i < edgeSize; i++)
		es[i].cap = 1;
}

bool Bfs(int s, int t){
	memset(level, -1, sizeof(level));
	level[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()){
		int nowSite = que.front(); que.pop();
		for(int i = head[nowSite]; i != -1; i = es[i].next_){
			if(es[i].cap > 0 && level[es[i].to] < 0){
				level[es[i].to] = level[nowSite] + 1;
				que.push(es[i].to);
			}
		}
	}
	return level[t] != -1;
}

int Dfs(int s, int t, int f){
	if(s == t)
		return f;
	for(int &i = tmpHead[s]; i != -1; i = es[i].next_){
		if(es[i].cap > 0 && level[es[i].to] > level[s]){
			int tmpI = i;
			int tmpF = Dfs(es[i].to, t, min(f, es[i].cap));
			if(tmpF > 0){
				es[tmpI].cap -= tmpF;
				es[tmpI ^ 1].cap += tmpF;
				return tmpF;
			}
		}
	}
	return 0;
}

void MaxFlow(int s, int t){
	int flow = 0;
	while(Bfs(s, t)){
		memcpy(tmpHead, head, sizeof(head));
		int f;
		while((f = Dfs(s, t, INF)) > 0)
			flow += f;
	}
}

int main(){
	int test, u, v;
	while(~scanf("%d", &test)){
		while(test--){
			InitEdge();
			scanf("%d %d", &n, &m);

			//����������ͨ�ı�
			for(int i = 0; i < m; i++){
				scanf("%d %d", &u, &v);
				AddEdge(u, v, 1);
			}
			//���浱ǰͼ����Ϣ
			saveEdgeSize = edgeSize;
			memcpy(saveHead, head, sizeof(head));

			//������֪��ı����Ϣ
			scanf("%d", &k);
			for(int i = 0; i < k; i++){
				scanf("%d %d", &p[i].first, &p[i].second);
			}

			int s = 0, t = n + 1;
			memset(ans, 0, sizeof(ans));
			//��������λ��Ϣ��������
			for(int i = 0; i < 31; i++){
				//��ԭ�ȱ������ߵ�ͼ�ϸ��ݶ�������Ϣ�������
				ResaveGraph();
				for(int j = 0; j < k; j++){
					if(p[j].second >> i & 1){
						AddEdge(s, p[j].first, INF);
					}else{
						AddEdge(p[j].first, t, INF);
					}
				}
				//��һ�������������S-TΪ����ͼ
				MaxFlow(s, t);
				Bfs(s, t);
				for(int j = 1; j <= n; j++){
					if(level[j] > 0)
						ans[j] += 1 << i;
				}
			}

			//�����
			for(int i = 1; i <= n; i++){
				printf("%d\n", ans[i]);
			}
		}
	}
	return 0;
}