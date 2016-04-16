//multiset 多重集合 
/*
s1.insert(“abc”);
s1.insert(“abc”);
此后s1中包含2个“abc”
*/
#include<set>
#include<iostream>
using namespace std;
int main()
{
	multiset<string> s1;
	s1.insert("abc");
	s1.insert("abc");
	s1.insert("dfdd");
	s1.insert("glj");
	s1.insert("bdjddfsd");
	multiset<string>::iterator it;
	it=s1.begin();
	while(it!=s1.end())
		cout<<*(it++)<<endl;
	cout<<endl;
	it=s1.find("gj");
	if(it!=s1.end())
		cout<<*it<<endl;
	else
		cout<<"not found\n";  //注意 \n 换行 
	it=s1.find("abc");
	if(it!=s1.end())
		cout<<*it<<endl;
	else
		cout<<"not find"<<endl;
}