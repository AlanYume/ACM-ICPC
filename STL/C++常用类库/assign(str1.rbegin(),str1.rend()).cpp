//str2.assign(str1.rbegin(),str1.rend())  函数对字符串倒置 
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str1,str2;
	cin>>str1;
	str2.assign(str1.rbegin(),str1.rend());  //字符串倒置 
	cout<<str1<<endl<<str2<<endl;
	cin>>str1;
	str2.assign(str1.begin(),str1.end());    //字符串拷贝 
	cout<<str1<<endl<<str2<<endl;
}



#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str;
	cin>>str;
	cout<<str<<endl;
	reverse(str.begin(),str.end());  //字符串倒置
	cout<<str<<endl;
	system("pause");
	return 0;
}