#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MAX_N = 40010;

struct Circle {
	double x, y, r;

	bool insideCircle(const Circle &c) const {
		double tmpX = x - c.x;
		double tmpY = y - c.y;
		return tmpX * tmpX + tmpY * tmpY <= r * r;
	}
};

int N;
Circle c[MAX_N];

void Solve() {
	//枚举关键点
	vector<pair<double, int> > events; //圆的左右端点的x坐标
	for (int i = 0; i < N; i++) {
		events.push_back(make_pair(c[i].x - c[i].r, i));
		events.push_back(make_pair(c[i].x + c[i].r, i + N));
	}
	sort(events.begin(), events.end());

	//平面扫描
	set<pair<double, int> > outers; //与扫描线相交的最外层的圆的集合(二叉树维护）
	vector<int> res; //最外层的圆的列表
	for (int i = 0; i < events.size(); i++) {
		int id = events[i].second % N;
		if (events[i].second < N) { //扫描到左端点
			set<pair<double, int> > :: iterator it = outers.lower_bound(make_pair(c[id].y, id));
			if (it != outers.end() && c[it->second].insideCircle(c[id])) continue;
			if (it != outers.begin() && c[(--it)->second].insideCircle(c[id])) continue;
			res.push_back(id);
			outers.insert(make_pair(c[id].y, id));
		} else {
			outers.erase(make_pair(c[id].y, id));
		}
	}

	sort(res.begin(), res.end());
	printf("%d\n", res.size());
	for (int i = 0; i < res.size(); i++) {
		printf("%d%c", res[i] + 1, i + 1 == res.size() ? '\n' : ' ');
	}
}

void Read() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%lf %lf %lf", &c[i].r, &c[i].x, &c[i].y);
	}
}

int main() {
	Read();
	Solve();
	return 0;
}
