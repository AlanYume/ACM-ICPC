//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1005&cid=42
//map 二叉树
#include<iostream>
#include<string>
#include<map>
using namespace std;
int main()
{
	char str[50];
	int count=0;
	map <string,int> counter;
	map <string,int> ::iterator it;
	while(gets(str)!=NULL)
	{
		//对于map容器，如果下标所表示的键在容器中不存在，则添加新元素
		counter [str]++;
		count++; 
	}
	cout.setf(ios::fixed);       //以定点形式显示浮点数
	cout.precision(4);           //设置小数部分的有数数字  4位
	for(it=counter.begin();it!=counter.end();it++)
	{
		double per =100*(double)it->second/(double)count;
		cout<<it->first<<" "<<per<<endl;
	}
	system("pause");
	return 0;
} 