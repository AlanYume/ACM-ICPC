//a.fnind(b) 函数 查找字符串 
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a,b;
	int pos;
	cin>>a>>b;
	pos=a.find(b); // 当查找成功返回下标  不成功则返回string::npos 
	while(pos!=string::npos)
	{
		cout<<pos<<endl;
		pos=a.find(b,pos+b.size());
	}
} 