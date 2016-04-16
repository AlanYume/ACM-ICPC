/*
	length(); size();  //求长度
	empty();           //判断是否为空串
	substr();          //求子串
	erase();           //删除若干个字符
	insert();          //插入字符
	replace();         //替换字符
	find系列函数;      //查找字串
        reverse(str.begin(),str.end());  //字符串倒置
*/
#include<string>
#include<iostream>
using namespace std;
int main()
{
	string s1;
	cin>>s1;
	cout<<s1.length()<<endl;
	if(s1.empty())
		cout<<"s1为空"<<endl;
	else
		cout<<"s1非空"<<endl;
	cout<<s1.substr(1,3)<<endl;//返回s1中下标为1的字符起的长为3的字串 
	reverse(str.begin(),str.end());  //字符串倒置
}