#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    int id;
    float gpa;
    char grade;
    string name;
    int marks[3];               // fixed-size array
    vector<string> subjects;    // STL container
	
    static int obj_count;

    // Default constructor
    Student() {
        id = 1;
        gpa = 9.5;
        grade = 'A';
        name = "Pujith";

        marks[0] = 90; marks[1] = 95; marks[2] = 99;
        subjects = {"Math", "Science", "English"};
	
	obj_count++;

    }

    // Default copy constructor (shallow copy, but safe for these types)
    // No need to write it explicitly — compiler-generated is enough

    void display(const string& label) {
        cout << "\n[" << label << "]\n";
        cout << "ID: " << id << ", GPA: " << gpa << ", Grade: " << grade << "\n";
        cout << "Name: " << name << "\n";

        cout << "Marks: ";
        for (int i = 0; i < 3; ++i)
            cout << marks[i] << " ";
        cout << "\nSubjects: ";
        for (auto& sub : subjects)
            cout << sub << " ";
        cout << "\n";
	cout << "obj count-"<<obj_count<<endl;
    }
};

int main() {
    Student a;
    Student b = a;  // default shallow copy
a.display("Original (a) before-");
    b.display("Copied (b) before"); 

    // Modify original to see if b is affected
    a.id = 2;
    a.gpa = 8.0;
    a.grade = 'B';
    a.name = "Updated Name";
    a.marks[0] = 70;
    a.subjects[0] = "History";

    a.display("Original (a)");
    b.display("Copied (b)");  // Check if b changed (it won't)

    return 0;
}

