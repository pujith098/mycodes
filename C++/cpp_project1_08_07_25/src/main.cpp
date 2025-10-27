#include <iostream>
#include <string>

using namespace std;
class student
{
	public:
		string name;
		int age;
		int marks[3];

		int average_marks(){
			return ((marks[0] + marks[1] + marks[2])/3);
		}
		student() {
			cout<<"enter the student name\n";
			cin>>name;
			cout<<"enter age of student \n";
			cin>>age;
			cout<<"enter the student marks one by one\n";
			for(int i=0;i<3;i++)
				cin>>marks[i];
		}
		student(const student &var)
		{
			cout<<"copy constructer"<<endl;
			name=var.name;
			age=var.age;
			for(int i=0;i<3;i++)
				marks[i]=var.marks[i];
		}

		void student_data_display()
		{
			cout<<"student name -"<<name<<endl;
                        cout<<"age of student "<<age<<endl;
                        for(int i=0;i<3;i++)
				 cout<<"student marks"<<i<<"-subject"<<marks[i]<<endl;
			int  val =average_marks();
			cout<<"average marks;"<<val<<endl;
			
		}

};

int max_of_num(int a, int b)
{
	if(a>b)
		cout<<"a is big"<<endl;
	else
		cout<<"b is big"<<endl;
	return 1;
}

float max_of_num(float a, float b)
{
	if(a>b)
                cout<<"a is big"<<endl;
        else
                cout<<"b is big"<<endl;
        return a;
}
void  max_of_num(float a, float b, float c)
{
        if(a>b)
                cout<<"a is big"<<endl;
        if(b<c)
                cout<<"b is big"<<endl;
}

int max_of_num(int a, int b, int c)
{
        if(a>b)
                cout<<"a is big"<<endl;
        if(b<c)
                cout<<"b is big"<<endl;
        return a;
}




int main()
{
	student one;
	one.student_data_display();
	student two = one;
	one.name="raju";
	two.marks[2] = 50;
	one.student_data_display();
	two.student_data_display();


	//function over loading
	max_of_num(1,2);
	max_of_num(1,2,3);
	max_of_num((float)7.0,(float)2.0);
	max_of_num((float)9.0,(float)7.24,(float)5.2);

}


