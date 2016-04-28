/*********** 状态递推 (找规律，强大了) ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int y, m, d;

//必胜态：在所有可推导的状态里至少存在一个比赛必败态
//1、(m+d)偶数全为必胜态：在可推导的状态里必存在一个（m+d）为奇数（这里不够严谨，加上“且该奇数对应的状态为必败态”））
//2、 对于（m+d）为奇数的，只要在其后的可推导状态里存在必败态，则该状态必胜
//必败态：在所有可推导的状态里全为必胜态
inline bool CheckWin(){
    if((m + d) % 2 == 0) return true;
    if(d == 30 && (m == 9 || m == 11) ) return true;
    return false;
}

int main(){
    int test;
    scanf("%d", &test);
    while(test--){
        scanf("%d %d %d", &y, &m, &d);
        printf("%s\n", CheckWin() ? "YES" : "NO");
    }
    return 0;
}
