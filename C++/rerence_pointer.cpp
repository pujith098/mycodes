#include <iostream>
using namespace std;

int main()
{
	int data =12;
	int* pointer =&data;
	int* &reference_pointer = pointer;
	int* another_pointer = pointer;
	
	cout<<"&data : - "<<&data<<endl;
        cout<<"*pointer : - "<<*pointer<<endl;
	cout<<"pointer : - "<<pointer<<endl;
        cout<<"&pointer : - "<<&pointer<<endl;
	cout<<"refence_pointer: -" <<reference_pointer<<endl;
	cout<<"*refence_pointer: -"<<*reference_pointer<<endl;
	cout<<"&reference_pointer: -"<<&reference_pointer<<endl;

	cout<<"*another_pointer : -"<<*another_pointer<<endl;
	cout<<"another_pointer : -"<<another_pointer<<endl;
}
	 
