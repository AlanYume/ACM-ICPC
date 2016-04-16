//映射 map 容器
/*
Map < key ,value > 类型 
插入元素时会自动排序。
关键字 key 唯一，不能重复，重复的话等于修改。
make_pair（ElemType, ElemType）返回一个pair。
例子：
	pair<int, string> t(1,”string”)
	pair<int, string> t=make_pair(1,”string”)
	可以通过t.first, t.second 访问pair的成员。
*/
#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<string,int> m;
	m["crq"]=100;
	m.insert(make_pair<string, int>("metoo",90));
	//等价于 m.insert(make_pair("metoo",90))
	//等价于 m["metoo"]=90;
	m["metoo"]++;
	map<string,int>::iterator it;
	for(it=m.begin();it!=m.end();it++)
		cout<<it->first<<" "<<it->second<<endl;
} 