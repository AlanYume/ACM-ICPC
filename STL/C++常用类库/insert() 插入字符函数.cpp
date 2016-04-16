//insert() 插入字符函数
#include<string>
#include<iostream>
using namespace std;
int main ()
{
	string s=",";
	s.insert(0,"heo"); cout<<s<<endl;//在0号位置插入整个字符串
	s.insert(4,"world",2); cout<<s<<endl;//在4号位置插入world的前2个字符wo 
	s.insert(2,2,'l');cout<<s<<endl;//在2号位置插入连个字符‘l’ 
	s.insert(s.end(),'r');cout<<s<<endl;//在字符串末尾插入字符‘r’ 
	s += "ld!";cout<<s<<endl;//在字符串末尾追加字符串“ld！” 
}