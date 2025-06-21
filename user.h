#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
public:
    int accNumber;
    string name;
    double balance;

    User();
    void createAccount();
    void display() const;
    void displayShort() const;
    void deposit(double);
    bool withdraw(double);
};

#endif