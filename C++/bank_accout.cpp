/*
C++ program to implement a simple class BankAccount with:

deposit() and withdraw() methods,

private balance,

constructor initialization,

and proper use of const and this pointer.
*/

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountHolder;
    double balance;

public:
    // Constructor with initialization list
    BankAccount(const string& name, double initialBalance)
        : accountHolder(name), balance(initialBalance) {
        cout << "Account created for " << accountHolder 
             << " with balance: " << balance << endl;
    }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;  // 'this' pointer used explicitly
            cout << "Deposited: " << amount 
                 << " | New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            this->balance -= amount;
            cout << "Withdrawn: " << amount 
                 << " | Remaining balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!" << endl;
        }
    }

    // Const method - does not modify object state
    double getBalance() const {
        return balance;
    }

    // Display account info (const correctness)
    void display() const {
        cout << "Account Holder: " << accountHolder 
             << " | Current Balance: " << getBalance() << endl;
    }
};

// main() function to test
int main() {
    BankAccount account("Pujit", 5000.0);  // object creation with constructor

    account.deposit(1500.0);
    account.withdraw(2000.0);
    account.display();

    cout << "Final balance (checked using const method): " 
         << account.getBalance() << endl;

    return 0;
}



