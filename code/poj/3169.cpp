#include <iostream>
#include <cstdio>
using namespace std;
const int INF = 100000000;

int N, ML, MD;
int AL[10010], BL[10010], DL[10010];
int AD[10010], BD[10010], DD[10010];
int d[1010];

void Solve(){
	fill(d, d + N, INF);
	d[0] = 0;
	for(int k = 0; k < N; k++)
	{
		for(int i = 0; i + 1 < N; i++)
			if(d[i + 1] < INF)
				d[i] = min(d[i], d[i + 1]);
		for(int i = 0; i < ML; i++)
			if(d[AL[i] -1] < INF)
				d[BL[i] -1] = min(d[BL[i] - 1], d[AL[i] - 1] + DL[i]);
		for(int i = 0; i < MD; i++)
			if(d[BD[i] - 1] < INF)
				d[AD[i] - 1] = min(d[AD[i] - 1], d[BD[i] - 1] - DD[i]);
	}
	int res = d[N - 1];
	if(d[0] < 0)
		res = -1;
	else if(res == INF)
		res = -2;
	printf("%d\n", res);
}

int main() {
	while(~scanf("%d %d %d", &N, &ML, &MD)) {
		for(int i = 0; i < ML; i++) scanf("%d %d %d", &AL[i], &BL[i], &DL[i]);
		for(int i = 0; i < MD; i++) scanf("%d %d %d", &AD[i], &BD[i], &DD[i]);
		Solve();
	}
	return 0;
}
