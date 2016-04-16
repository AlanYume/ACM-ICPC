#include<iostream>
using namespace std;
class Rectangle
{
   private:
	int x1,y1,x2,y2;
   public:
	void Sc();
	void Pf();
};
void Rectangle::Sc()
{
   cin>>x1>>y1>>x2>>y2;
}
void Rectangle::Pf()
{
   cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
}
int main()
{
    Rectangle a;
    a.Sc();
    a.Pf();
}