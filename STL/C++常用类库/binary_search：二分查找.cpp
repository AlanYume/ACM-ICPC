//binary_search 二分查找
//std 里面的函数 lower_bound(vec.begin(),vec.end(),n); 
//                      返回n在vector里面的迭代器的地址 
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
	vector<int> vec;
	int n;//二分查找的前提是已经排序
	vec.push_back(1);
	vec.push_back(9);
	vec.push_back(3);
	vec.push_back(4);
	vector<int>::iterator it=vec.begin();
	while(it!=vec.end())
		cout<<*(it++)<<endl;
	sort(vec.begin(),vec.end());
	cout<<endl;
	it=vec.begin();
	while(it!=vec.end())
		cout<<*(it++)<<endl;
	while(cin>>n)
		if(binary_search(vec.begin(),vec.end(),n))
		{
			cout<<"Find"<<" "<<n<<endl;
			it = lower_bound(vec.begin(),vec.end(),n);
			cout<<"对应的位置"<<it-vec.begin()<<endl;
		}
		else
			cout<<"Not Found!"<<endl;
}