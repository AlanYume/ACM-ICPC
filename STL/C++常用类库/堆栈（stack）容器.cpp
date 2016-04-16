//堆栈（stack）容器
#include<iostream>
#include<stack>
using namespace std;
int main()
{
	int a=1,b=2,c=3;
	stack<int> s;
	s.push(a);
	s.push(b);
	s.push(c);
	cout<<"size:"<<s.size()<<endl;
	cout<<"top:"<<s.top()<<endl;
	s.pop();
	cout<<"size:"<<s.size()<<endl;
	cout<<"top:"<<s.top()<<endl;
	while(!s.empty())
		s.pop();
	cout<<"size:"<<s.size()<<endl;
	return 0;
}