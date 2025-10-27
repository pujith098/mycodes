#include <iostream>
using namespace std;

class Student {
private:
    static int obj_count;  // private static variable

public:
    string name;

    Student(const string& n) {
        name = n;
        obj_count++;  // increment count on each object creation
        cout << "Constructor: " << name << " created.\n";
    }

    static int get_count() {
        return obj_count;  // public static method to access private static variable
    }

    void display() const {
        cout << "Student name: " << name << endl;
    }
};

// 🧠 Define the static member outside the class
int Student::obj_count = 0;

int main() {
    cout << "Creating students...\n";

    Student s1("Pujith");
    Student s2("Ravi");

    s1.display();
    s2.display();

    cout << "\nTotal students created: " << Student::get_count() << endl;

    Student s3("Kiran");
    s3.display();

    cout << "\nTotal students created: " << Student::get_count() << endl;

    return 0;
}

