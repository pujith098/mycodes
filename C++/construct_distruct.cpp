#include <iostream>
using namespace std;

class Base {
public:
    Base()  { cout << "Base constructor\n"; }
    ~Base() { cout << "Base destructor\n"; }   // ❌ Not virtual
};

class Derived : public Base {
public:
    Derived()  { cout << "Derived constructor\n"; }
    ~Derived() { cout << "Derived destructor\n"; }
};

int main() {
    Base* obj = new Derived();  // Base pointer -> Derived object
    delete obj;                 // ❌ Only Base destructor called
    return 0;
}

