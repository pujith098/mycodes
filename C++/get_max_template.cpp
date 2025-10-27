#include<iostream>

using namespace std;

template <typename T>
T get_max(T var1, T var2)
{
	if(var1 > var2)
		return var1;
	else
		return var2;
}
int main()
{
	cout<<"inter max:- "<<get_max(2,4)<<endl;
	cout<<"real max:- "<<get_max(4.0,5.34)<<endl;
}
	
