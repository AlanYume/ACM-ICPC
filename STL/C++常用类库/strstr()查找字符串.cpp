//strstr(str1,str2) 函数在str1串中查找 str2 出现的位置的指针 
#include<stdio.h>
#include<string.h>
int main()
{
	char a[100],b[50],*p;
	int pos;
	gets(a);
	gets(b);
	p=strstr(a,b);
	while(p!=NULL)
	{
		pos=p-a;
		printf("%d\n",pos);
		p=strstr(a+pos+strlen(b),b);
	}
}