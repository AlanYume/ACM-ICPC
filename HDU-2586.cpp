/************* Tarjan�����㷨��LCA ****************/

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

const int kMaxN = 40000 + 16;
const int kMaxM = 200 + 16;
const int KMaxEdgeSize = (kMaxN << 1) + 16;
const int kMaxQuestionEdgeSize = (kMaxM << 1) + 16;

struct Edge{
	int to, next_m, val;
};

int n, m;
int dist_for_quesion[kMaxM];
int head[kMaxN], question_head[kMaxN]; //�ڶ�������quest...ҲӦ����KMaxN��һ����ĸ������һ���磬����˵��wrong answer ��ѽѽ~��
int edge_size, question_edge_size;
Edge es[KMaxEdgeSize], q_es[kMaxQuestionEdgeSize];

int par[kMaxN]; //par[x]��= �ڵ�x������
int dist[kMaxN]; //dist[x]:= �ڵ�x�����ڵ�ľ���

inline void InitEdge(){
	edge_size = 0;
	memset(head, -1, sizeof(head));
}

inline void InitQuestionEdge(){
	question_edge_size = 0;
	memset(question_head, -1, sizeof(question_head));
}

inline void AddEdge(int from, int to, int len){
	es[edge_size].to = to;
	es[edge_size].val = len;
	es[edge_size].next_m = head[from];
	head[from] = edge_size++;
}

inline void AddQuestionEdge(int from, int to, int q_id){
	q_es[question_edge_size].to = to;
	q_es[question_edge_size].val = q_id;
	q_es[question_edge_size].next_m = question_head[from];
	question_head[from] = question_edge_size++;
}

inline void InitPar(){
	memset(par, -1, sizeof(par));
}

int GetPar(int x){
	if(x == par[x]) return x;
	return par[x] = GetPar(par[x]);
}

void Tarjan(int root, int len){ //�����������
	dist[root] = len;
	par[root] = root; //��һ������ʡ����Ϊ��ÿ��ѯ���У�ÿ���㶼�п��ܳ�Ϊ��ѯ�ʵ�Ե�����

	for(int i = head[root]; ~i; i = es[i].next_m){
		int to = es[i].to;
		if(par[to] == -1){ //��ǰ������δ���ʹ�
			Tarjan(to, len + es[i].val);
			par[to] = root;
		}
	}

	for(int i = question_head[root]; ~i; i = q_es[i].next_m){
		int to = q_es[i].to;
		if(par[to] != -1){ //����ѯ�ʵĽڵ�ԣ�ǰ�᣺��Ѱ�ʵĽڵ�Ե��������ѱ�����ϣ�
			int lca = GetPar(to); //��ѯ�ʵ�Ե������������
			dist_for_quesion[q_es[i].val] = dist[root] + dist[to] - (dist[lca] << 1);
		}
	}
}

void LCA(int root){
	InitPar();
	Tarjan(root, 0);
}

int main(){
	int test;
	scanf("%d", &test);
	while(test--){
		scanf("%d %d", &n, &m);

		InitEdge();
		for(int i = 0; i + 1 < n; i++){
			int u, v, len;
			scanf("%d %d %d", &u, &v, &len);
			AddEdge(u, v, len);
			AddEdge(v, u, len);
		}

		InitQuestionEdge();
		for(int i = 0; i < m; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			AddQuestionEdge(u, v, i);
			AddQuestionEdge(v, u, i);
		}

		LCA(1);

		for(int i = 0; i < m; i++){
			printf("%d\n", dist_for_quesion[i]);
		}
	}
	return 0;
}