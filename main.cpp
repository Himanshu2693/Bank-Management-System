#include<bits/stdc++.h>
#include "bank.h"
#include "atm.h"
#include "user.h"
#include<iostream>
using namespace std;

int main() {
    int choice;
    Bank bank;
    ATM atm;

    do {
        cout << "\nMain Menu:\n1. ATM\n2. Bank\n3. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: atm.atmMenu(); break;
        case 2: bank.bankMenu(); break;
        case 3: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!"; break;
        }
    } while (choice != 3);

    return 0;
}
