//memset()  函数是按位赋值的 
#include<stdio.h>
#include<string.h>
int main()
{
	char a[10];
	memset(a,'A',sizeof(a));
	for(int i=0;i<10;i++)
		printf("%c ",a[i]);
	printf("\n");
	int b[10];
	memset(b,0,sizeof(b));
	for(int i=0;i<10;i++)
		printf("%d ",b[i]);
	printf("\n");
	memset(b,1,sizeof(b));
	for(int i=0;i<10;i++)
		printf("%d ",b[i]);
	printf("\n");
	memset(b,'1',sizeof(b));
	for(int i=0;i<10;i++)
		printf("%d ",b[i]);
	printf("\n");
}