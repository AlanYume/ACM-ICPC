//TOJ 2894 
#include<stdio.h>
#include<queue>
#include<map>
using namespace std;
struct Message
{
	char m[20];
	int pri,par,t;
}mes;
bool operator < (Message a,Message b)
{
	if(a.pri!=b.pri)
		return a.pri>b.pri;
	return a.t>b.t;
}
main()
{
	char cmd[4];
	map<int,int> mymap;
	priority_queue<Message> pq;
	while(~scanf("%s",cmd))
	{
		if(cmd[0]=='P')
		{
			scanf("%s %d %d",mes.m,&mes.par,&mes.pri);
			mes.t=mymap[mes.pri]++;
			pq.push(mes);
			
		}
		else
		{
			if(pq.empty())
				puts("EMPTY QUEUE!");
			else
			{
				mes=pq.top();
				pq.pop();
				printf("%s %d\n",mes.m,mes.par);
			}
		}
	}	
}