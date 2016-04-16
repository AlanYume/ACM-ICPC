//vector：向量
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int> v;
	int i;
	for(i=0;i<=10;i++)
		v.push_back(i);
	for(i=0;i<=10;i++)
		cout<<v[i]<<" ";
	cout<<endl;
	v.pop_back();
	v.pop_back();
	vector<int>::iterator it;
	for(it=v.begin();it!=v.end();it++)
		cout<<*it<<" ";
	cout<<endl;
	v.clear();
	for(i=0;i<5;i++)
		v.push_back(i);
	for(i=0;i<=10;i++)
		cout<<v.at(i)<<" "; //v.at(i)比v[i]更加安全的访问v[i] 
	cout<<endl;
}