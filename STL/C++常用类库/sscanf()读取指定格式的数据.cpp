//sscanf()  函数从一个字符串中读进与指定格式相符的数据.
#include<stdio.h>
int main()
{
	char buf[100];
	sscanf("iios/12DDWDFF@122","%*[^/]/%[^@]",buf);//获取 / 和 @ 之间的字符串，先将 "iios/"过滤掉，再将非'@'的一串内容送到buf中
	printf("%s\n",buf);
}