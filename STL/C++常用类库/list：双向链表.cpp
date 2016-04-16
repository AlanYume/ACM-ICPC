// 双向链表 list 
#include<iostream>
#include<list>
using namespace std;
void DisplayMyList(list<int>&mylist)
{
	list<int>::iterator it=mylist.begin();
	// 定义一个链表的迭代器，类似于指针 
	cout<<"List Values: ";
	while(it!=mylist.end())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}
int main()
{
	list<int> mylist;
	list<int>::iterator it;
	mylist.push_back(1);  //从链表后面插入1 
	mylist.push_back(2);  //从链表后面插入2 
	cout<<"mylist size: "<<mylist.size()<<endl;
	//显示链表的长度 
	DisplayMyList(mylist);
	it=mylist.begin();
	//获取链表的头指针 
	it++;   //指向链表的第二个节点 
	mylist.insert(it,3);
	//在第二个节点之前插入3
	cout<<"mylist size: "<<mylist.size()<<endl;
	DisplayMyList(mylist);
	mylist.pop_front();
	//删除第一个节点 
	cout<<"mylist size: "<<mylist.size()<<endl;
	DisplayMyList(mylist);
}