//strtok(a,b)函数已b中出现的任意字符分割字符串a 
#include<stdio.h>
#include<string.h>
int main()
{
	char a[100],b[10],*p;
	gets(a);
	gets(b); 
	p=strtok(a,b);
	while(p!=NULL)
	{
		puts(p);
		p=strtok(NULL,b);
	}
	puts(a);//注意！！原字符串已经被修改 
}