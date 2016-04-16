//transform()  转换字符串的大小写
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
	string s1,s2;
	cin>>s1>>s2;
	transform(s1.begin(),s1.end(),s2.begin(),tolower);  //把s1串中转换为小写字符赋值给s2
	cout<<s1<<endl<<s2<<endl;
	transform(s1.begin(),s1.end(),s2.begin(),toupper);  //把s1串中转换为大写字符赋值给s2
	cout<<s1<<endl<<s2<<endl;
}
/*
#include<stdio.h>
#include<string.h>
int main()
{
	char a[10];
	gets(a);
	puts(a);
	strlwr(a);
	puts(a);
	strupr(a);
	puts(a);
}
*/