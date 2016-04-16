/******* Dancing Link X（精确覆盖）*******/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxN = 2510;
const int kMaxM = 3010;
const int kMaxNode = kMaxN*4+kMaxM;

int N;

struct DLX{
	int n, m, size;
	int U[kMaxNode], D[kMaxNode], L[kMaxNode], R[kMaxNode], Row[kMaxNode], Col[kMaxNode];
	int H[kMaxN], S[kMaxM];
	int ansd, ans[kMaxN];

	void Init(int _n, int _m){
		n = _n; m = _m;
		for(int i = 0; i <= m; i++){
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i + 1;
			R[i] = i - 1;
		}
		L[m] = 0; R[0] = m;
		size = m;
		for(int i = 1; i <= n; i++) H[i] = -1;
	}

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

	int p_ans[54];
	bool Dance(int d){
		if(d >= N){
			for(int i = 0; i < d; i++){
				p_ans[(ans[i]-1)/N] = (ans[i]%N ? ans[i]%N :N);
			}
			for(int i = 0; i < N; i++){
				if(i) printf(" ");
				printf("%d", p_ans[i]);
			}
			printf("\n");
			return true;
		}

		int c = L[0];
		for(int i = L[0]; i != 0 && i <= 2*N; i = L[i]){ //注意：对于每条谢对角线，不一定都有皇后覆盖，所以，如果在第一步就错误的选取了怎么都不可能会被覆盖的斜对角线作出初始Dance Link X 的覆盖列，那么势必导致无解。随意i必须小于等于2*n，即只在行和列里取最小的S[i]，作为处理DLX的覆盖列
			if(S[i] < S[c]) c = i;
		}
		ReMove(c);
		for(int i = U[c]; i != c; i = U[i]){
			ans[d] = Row[i];
			for(int j = L[i]; j != i; j = L[j]) ReMove(Col[j]);
			if(Dance(d+1)) return true;
			for(int j = R[i]; j != i; j = R[j]) ReSume(Col[j]);
		}
		ReSume(c);
		return false;
	}

	void Place(int &r, int &c, int &lx, int &rx, int i, int j){
		r = i;  c = N + j;
		lx = 2*N + j+i-1;
		rx = 4*N + j-i+N-1;
	}
}dlx;

int main(){
	while(~scanf("%d" ,&N)){
		dlx.Init(N*N, 6*N-2);
		for(int i = 1; i <= N; i++){
			int tmp_col, r, c, lx, rx;
			scanf("%d", &tmp_col);
			if(tmp_col){
				dlx.Place(r, c, lx, rx, i, tmp_col);
				dlx.Link((i-1)*N+tmp_col, r);
				dlx.Link((i-1)*N+tmp_col, c);
				dlx.Link((i-1)*N+tmp_col, lx);
				dlx.Link((i-1)*N+tmp_col, rx);
			}else{
				for(int j = 1; j <= N; j++){
					dlx.Place(r, c, lx, rx, i, j);
					dlx.Link((i-1)*N+j, r);
                    dlx.Link((i-1)*N+j, c);
					dlx.Link((i-1)*N+j, lx);
					dlx.Link((i-1)*N+j, rx);
				}
			}
		}
		dlx.Dance(0);
	}
	return 0;
}

