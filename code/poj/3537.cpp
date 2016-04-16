/********** 尼姆博奕（Nimm Game）+ SG函数 **********/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <set>
using namespace std;

const int kMaxN = 2000 + 16;

int n;
int sg[kMaxN];

int GetMex(int x){
    if(x <= 0) return 0;
    if(sg[x] != -1) return sg[x];

    bool visit[kMaxN];
    memset(visit, false, sizeof(visit));
    int max_sit = (x >> 1) + (x % 2);
    for(int i = 1; i <= max_sit; i++){ //因为左右对称，所以只需枚举一半的放置位置
        visit[GetMex(x - (i + 2)) ^ GetMex(i - 3)] = true;
    }

    int cnt = 0;
    while(visit[cnt] == true) cnt++;
    return sg[x] = cnt;
}

int main(){
    memset(sg, -1, sizeof(sg));
    while(~scanf("%d", &n)){
        printf("%d\n", GetMex(n) ? 1 : 2);
    }
    return 0;
}
