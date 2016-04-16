/**************  ˼ά *****************/
#include<cstdio>
#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<int,int> lm;
	map<int,int> rm;
	map<int,int>::iterator it;
	int n,k,i,wei;
	int num[100010];
	int sumnum;
	while(~scanf("%d %d",&n,&k))
	{
		lm.clear();
		rm.clear();
		sumnum=0;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&num[i]);
			if(num[i]==k)
				wei=i;
		}
		int geshu=0;
		for(i=wei-1;i>=1;i--)
			if(num[i]>num[wei])
			{
				geshu++;
				lm[geshu]++;
			}
			else
			{
				geshu--;
				lm[geshu]++;
			}
		geshu=0;
		for(i=wei+1;i<=n;i++)
			if(num[i]>num[wei])
			{
				geshu++;
				rm[geshu]++;
			}
			else
			{
				geshu--;
				rm[geshu]++;
			}
		lm[0]++;
		rm[0]++;
		for(it=lm.begin();it!=lm.end();it++)
			sumnum+=(it->second)*rm[-(it->first)];
		printf("%d\n",sumnum);
	}
	return 0;
}