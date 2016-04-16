//队列（queue）容器
#include<iostream>
#include<queue>
//#include<string>
using namespace std;
int main()
{
	queue<string>que;
	que.push("C++");
	que.push("is");
	que.push("powerfull");
	que.push("language");
	cout<<"size:"<<que.size()<<endl;
	cout<<"front:"<<que.front()<<endl;
	cout<<"back:"<<que.back()<<endl;
	while(!que.empty())
	{
		cout<<que.front()<<" ";
		que.pop();
	}
	cout<<endl;
}