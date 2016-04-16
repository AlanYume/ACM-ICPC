//replace() 替换字符函数
#include<string>
#include<iostream>
using namespace std;
int main()
{
	string s="hello, world!"; 
	s.replace(7,6,"");
	//删除第7个字符后的6个字符，以空串代替
	cout<<s<<endl;
	s.replace(7,6,"crq");
	//删除第7个字符后的6个字符，以"crq"代替
	cout<<s<<endl; 
	s.replace(7,3,"carterchen",6);
	//删除第7个字符后3个字符,以"caterchen"前6个字符代替
	cout<<s<<endl;
	s.replace(7,6,3,'z');
	//删除第7个字符后的6个字符,以3个'z'字符代替
	cout<<s<<endl;
	//...还有很多用法，自行参考资料
}