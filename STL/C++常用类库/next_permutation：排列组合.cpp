//排列组合：next_permutation 函数 
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	char str[210];
	int count=1;
	cin>>str;
	int len=strlen(str);
	sort(str,str+len);
	do
	{
		printf("%d %s\n",count++,str);
	}while(next_permutation(str,str+len));
}