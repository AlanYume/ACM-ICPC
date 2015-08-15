/************ 计算几何（直线） + 暴力 ****************/
//三个for循环枚举鸟时，一个注意：不能每次都从0开始，
//一开始没考虑到，所以感觉复杂度过不去
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;
const int kMaxN = 1000000 + 16;
const int kMaxM = 250 + 6;

struct Point{
	ll x, y;
};
struct Line{
	ll a, b, c;
};

int n, m, num[kMaxN];
Point p[kMaxM];

//根据两点确定一条直线：ax + by + c = 0
Line GetLine(const Point &a, const Point &b){
	Line l;
	l.a = b.y - a.y;
	l.b = a.x - b.x;
	l.c = b.x * a.y - a.x * b.y;
	return l;
}

//判断点p是否在直线l上
bool JudgeInLine(const Point &p, const Line &l){
	return (l.a * p.x + l.b * p.y + l.c == 0);
}

//已知一点的y坐标且经过直线l，求其x坐标(根据题目要求，x必须为【1，n】之间的整数
ll GetX(const ll &y, const Line &l){
	if(l.a == 0 || (l.b * y + l.c) % l.a != 0) return -1; //无解
	return -(l.b * y + l.c) / l.a;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		scanf("%I64d %I64d", &p[i].x, &p[i].y);
	}

	memset(num, 0, sizeof(num));
	for(int i = 0; i < m; i++){ //注意三个for循环枚举的i、j、k的起始值
		for(int j = i + 1; j < m; j++){
			Line tmp_l = GetLine(p[i], p[j]);
			ll x = GetX(0, tmp_l);
			if(x < 1 || x > n) continue;
			int cnt = 2;
			for(int k = j + 1; k < m; k++){
				if(JudgeInLine(p[k], tmp_l) == true) cnt += 1;
			}
			num[x] = max(num[x], cnt);
		}
	}

	int ans = 0;
	for(int i = 1; i <= n; i++){
		if(num[i] != 0){
			ans += num[i];
		}else{
			ans += 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
