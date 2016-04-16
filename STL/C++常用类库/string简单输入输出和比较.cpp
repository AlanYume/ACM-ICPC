#include<string>
#include<iostream>
using namespace std;
int main()
{
	string str,str1="Hello, word!",str2("OK");
	str=str2;
	cout<<str<<endl<<str1<<endl<<str2<<endl;
	cout<<str[10]<<"***"<<str.at(1)<<endl;
	//str[i]//返回str中索引i处字符的引用，不查是否出界
    //str.at(i)//返回str中索引i处字符的引用，查是否出界
    str1+=str2;
    cout<<str1<<endl;
    /*str1+=str2; //str2的字符数据连接到str1的尾部
	 str1+str2;  //将str2连接到str1的尾部，str1不改变
	 str1==str2;  str1!=str2;
	 str1<str2;  str1>str2;  
	 str1<=str2;  str1>=str2;//基于字典序的比较，
	                         返回布尔值，true或false*/
    getline(cin,str);//回车结束，获取整行
    cout<<str<<endl;
}