#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	int data;
	cout<< "enter the data"<< endl;
	cin>> data;
	cout<< "Decimal val: "<<data<<endl;
	cout<< "Octal val : "<<oct<<data<<endl;
	cout<< "Hex val : "<<hex<<data<<endl;
	cout<< "Binary val : "<<bitset<32>(data)<<endl;
}
