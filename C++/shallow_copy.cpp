#include <iostream>
#include <cstring>
using namespace std;

class Student {
public:
    char* name;

    // Constructor
    Student(const char* n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        cout << "Constructor: name = " << name << endl;
    }

    // ❌ Shallow Copy Constructor
    Student(const Student& other) {
        name = other.name;  // just copy the pointer — NOT deep
        cout << "Shallow Copy Constructor: name = " << name << endl;
    }

    // Destructor
    ~Student() {
        cout << "Destructor called for name = " << name << endl;
        delete[] name;
    }

    void changeName(const char* newName) {
        strcpy(name, newName);
    }

    void display() {
        cout << "Student name: " << name << endl;
    }
};

int main() {
    Student s1("Pujith");
    Student s2 = s1;  // Shallow copy

    cout << "\nAfter copy:" << endl;
    s1.display();
    s2.display();

    cout << "\nModifying s1 name to Raju..." << endl;
    s1.changeName("Raju");

    s1.display();  // Shows "Raju"
    s2.display();  // Also shows "Raju" — bug! shared memory

    cout << "\nExiting program..." << endl;
    return 0;
}

