#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kMaxTime = 1000 + 16;

int t, w;
int drop_tree_id[kMaxTime];
int get_apples[2][kMaxTime];

int main(){
	scanf("%d %d", &t, &w);
	for(int i = 1; i <= t; i++){
		scanf("%d", &drop_tree_id[i]);
		get_apples[0][i] = get_apples[0][i - 1] + (drop_tree_id[i] & 1);
	}

	int ans = get_apples[0][t];

	for(int i = 1; i <= w; i++){
		for(int j = 1; j <= t; j++){
			get_apples[i & 1][j] = max(get_apples[(i - 1) & 1][j - 1], get_apples[i & 1][j - 1]) + ((i & 1) ? (drop_tree_id[j] == 2) : (drop_tree_id[j] == 1));
			ans = max(ans, get_apples[i & 1][j]);
		}
	}

	printf("%d\n", ans);

	return 0;
}