//首先dp 数组必须已经按按升序排列，然后lower_bound（）
//以基于二分搜索的方式查找dp - dp[n] 之内的大于等于a[i]
//的第一个元素，并返回其下标
#include<iostream>
using namespace std;
const int INF = 4000000;
int N, A[1000010];
int dp[1000010];
int main()
{
	while(~scanf("%d", &N))
	{
		for(int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		fill(dp, dp + N, INF);
		for(int i = 0; i < N; i++)
			*lower_bound(dp, dp + N, A[i]) = A[i];
		printf("%d\n", lower_bound(dp, dp + N, INF) - dp);
	}
	return 0;
}