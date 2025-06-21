#include "user.h"

User::User() {
    accNumber = 0;
    balance = 0;
}

void User::createAccount() {
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Balance: ";
    cin >> balance;
}

void User::display() const {
    cout << "\nAccount Number: " << accNumber;
    cout << "\nName: " << name;
    cout << "\nBalance: " << balance << endl;
}

void User::displayShort() const {
    cout << accNumber << "\t" << name << "\t" << balance << endl;
}

void User::deposit(double amt) {
    balance += amt;
}

bool User::withdraw(double amt) {
    if (amt > balance) return false;
    balance -= amt;
    return true;
}
