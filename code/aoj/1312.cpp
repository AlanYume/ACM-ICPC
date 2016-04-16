/*************** Hash 块模式匹配 *********************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long long ull;
const int kMaxW = 1000 + 16;
const int kMaxH = 1000 + 16;
const int kMaxP = 100 + 16;

int w, h, p;
bool field[kMaxH][kMaxW]; //匹配对象
bool patterns[8][kMaxH][kMaxW]; //匹配模式
vector<ull> patterns_val;

ull hash_m[kMaxH][kMaxW], tmp[kMaxW][kMaxH];


inline int ChangeToNumber(char ch){
	if(ch >= 'A' && ch <= 'Z') return ch - 'A';
	if(ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
	if(ch >= '0' && ch <= '9') return ch - '0' + 52;
	if(ch == '+') return 62;
	if(ch == '/') return 63;
}

void Compute_hash(bool a[kMaxH][kMaxW], int n, int m){
	const ull B1 = 9973;
	const ull B2 = 100000007;

	ull t1 = 1; //B1 的 p次方
	for(int j = 0; j < p; j++) t1 *= B1;
	//按行方向计算哈系
	for(int i = 0; i < n; i++){
		ull e = 0;
		for(int j = 0; j < p; j++) e = e * B1 + a[i][j];

		for(int j = 0; j + p <= m; j++){
			tmp[i][j] = e;
			if(j + p < m) e = e * B1 - t1 * a[i][j] + a[i][j + p];
		}
	}

	ull t2 = 1; //B2 的 p次方
	for(int i = 0; i < p; i++) t2 *= B2;
	//按列方向计算哈系
	for(int j = 0; j + p <= m; j++){
		ull e = 0;
		for(int i = 0; i < p; i++) e = e * B2 + tmp[i][j];

		for(int i = 0; i + p <= n; i++){
			hash_m[i][j] = e;
			if(i + p < n) e = e * B2 - t2 * tmp[i][j] + tmp[i + p][j];
		}
	}
}

int Solve(){
	patterns_val.clear();
	for(int k = 0; k < 8; k++){
		Compute_hash(patterns[k], p, p);
		patterns_val.push_back(hash_m[0][0]);
	}

	int ans = 0;
	Compute_hash(field, h, w);
	for(int i = 0; i + p <= h; i++){
		for(int j = 0; j + p <= w; j++){
			for(int k = 0; k < 8; k++){
				if(hash_m[i][j] == patterns_val[k]){
					ans += 1;
					break;
				}
			}
		}
	}

	return ans;
}

int main(){
	while(~scanf("%d %d %d", &w, &h, &p)){
		if(w == 0 && h == 0 && p == 0) break;

		//读入并生成匹配块
		for(int i = 0; i < h; i++){
			char str[kMaxW];
			scanf("%s", str);
			for(int j = 0; j < (w + 5) / 6; j++){
				str[j] = ChangeToNumber(str[j]);
			}
			for(int j = 0; j < w; j++){
				field[i][j] = (str[j / 6] >> (5 - j % 6)) & 1;
			}
		}

		//读入并生成模式块
		for(int i = 0; i < p; i++){
			char str[kMaxP];
			scanf("%s", str);
			for(int j = 0; j < (p + 5) / 6; j++){
				str[j] = ChangeToNumber(str[j]);
			}
			for(int j = 0; j < p; j++){
				patterns[0][i][j] = (str[j / 6] >> (5 - j % 6)) & 1;
			}
		}

		//转义生成其他7中模式块
		//逆时针旋转
		for(int k = 1; k < 4; k++){
			for(int i = 0; i < p; i++){
				for(int j = 0; j < p; j++){
					patterns[k][i][j] = patterns[k - 1][p - j - 1][i];
				}
			}
		}
		//镜像对称
		for(int k = 0; k < 4; k++){
			for(int i = 0; i < p; i++){
				for(int j = 0; j < p; j++){
					patterns[k + 4][i][j] = patterns[k][i][p - j - 1];
				}
			}
		}

		printf("%d\n", Solve());
	}

	return 0;
}