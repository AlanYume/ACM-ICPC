//priority_queue:优先队列

/*
头文件：#include <queue>

优先队列与队列的差别在于优先队列不是按照入
队的顺序出队，而是按照队列中元素的优先权顺
序出队（默认为大者优先，也可以通过指定算子
来指定自己的优先顺序）。

priority_queue模板类有三个模板参数，第一个
是元素类型，第二个容器类型，第三个是比较算
子。其中后两个都可以省略，默认容器为vector，
默认算子为less，即小的往前排，大的往后排（
出队时序列尾的元素出队）。

*/
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int main()
{
	priority_queue< int,vector<int>,less<int> > ipq; 
	 //less 从小到大排序
	 //greater  从大到小排序
	ipq.push(1);
	ipq.push(3);
	ipq.push(2);
	while(!ipq.empty())   //出队时序列尾的元素出队
	{
		cout<<ipq.top()<<" ";
		ipq.pop();
	}
	cout<<endl;
}

/*int main()
{
	priority_queue< string,vector<string>,greater<string> > ipq; 
	ipq.push("sdfljdf");
	ipq.push("adlld");
	ipq.push("zsdlldjjl");
	ipq.push("bs");
	while(!ipq.empty())
	{
		cout<<ipq.top()<<endl;
		ipq.pop();
	}
	cout<<endl;
}*/