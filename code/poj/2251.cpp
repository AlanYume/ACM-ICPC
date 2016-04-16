/*********** A* *************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

const int kINF = 30000;
const int kMaxN = 34;
const int dir[6][3]={{-1, 0, 0},
                {1, 0, 0},
                {0, -1, 0},
                {0, 1, 0},
                {0, 0, 1},
                {0, 0, -1}};

int L, R, C;
char filed[kMaxN][kMaxN][kMaxN];
int ps[kMaxN][kMaxN][kMaxN];
int s_l, s_r, s_c;
int e_l, e_r, e_c;

inline int Abs(const int &val){
	return val > 0 ? val : -val;
}

struct Node{
	int l, r, c, depth;
	Node() {}
	Node(int l, int r, int c, int depth) : l(l), r(r), c(c) , depth(depth) {}
	Node(Node tmp_node, int dir_id) : l(tmp_node.l + dir[dir_id][0]), r(tmp_node.r + dir[dir_id][1]), c(tmp_node.c + dir[dir_id][2]), depth(tmp_node.depth+1) {}

	bool operator < (const Node &tmp_node) const{
		return (depth + Abs(l - e_l) + Abs(r - e_r) + Abs(c - e_c)) > (tmp_node.depth + Abs(tmp_node.l - e_l) + Abs(tmp_node.r - e_r) + Abs(tmp_node.c - e_c));
	}

	bool InFiled(){
		if(l < 0 || l >= L || r < 0 || r >= R || c < 0 || c >= C) return false;
		if(filed[l][r][c] == '#') return false;
		return true;
	}
};

int Astart(){
	Node now_node = Node(s_l, s_r, s_c, 0);
	ps[s_l][s_r][s_c] = 0;
	priority_queue<Node> open;
	open.push(now_node);
	while(!open.empty()){
		now_node = open.top();
		open.pop();
		if(now_node.l == e_l && now_node.r == e_r && now_node.c == e_c) return now_node.depth;
		if(ps[now_node.l][now_node.r][now_node.c] == now_node.depth){
			for(int i = 0; i < 6; i++){
				Node next_node = Node(now_node, i);
				if(next_node.InFiled() && ps[next_node.l][next_node.r][next_node.c] > next_node.depth){
					ps[next_node.l][next_node.r][next_node.c] = next_node.depth;
					open.push(next_node);
				}
			}
		}
	}
	return kINF;
}

int main(){
	while(~scanf("%d %d %d", &L, &R, &C)){
		if(L == 0 && R == 0 && C == 0) break;
		for(int l = 0; l < L; l++){
			for(int r = 0; r < R; r++){
				scanf("%s", filed[l][r]);
				for(int c = 0; c < C; c++){
					if(filed[l][r][c] == 'S'){
						s_l = l; s_r = r; s_c = c;
						filed[l][r][c] = '.';
					}else if(filed[l][r][c] == 'E'){
						e_l = l; e_r = r; e_c = c;
						filed[l][r][c] = '.';
					}
					ps[l][r][c] = kINF;
				}
			}
		}
		int ans = Astart();
		if(ans == kINF){
			printf("Trapped!\n");
		}else{
			printf("Escaped in %d minute(s).\n", ans);
		}
	}
	return 0;
}
