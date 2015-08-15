/***** Dancing Link X *****/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxM = 1010; //列
const int kMaxN = 510; //行
const int kMaxNode = 500010;

struct DLX{
	int n, m, size;
	int U[kMaxNode], D[kMaxNode], L[kMaxNode], R[kMaxNode], Row[kMaxNode], Col[kMaxNode];
	int S[kMaxM], H[kMaxN];
	int ansd;

	void Init(int _n, int _m){
		ansd = kINF;
		n = _n;
		m = _m;
		for(int i = 0; i <= m; i++){
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i + 1; //相对与i+1来说，i在i+1的L
			R[i] = i - 1; //同上（这样反向指向，评判的时花的时间可以少一些）
		}
		R[0] = m; L[m] = 0; //保证仍然构成环
		size = m;
		for(int i = 1; i <= n; i++) H[i] = -1;
	}

	//之后的L、R都相对自己所在位置而言了，与上面不同，相互错开

	void Link(int r, int c){
		S[c]++;
		Col[++size] = c;
		Row[size] = r;
		U[size] = U[c];
		D[U[c]] = size;
		D[size] = c;
		U[c] = size;
		if(H[r] == -1){
			H[r] = L[size] = R[size] = size;
		}else{
			L[size] = L[H[r]];
			R[L[H[r]]] = size;
			R[size] = H[r];
			L[H[r]] = size;
		}
	}

	void ReMove(int c){
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for(int i = U[c]; i != c; i = U[i]){
			for(int j = L[i]; j != i; j = L[j]){
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				S[Col[j]]--;
			}
		}
	}

	void ReSume(int c){
		for(int i = D[c]; i != c; i = D[i]){
			for(int j = R[i]; j != i; j = R[j]){
				U[D[j]] = D[U[j]] = j;
				S[Col[j]]++;
			}
		}
		R[L[c]] = L[R[c]] = c;
	}

	bool Dance(int d){
		if(L[0] == 0){
			if(d < ansd) ansd = d;
			return true;
		}

		int c = L[0];
		for(int i = L[0]; i != 0; i = L[i]){
			if(S[i] < S[c]) c = i;
		}
		ReMove(c);
		for(int i = U[c]; i != c; i = U[i]){
			for(int j = L[i]; j != i; j = L[j]) ReMove(Col[j]);
			Dance(d+1);
			for(int j = R[i]; j != i; j = R[j]) ReSume(Col[j]);
		}
		ReSume(c);
		return false;
	}
}dlx;

int main(){
	int test;
	int n, m, p;

	scanf("%d", &test);
	while(test--){
		scanf("%d %d %d", &n, &m, &p);

		dlx.Init(p, n*m);

		for(int i = 1; i <= p; i++){
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			//printf("占据： ");
			for(int y = y1; y < y2; y++){
				for(int x = x1; x < x2; x++){
                    //printf("%d ", y*(m+1)+x+1);
					dlx.Link(i, x*m+y+1);
				}
				//printf("\n");
			}
			//printf("\n");
		}

		dlx.Dance(0);
		if(dlx.ansd == kINF) dlx.ansd = -1;
		printf("%d\n", dlx.ansd);
	}
	return 0;
}

/*int main()
{
    int T;
    int n,m,p;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&p);
        dlx.Init(p,n*m);
        int x1,y1,x2,y2;
        for(int k = 1;k <= p;k++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            for(int i = x1+1;i <= x2;i++)
                for(int j = y1+1;j <= y2;j++)
                    dlx.Link(k,j + (i-1)*m);
        }
        dlx.Dance(0);
		if(dlx.ansd == kINF) dlx.ansd = -1;
        printf("%d\n", dlx.ansd);
    }
    return 0;
}*/

/*

3
5 5 2
0 0 5 2
0 2 5 5

*/

