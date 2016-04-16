//sprintf()  函数从一个字符串中输出与指定格式相符的数据到另一个字符串 
#include<stdio.h>
int main()
{
	char s[100];
	sprintf(s,"%6.3f",3.1415626);
	printf("%s\n",s);
}