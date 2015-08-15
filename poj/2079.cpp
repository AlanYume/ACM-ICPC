/****** 旋转卡壳 *********/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define EPS (1e-10)
const int kMaxN = 50000 + 16;

class Point{
public:
	double x, y;

	bool operator < (const Point &tmp_p) const{
		if(x != tmp_p.x) return x < tmp_p.x;
		return y < tmp_p.y;
	}

	Point() {}
	Point(double x, double y) : x(x), y(y) {}

	double Add(double a, double b){
		if(abs(a + b) < EPS*(abs(a) + abs(b))) return 0;
		return a + b;
	}

	Point operator + (Point p){
		return Point(Add(x, p.x), Add(y, p.y));
	}

	Point operator - (Point p){
		return Point(Add(x, -p.x), Add(y, -p.y));
	}

	Point operator * (double d){
		return Point(x * d, y * d);
	}

	double Dot(Point p){ //内积
		return Add(x * p.x, y * p.y);
	}

	double Det(Point p){ //外积
		return Add(x * p.y, -y * p.x);
	}
};

int n;
Point ps[kMaxN];

vector<Point> Convex_hull(Point *ps, int n){
	sort(ps, ps + n);
	int k = 0;
	vector<Point> qs(n<<1);
	for(int i = 0; i < n; i++){
		while(k > 1 && (qs[k-1] - qs[k-2]).Det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	for(int i = n - 2, t = k; i >= 0; i--){
		while(k > t && (qs[k-1] - qs[k-2]).Det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k-1);
	return qs;
}

double GetArea(Point &p1, Point &p2, Point &p3){
	double s = 0;
	s = p1.Det(p2) + p2.Det(p3) + p3.Det(p1);
	if(s < 0) s = -s;
	return s;
}

void GetMaxArea(){
	vector<Point> qs = Convex_hull(ps, n);

	double max_are = 0;
   	int size = qs.size();
	for(int i = 0; i < size; i++){
		int j = (i + 1) % size;
		int k = (j + 1) % size;
		while(k != i && GetArea(qs[i], qs[j], qs[k]) < GetArea(qs[i], qs[j], qs[(k+1)%size])) k = (k+1)%size;

		if(k == i) continue;

		int tmp_k = (k+1)%size;
		while(j != tmp_k && k != i){
			max_are = max(max_are, GetArea(qs[i], qs[j], qs[k]));
			while(k != i && GetArea(qs[i], qs[j], qs[k]) < GetArea(qs[i], qs[j], qs[(k+1)%size])) k = (k+1)%size;
			j = (j+1)%size;
		}
	}
	printf("%.2f\n", max_are / 2);
}

int main(){
	while(~scanf("%d", &n)){
		if(n == -1) break;
		for(int i = 0; i < n; i++){
			scanf("%lf %lf", &ps[i].x, &ps[i].y);
		}
		GetMaxArea();
	}
	return 0;
}

