#include<iostream>
#include<string>
using namespace std;

template <typename T>
void sum(T a, T b)
{
	cout <<a+b<<endl;
}
int main()
{
	sum(10,12);
	sum(12.25,12.25);
	sum((string)"ujith",(string)"kumar");
	return 0;
}

