/*********** Dancing Links(可重复覆盖） ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 10;
const int kMaxNode = 100000; //注意：因为每个点都可由多块地毯覆盖，所以KMaxNode != (kMaxN+1)*kMaxN;

int n, m;
int pane_id[kMaxN+4][kMaxN+4];
int fold_size[kMaxN+4][kMaxN+4];

class DLX{
private:
	int n, m, size;
	int U[kMaxNode], D[kMaxNode], L[kMaxNode], R[kMaxNode], Row[kMaxNode], Col[kMaxNode];
	int H[kMaxNode], S[kMaxNode];
	int ansd;

	void ReMove(int c){
		for(int i = U[c]; i != c; i = U[i]){
			L[R[i]] = L[i];
			R[L[i]] = R[i];
		}
	}

	void ReSume(int c){
		for(int i = D[c]; i != c; i = D[i]){
			L[R[i]] = R[L[i]] = i;
		}
	}

	bool v[kMaxNode];
	int H_g(){
		int ret = 0;
		for(int c = L[0]; c != 0; c = L[c]) v[c] = true;
		for(int c = L[0]; c != 0; c = L[c]){
			if(v[c]){
				ret++;
				v[c] = false;
				for(int i = U[c]; i != c; i = U[i]){
					for(int j = L[i]; j != i; j = L[j]){
						v[Col[j]] = false;
					}
				}
			}
		}
		return ret;
	}

public:
	void Init(int _n, int _m){
		ansd = kINF;
		n = _n;
		m = _m;
		for(int i = 0; i <= m; i++){
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i - 1;
			R[i] = i + 1;
		}
		R[m] = 0; L[0] = m;
		size = m;
		for(int i = 1; i <= n; i++) H[i] = -1;
	}

	void Link(int r, int c){
		++S[c];
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

	void Dance(int d){
		if(d + H_g() >= ansd) return ;
		if(L[0] == 0){
			if(d < ansd) ansd = d;
			return ;
		}
		int c = L[0];
		for(int i = L[0]; i != 0; i = L[i]){
			if(S[i] < S[c]) c = i;
		}
		for(int i = U[c]; i != c; i = U[i]){
			ReMove(i);
			for(int j = L[i]; j != i; j = L[j]) ReMove(j);
			Dance(d+1);
			for(int j = R[i]; j != i; j = R[j]) ReSume(j);
			ReSume(i);
		}
	}

	int GetAnsd(){
		return ansd;
	}
}dlx;

int main(){
	while(~scanf("%d %d", &m, &n)){
		if(n == 0 && m == 0) break;
		int col_size =0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				scanf("%d", &fold_size[i][j]);
				if(fold_size[i][j]){
					pane_id[i][j] = ++col_size; //为每一块需要覆盖的地砖编号，方便建立下面的十字（链）表
				}else{
					pane_id[i][j] = 0;
				}
			}
		}

		//DP，预处理出每块以(i,j)为覆盖地毯的左上角，可以覆盖到的最范围（边长表示）
		for(int i = n - 2; i >= 0; i--){
			for(int j = m - 2; j >= 0;j--){
				if(fold_size[i][j]){
					fold_size[i][j] = min(fold_size[i+1][j], min(fold_size[i][j+1], fold_size[i+1][j+1])) + 1;
				}
			}
		}

		//过掉被完全包含在其他地毯内的地毯，令其变长fold_size[][] = 0;
		int row_size = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(fold_size[i][j]){
					bool is_folded = false;
					for(int x = 0; x <= i && !is_folded; x++){
						for(int y = 0; y <= j && !is_folded; y++){
							if(x == i && y == j) continue;
							if(x + fold_size[x][y] >= i + fold_size[i][j] && y + fold_size[x][y] >= j + fold_size[i][j]){
								is_folded = true;
								fold_size[i][j] = 0;
							}
						}
					}
					if(is_folded == false){
						++row_size;
					}
				}
			}
		}

		//初始化舞蹈链
		dlx.Init(row_size, col_size);
		
		//建立舞蹈链
		int tmp_row_size = 1;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(fold_size[i][j]){
					for(int x = 0; x < fold_size[i][j]; x++){
						for(int y = 0; y < fold_size[i][j]; y++){
							if(pane_id[i+x][j+y]){
								dlx.Link(tmp_row_size, pane_id[i+x][j+y]);
							}
						}
					}
					tmp_row_size++;
				}
			}
		}

		dlx.Dance(0); //求最小覆盖地毯数
		printf("%d\n", dlx.GetAnsd());
	}
	return 0;
}
