/*********** 位运算 + 二分 *******************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 1000;
const int kMaxSize = 200 + 16;
const int dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};

struct Point{
	int x, y;
};

int n, m;
char filed[kMaxSize][kMaxSize];
int point_size;
Point p[15 + 6];
bool isLight[15 + 6];

inline int CanShut(int x, int y){
	if(x >= 0 && x < n && y >= 0 && y < m){
		if(filed[x][y] == '#'){ //不可被照射点
			return -1;
		}else{
			return 0; //当前照射点可以被照射到
		}
	}else{
		return 1; //当前被照射点已经在区域外
	}
}

int Solve(int bit){ //函数返回 0，表示bit是可行方案，否则放回 kINF

	Point tmp[2];
	for(int i = 0; i < point_size; i++){ //考虑对第i栈灯进行旋转，其他使用默认
		if((bit >> i) & 1){
			for(int k = 0; k < 4; k++){ //第i栈灯分别进行4个方向旋转
				memset(isLight, false, sizeof(isLight));
				tmp[0].x = p[i].x + dir[k][0];
				tmp[0].y = p[i].y + dir[k][1];
				tmp[1].x = p[i].x + dir[(k + 1) % 4][0];
				tmp[1].y = p[i].y + dir[(k + 1) % 4][1];
				int tmp_val_1 = CanShut(tmp[0].x, tmp[0].y);
				int tmp_val_2 = CanShut(tmp[1].x, tmp[1].y);
				if(tmp_val_1 == -1 || tmp_val_2 == -1){
					continue;
				}else{
					isLight[i] = true;
					if(tmp_val_1 == 0) isLight[ filed[ tmp[0].x ][ tmp[0].y  ] ] = true;
					if(tmp_val_2 == 0) isLight[ filed[ tmp[1].x ][ tmp[1].y  ] ] = true;


					for(int j = 0; j < point_size; j++){
						if( ((bit >> j) & 1) && i != j ){ //判断第j栈灯使用默认照射的可行性
							tmp[0].x = p[j].x + dir[0][0];
							tmp[0].y = p[j].y + dir[0][1];
							tmp[1].x = p[j].x + dir[1][0];
							tmp[1].y = p[j].y + dir[1][1];
							int tmp_val_1 = CanShut(tmp[0].x, tmp[0].y);
							int tmp_val_2 = CanShut(tmp[1].x, tmp[1].y);
							if(tmp_val_1 == -1 || tmp_val_2 == -1){

							}else{
								if(tmp_val_1 == 0) isLight[ filed[ tmp[0].x ][ tmp[0].y  ] ] = true;
								if(tmp_val_2 == 0) isLight[ filed[ tmp[1].x ][ tmp[1].y  ] ] = true;
								isLight[j] = true;
							}
						}
					}

					bool can_shut = true;
					for(int l = 0; l < point_size; l++){
						if(isLight[l] == false){
							can_shut = false;
						}
					}
					if(can_shut) return 0;

				}
			}
		}
	}

	return kINF;
}

int main(){
	while(~scanf("%d %d", &n, &m)){
		if(n == 0 && m == 0) break;

		point_size = 0;
		for(int i = 0; i < n; i++){
			scanf("%s", filed[i]);
			for(int j = 0; j < m; j++){
				if(filed[i][j] == '.'){
					p[point_size].x = i;
					p[point_size].y = j;
					filed[i][j] = point_size;
					point_size++;
				}
			}
		}

		int ans = kINF;
		if(point_size == 0){
			ans = 0;
		}else{

			int limit = (1 << point_size);

			//二分枚举最少需要的灯的个数
			int l = 1, r = point_size ;
			while(r >= l){
				int mid = (l + r) >> 1;

				bool have_ans = false;
				int comb = (1 << mid) - 1; //枚举所有元素个数为mid个的子集
				while(comb < limit && have_ans == false){
					int tmp_ans = Solve(comb);
					if(tmp_ans != kINF){
						ans = mid;
						have_ans = true;
					}
					int x = comb & -comb, y = comb + x;
					comb = ((comb & ~y) / x >> 1) | y;
				}

				if(have_ans == true){
					r = mid - 1;
				}else{
					l = mid + 1;
				}

			}
		}

		if(ans == kINF){
			printf("-1\n");
		}else{
			printf("%d\n", ans);
		}
	}
	return 0;
}

/*

3 3
.#.
###
.#.

*/