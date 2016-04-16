//find（）函数的参数 和 查找的返回值 
//注意sring 里面的find 没有找到的返回值为string::npos  特例
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
main()  {
	int array[10] = {10,20,30,40};
	vector<int> v;
	v.push_back(1);	v.push_back(2);
	v.push_back(3);	v.push_back(4);
	vector<int>::iterator p;
	p = find(v.begin(),v.end(),3);
	if( p != v.end())
		cout << * p << endl;
	p = find(v.begin(),v.end(),9);
	if( p == v.end())
		cout << "not found " << endl;
	p = find(v.begin()+1,v.end()-2,1);
	//因为在 v.begin()+1,v.end()-2,没有找到 1
	//所以返回 p=v.end()-2 (！= v.end()) =3 
	if( p != v.end())
		cout << * p << endl;
	int * pp = find( array,array+4,20);
	cout << * pp << endl;
}


#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n[]={1,4,22,3,8,5};
	int len=sizeof(n)/sizeof(int);
	cout<<*max_element(n,n+len)<<endl;
	cout<<*min_element(n,n+len)<<endl;
	return 0;
}