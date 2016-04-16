//集合（set）容器
/*
插入元素时会自动排序。
自动排序的主要优点在于使二叉树查找元素时具有良好性能。O(log(n))的查找复杂度。
插入的值不能重复，重复的话等于覆盖。
*/
#include<iostream>
#include<set>
using namespace std;
int main()
{
	int i,ary[]={5,3,7,5,2,3,7,5,5,4},bry[]={5,6,0,6,-19}; 
	set<int>s1;  //默认按照从小到大排序 less<int>
	set<int>s2;  //加上  ,greater<int>  试试  
	                    //按照从大到小排序 greater<int>
	set<int>::iterator It;
	for(i=0;i<sizeof(ary)/sizeof(int);i++)
		s1.insert(ary[i]);
	cout<<"S1:";
	for(It=s1.begin();It!=s1.end();It++)
		cout<<*It<<" ";
	cout<<endl;
	cout<<"size:"<<s1.size()<<endl;
	for(i=0;i<sizeof(bry)/sizeof(int);i++)
		s2.insert(bry[i]);
	cout<<"S2:";
	It=s2.begin();
	while(It!=s2.end())
		cout<<*(It++)<<" ";
	cout<<endl;
	cout<<"size:"<<s2.size()<<endl;
//如果要进行集合运算  两个集合必须都是默认 从小到大 排序的 
	set<int> si;
	set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(si,si.begin()));
	//Si为 S1 与 S2求 交 后的集合
	cout<<"交集:";
	It=si.begin();
	while(It!=si.end())
		cout<<*(It++)<<" ";
	cout<<endl;
	si.clear();
	set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(si,si.begin()));
	//............	求 并 后的集合 
	cout<<"并集"; 
	It=si.begin();
	while(It!=si.end())
		cout<<*(It++)<<" ";
	cout<<endl;
	si.clear();
	set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(si,si.begin()));
	//用于求两个集合的差集，结果集合中包含所有属于第一个集合但不属于第二个集合的元素。
	cout<<"差集"; 
    It=si.begin();
	while(It!=si.end())
		cout<<*(It++)<<" ";
	cout<<endl;
}