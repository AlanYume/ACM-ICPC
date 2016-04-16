// multimap 多重映射
 /*
lower_bound(k)返回一个迭代器，
		指向first不小于k的第一个元素
upper_bound(k)返回一个迭代器，
		指向first大于k的第一个元素 
equal_range()函数查找multimap中键值等于key的
	   所有元素，返回指示范围的两个迭代器 
find()  函数返回的是第一个找到的元素的位置  
*/
 #include<iostream>
 #include<map>
 using namespace std;
 int main()
 {
    typedef std::multimap<int,int> Pairs; 
	//宏定义：Pairs 取代 multimap<int,int>
	multimap<int,int>::iterator iter; 
	Pairs pairs;  
	pairs.insert(make_pair(1,5));  
	pairs.insert(make_pair(1,2));  
	pairs.insert(make_pair(1,3));  
	pairs.insert(make_pair(2,4));  
	pairs.insert(make_pair(2,5));  
	pairs.insert(make_pair(3,2));
	
	/*或者 
	int key = 1;
	Pairs::iterator position = pairs.lower_bound(key);  
	while(position != pairs.upper_bound(key))  
	{  
	    cout << position->first << " "<< position->second<<endl;  
	    ++position;  
	}*/	
	
	iter=pairs.find(1);  
	 //find返回的是第一个找到的元素的位置  
 	 //否则返回 pairs.end() 
    if(iter==pairs.end())
 		cout<<"can not find 1\n";
    else
		cout<<iter->second<<endl;
    pair<Pairs::iterator,Pairs::iterator> range;
    //这样 range 就可以存储 pair的两个迭代器了 
    //前面说了find只能返回第一个位置  
    range = pairs.equal_range(1);
    //equal_range()函数查找multimap中键值等于key的
	//所有元素，返回指示范围的两个迭代器 
    for(iter=range.first;iter!=range.second;iter++)  
        cout<<iter->first<<" "<<iter->second<<endl;

}