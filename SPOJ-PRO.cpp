/********** 线段树（返回区间中指定个数的节点对应的下标）***************/
//http://www.spoj.com/problems/PRO/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMnodexN = 1000000 + 16;
typedef long long ll;

int n;
ll node[kMnodexN << 2];

//为编号为x的节点对应的个数 +1
void Updnodete(int l, int r, int rt, int x){
	if(l == r){
		node[rt]++;
		return;
	}
	int m = (l + r) >> 1;
	if(x <= m){
		Updnodete(l, m, rt << 1, x);
	}else{
		Updnodete(m + 1, r, rt << 1 | 1 , x);
	}
	node[rt] = node[rt << 1] + node[rt << 1 | 1];
}

//返回元素个数达到x时 的那个节点的下标
int Query(int l, int r, int rt, ll x){
	if(l == r){
		node[rt]--;
		return l;
	}
	int m = (l + r) >> 1;
	int node_id;
	if(x <= node[rt << 1]){
		node_id = Query(l, m, rt << 1, x);
	}else{
		node_id = Query(m + 1, r, rt << 1 | 1, x - node[rt << 1]);
	}
	node[rt] = node[rt << 1] + node[rt << 1 | 1];
	return node_id;
}

int main(){
	scanf("%d", &n);
	
	ll tmp_num = 0, ans = 0;
	for(int i = 1; i <= n; i++){
		int m;
		scanf("%d", &m);
		tmp_num += m;
		while(m--){
			int x;
			scanf("%d", &x);
			Updnodete(1, 1000000, 1, x);
		}
		int sum1 = Query(1, 1000000, 1, 1);
		int sum2 = Query(1, 1000000, 1, tmp_num - 1);
		tmp_num -= 2;
		ans += sum2 - sum1;
	}
	printf("%lld\n", ans);
	return 0;
}