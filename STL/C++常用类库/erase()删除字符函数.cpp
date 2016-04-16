//erase() 删除字符函数
#include<string>
#include<iostream>
using namespace std;
int main()
{
	string s="hello, world!";
	string ss1 = s.erase(6);//删除第6个字符开始的所有字符
	string ss2 = s.erase(1,2); //删除第1个字符开始的连续的2个字符
	cout<<s<<endl<<ss1<<endl<<ss2<<endl;
}