//strrev() 函数对字符串逆置 
#include<string.h>
#include<stdio.h>
int main()
{
	char a[10];
	gets(a);
	puts(a);
	strrev(a);
	puts(a);
/*	int b[10],i;
	for(i=0;i<10;i++)
		scanf("%d",&b[i]);
	for(i=0;i<10;i++)
		printf("%d ",b[i]);
	putchar('\n');
	strrev(b);     //strrev() 函数只能对 字符串 逆置 
	for(i=0;i<10;i++)
		printf("%d ",b[i]);
	putchar('\n');*/
}