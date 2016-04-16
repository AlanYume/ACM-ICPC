//substr() 求字串函数
#include<string>
#include<iostream>
using namespace std;
int main ()
{
	string s="hello, world!";
	string ss1=s.substr(2);
	string ss2=s.substr(2,3);
	cout<<ss1<<endl<<ss2<<endl;
}
