/******** 精确覆盖（Dancing Links X) ***********/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int N = 16;
const int kMaxN = N*N*N + 10;
const int kMaxM = N*N*4 + 10;
const int kMaxNode = kMaxN*4 + kMaxM + 10;

char map[N][N+10];

class DLX{
private:
	int n, m, size;
	int U[kMaxNode], D[kMaxNode], L[kMaxNode], R[kMaxNode], Row[kMaxNode], Col[kMaxNode];
	int H[kMaxN], S[kMaxM];
	int ansd, ans[N*N + 10];

    void Print(){
		for(int i = 0; i < N; i++) printf("%s\n", map[i]);
	}

	void ReMove(int c){
		L[R[c]] = L[c]; R[L[c]] = R[c];
		for(int i = U[c]; i != c; i = U[i]){
			for(int j = L[i]; j != i; j = L[j]){
				D[U[j]] = D[j];
				U[D[j]] = U[j];
				--S[Col[j]];
			}
		}
	}

	void ReSume(int c){
		for(int i = D[c]; i != c; i = D[i]){
			for(int j = R[i]; j != i; j = R[j]){
				D[U[j]] = U[D[j]] = j;
				++S[Col[j]];
			}
		}
		R[L[c]] = L[R[c]] = c;
	}

public:
	void Init(int _n, int _m){
		n = _n; m = _m;
		for(int i = 0; i <= m; i++){
			S[i] = 0;
			D[i] = U[i] = i;
			L[i] = i - 1;
			R[i] = i + 1;
		}
		L[0] = m; R[m] = 0;
		size = m;
		for(int i = 1; i <= n; i++) H[i] = -1;
	}

	void Link(int r, int c){
		S[c] += 1;
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

	bool Dance(int ansd){
		if(R[0] == 0){
			for(int i = 0; i < ansd; i++){
				int tmp_val = (ans[i] - 1) / N;
				map[tmp_val / N][tmp_val % N] = (ans[i] - 1) % N + 'A';
			}
			Print();
			return true;
		}
		int c = L[0];
		for(int i = L[0]; i != 0; i = L[i]){
			if(S[i] < S[c]) c = i;
		}
		ReMove(c);
		for(int i = U[c]; i != c; i = U[i]){
			ans[ansd] = Row[i];
			for(int j = L[i]; j != i; j = L[j]) ReMove(Col[j]);
			if(Dance(ansd+1)) return true;
			for(int j = R[i]; j != i; j = R[j]) ReSume(Col[j]);
		}
		ReSume(c);
		return false;
	}

	void GetPlace(int &r, int &c1, int &c2, int &c3, int &c4, int i, int j, int k){
		r = (i*N+j)*N + k;
		c1 = i*N + j + 1;
		c2 = N*N + i*N + k;
		c3 = N*N*2 + j*N + k;
		c4 = N*N*3 + ((i/4)*4 + (j/4))*N + k;
	}
}dlx;

int main(){
	while(~scanf("%s", map[0])){
		dlx.Init(N*N*N, N*N*4);
		for(int i = 0; i < N; i++){
			if(i != 0) scanf("%s", map[i]);
			for(int j = 0; j < N; j++){
				for(int k = 0; k < N; k++){
					if(map[i][j] == '-' || map[i][j] == k + 'A'){
						int r, c1, c2, c3, c4;
						dlx.GetPlace(r, c1, c2, c3, c4, i, j, k+1);
						dlx.Link(r, c1);
						dlx.Link(r, c2);
						dlx.Link(r, c3);
						dlx.Link(r, c4);
					}
				}
			}
		}
		dlx.Dance(0);
		printf("\n");
	}
	return 0;
}

