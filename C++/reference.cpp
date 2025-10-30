#include<iostream>

using namespace std;
int main()
{
	int data =10, data2=20;
	int &ref=data;
	
	int* pointer= &data;
	int* &ptr_ref= pointer;
	int* pointer2= &data2;
	
	cout<<"data address--"<<&data<<"data2 address--"<<&data2<<endl; //data address ---data2 address

	cout<<"ref---"<<ref<<"---ref address--"<<&ref<<endl;//10 and data address
	ref= data2;
	cout<<"ref---"<<ref<<"---ref address--"<<&ref<<endl;//20 and data address
	
	cout<<"ptr_ref---"<<ptr_ref<<"---ptr_ref deref--"<<*ptr_ref<<endl; //data address and 20 
	
	cout<<"pointer"<<pointer<<"---pointer deref--"<<*pointer<<endl; //data addres and 20

	ptr_ref=pointer2;

	cout<<"ptr_ref---"<<ptr_ref<<"---ptr_ref deref--"<<*ptr_ref<<endl; //data2 address and 20
	 
return 0;
}
	
