#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Edge {
	int u, v, cost;
};

int N, M, R;
Edge es[50010];
int par[20010], ran[20010];

void InitBin(int n) {
	for(int i = 0; i < n; i++) {
		par[i] = i;
		ran[i] = 0;
	}
}

int FindBin(int x) {
	if(par[x] == x)
		return x;
	else
		return par[x] = FindBin(par[x]);
}

void UniteBin(int x, int y) {
	x = FindBin(x);
	y = FindBin(y);
	if(x == y)
		return ;
	if(ran[x] < ran[y])
		par[x] = y;
	else {
		par[y] = x;
		if(ran[x] == ran[y])
			ran[x]++;
	}
}

bool SameBin(int x, int y) {
	return FindBin(x) == FindBin(y);
}

bool cmp(const Edge &e1, const Edge &e2) {
	return e1.cost < e2.cost;
}

int Kruskal() {
	sort(es, es + R, cmp);
	InitBin(N + M);
	int res = 0;
	for(int i = 0; i < R; i++) {
		Edge e = es[i];
		if(!SameBin(e.u, e.v)) {
			UniteBin(e.u, e.v);
			res += e.cost;
		}
	}
	return res;
}

int main() {
	int test;
	int x, y, d;
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d %d", &N, &M, &R);
		for(int i = 0; i < R; i++) {
			scanf("%d %d %d", &x, &y, &d);
			es[i].u = x;
			es[i].v = N + y;
			es[i].cost = -d;
		}
		printf("%d\n", 10000 * (N + M) +Kruskal());
	}
	return 0;
}
