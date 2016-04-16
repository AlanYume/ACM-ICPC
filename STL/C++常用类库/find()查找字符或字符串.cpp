#include<iostream>
#include<string>
using namespace std;
/*main()
{
	int i,lenm;
	string m,z;
	string::size_type position;
	while(cin>>m>>z)
	{
		i=0;lenm=m.size();
		position=z.find(m);
		while(position!=string::npos)  //string::npos等价于z.npos 
		{
			i++;
			cout<<position<<endl;     //返回查找到的第一个字符的下标 
			z.erase(position,lenm);
			position=z.find(m);
		}
		cout<<i<<endl;
	}
}*/
int main()
{
	string s="hello, world!";
	string filter=",!";
	cout<<s.find('l',3)<<endl;
	//第3个开始查找字符'l'的首次出现
	cout<<s.find("lo", 7)<<" "<<string::npos<<endl;
	//字串首次出现，不存在返回string::npos
	cout<<s.rfind("lo",7)<<endl;
	//从第7个位置往前能找到
	cout<<s.find_first_of(filter,2)<<endl;
	//从第2个位置开始找在字符串filter中的字符
	cout<<s.find_last_of(filter)<<endl;
	//同上，只是从后往前找
	cout<<s.find_first_not_of(filter)<<endl;
	//不在filter中的...
	cout<<s.find_last_not_of(filter,100)<<endl;
	//从后往前
}