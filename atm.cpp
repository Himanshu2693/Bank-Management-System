#include "atm.h"
#include <fstream>

void ATM::atmMenu() {
    int accNo, choice;
    User u;
    bool found = false;

    cout << "Enter Account Number: ";
    cin >> accNo;

    ifstream file("users.dat", ios::binary);
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Account not found. Returning to main menu.\n";
        return;
    }

    do {
        cout << "\nATM Menu:\n1. Check Balance\n2. Withdraw\n3. View Account\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: checkBalance(accNo); break;
            case 2: withdrawAmount(accNo); break;
            case 3: viewAccount(accNo); break;
            case 4: cout << "Exiting ATM menu...\n"; break;
            default: cout << "Invalid choice! Try again.\n"; break;
        }
    } while (choice != 4);
}


void ATM::checkBalance(int accNo) {
    User u;
    ifstream file("users.dat", ios::binary);
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            cout << "Balance: " << u.balance << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

void ATM::withdrawAmount(int accNo) {
    fstream file("users.dat", ios::binary | ios::in | ios::out);
    User u;
    streampos pos;
    double amt;

    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            pos = file.tellg();
            pos -= static_cast<streamoff>(sizeof(User));
            cout << "Enter amount to withdraw: ";
            cin >> amt;
            if (!u.withdraw(amt)) {
                cout << "Insufficient funds!" << endl;
                return;
            }
            file.seekp(pos);
            file.write((char*)&u, sizeof(User));
            cout << "Withdrawal successful." << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

void ATM::viewAccount(int accNo) {
    User u;
    ifstream file("users.dat", ios::binary);
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            u.display();
            return;
        }
    }
    cout << "Account not found!" << endl;
}
