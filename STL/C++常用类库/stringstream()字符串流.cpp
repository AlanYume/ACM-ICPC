//stringstream()  字符串流 从前往后流出 
#include<iostream>
#include<sstream>
//函数功能：每行有若干个数，求其和并输出 
using namespace std;
main()
{
	string s;
	while(getline(cin,s))
	{
		stringstream ss;
		ss<<s;
		int sum=0,a;
		while(ss>>a)
		{
			sum+=a;
			cout<<a<<endl;
		}	
		cout<<sum<<endl;
	}
} 