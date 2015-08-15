/*************** ���㼸�� ******************/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define EPS (1e-10)

double add(double a, double b)
{
	if(fabs(a + b) < EPS * (fabs(a) + fabs(b)))
		return 0;
	return a + b;
}

struct P
{
	double x, y;
	P() {}
	P(double x, double y) : x(x), y(y) {}
	P operator + (P p)
	{
		return P(add(x, p.x), add(y, p.y));
	}
	P operator -(P p)
	{
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator *(double d)
	{
		return P(x * d, y * d);
	}
	double dot(P p)  //�ڻ�
	{
		return add(x * p.x, y * p.y);
	}
	double det(P p)  //���
	{
		return add(x * p.y, -y * p.x);
	}
};

//�жϵ�q�Ƿ����߶�p1 - p2 ��
bool on_seg(P p1, P p2, P q)
{
	return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

//����ֱ��p1-p2�� ֱ�� q1 -q2 �Ľ���
P intersection(P p1, P p2, P q1, P q2)
{
	return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

//�жϽϸߵ��Ƿ���ס�ϵ͵�
bool BeHide(P p1, P p2, P p_jiao)
{
	if(p1.y < p2. y)
		swap(p1, p2);
	if(p1.x <= p2.x && p2.x < p_jiao.x && (p1 - p_jiao).det(p2 - p_jiao) > EPS)
		return true;
	if(p1.x >= p2.x && p2.x > p_jiao.x && (p1 - p_jiao).det(p2 - p_jiao) < EPS)
		return true;
	return false;
}

int main()
{
	int test;
	scanf("%d", &test);
	while(test--){
        P p1, p2, q1, q2;
        scanf("%lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y);
		scanf("%lf %lf %lf %lf", &q1.x, &q1.y, &q2.x, &q2.y);

		if(p1.y == p2.y || q1.y == q2.y)   //����ˮƽ�߶�
		{
			printf("0.00\n");
			continue;
		}
		if(p1.y < p2.y)
			swap(p1, p2);
		if(q1.y < q2.y)
			swap(q1, q2);

		//���㽻��
		P p_jiao = intersection(p1, p2, q1, q2);

		//���߶β�ƽ�У��غϣ� �� ���ڽ���
		if((p1 - p2).det(q1 - q2) != 0 && on_seg(p1, p2, p_jiao) && on_seg(q1, q2, p_jiao))
		{
			double min_y = min(p1.y, q1.y);

			if(fabs(p_jiao.y - min_y) <= EPS || BeHide(p1, q1, p_jiao))   //����������һ���߶ε���ߵ�ȸ�
			{
				printf("0.00\n");
				continue;
			}
			else
			{
				P tmp_p;
				if(p1.y >= q1.y)
				{
					tmp_p = intersection(q1, P(q1.x + 1000, q1.y), p1, p2);
					printf("%.2f\n", fabs(0.5 * (tmp_p - p_jiao).det(q1 - p_jiao)) + EPS);
				}
				else
				{
					tmp_p = intersection(p1, P(p1.x + 1000, p1.y), q1, q2);
					printf("%.2f\n", fabs(0.5 * (tmp_p - p_jiao).det(p1 - p_jiao)) + EPS);
				}
			}
		}
		else
		{
			printf("0.00\n");
		}
	}
	return 0;
}