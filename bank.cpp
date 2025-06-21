#include "bank.h"
#include <fstream>
#include <limits>
using namespace std;


void Bank::bankMenu() {
    int choice;
    do {
        cout << "\nBank Menu:\n1. Add User\n2. View All\n3. Deposit\n4. Withdraw\n5. Search\n6. Edit\n7. Delete\n8. Transfer\n9. Exit\nChoice: ";
        cin >> choice;

        int acc1, acc2;
        double amt;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addUser();
            break;
        case 2:
            viewAll();
            break;
        case 3:
            cout << "Account No: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid account number!\n";
                break;
            }
            cout << "Amount: ";
            cin >> amt;
            if (cin.fail() || amt < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount!\n";
                break;
            }
            depositMoney(acc1, amt);
            break;
        case 4:
            cout << "Account No: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid account number!\n";
                break;
            }
            cout << "Amount: ";
            cin >> amt;
            if (cin.fail() || amt < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount!\n";
                break;
            }
            withdrawMoney(acc1, amt);
            break;
        case 5:
            cout << "Account No: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid account number!\n";
                break;
            }
            searchUser(acc1);
            break;
        case 6:
            cout << "Account No: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid account number!\n";
                break;
            }
            editUser(acc1);
            break;
        case 7:
            cout << "Account No: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid account number!\n";
                break;
            }
            deleteUser(acc1);
            break;
        case 8:
            cout << "From Acc: ";
            cin >> acc1;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid sender account number!\n";
                break;
            }
            cout << "To Acc: ";
            cin >> acc2;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid receiver account number!\n";
                break;
            }
            cout << "Amount: ";
            cin >> amt;
            if (cin.fail() || amt < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount!\n";
                break;
            }
            transferMoney(acc1, acc2, amt);
            break;
        case 9:
            cout << "Exiting bank menu...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            break;
        }

    } while (choice != 9);
}


void Bank::addUser() {
    User u;
    u.createAccount();
    ofstream file("users.dat", ios::binary | ios::app);
    file.write((char*)&u, sizeof(User));
}

void Bank::viewAll() {
    User u;
    ifstream file("users.dat", ios::binary);
    while (file.read((char*)&u, sizeof(User))) u.displayShort();

    if (!file) {
    cout << "No user records found.\n";
    return;
}

}

void Bank::depositMoney(int accNo, double amt) {
    fstream file("users.dat", ios::binary | ios::in | ios::out);
    User u; streampos pos;
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            pos = file.tellg();
            pos -= static_cast<streamoff>(sizeof(User));
            u.deposit(amt);
            file.seekp(pos);
            file.write((char*)&u, sizeof(User));
            cout << "Deposited." << endl;
            return;
        }
    }
    cout << "Account not found!" << endl;
}

void Bank::withdrawMoney(int accNo, double amt) {
    fstream file("users.dat", ios::binary | ios::in | ios::out);
    User u; streampos pos;
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            pos = file.tellg();
            pos -= static_cast<streamoff>(sizeof(User));
            if (!u.withdraw(amt)) { cout << "Insufficient balance!"; return; }
            file.seekp(pos);
            file.write((char*)&u, sizeof(User));
            cout << "Withdrawn." << endl;
            return;
        }
    }
    cout << "Account not found!";
}

void Bank::searchUser(int accNo) {
    User u; ifstream file("users.dat", ios::binary);
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) { u.display(); return; }
    }
    cout << "Account not found!";
}

void Bank::editUser(int accNo) {
    fstream file("users.dat", ios::binary | ios::in | ios::out);
    User u; streampos pos;
    while (file.read((char*)&u, sizeof(User))) {
        if (u.accNumber == accNo) {
            pos = file.tellg(); 
            pos -= static_cast<streamoff>(sizeof(User));
            cout << "Editing user...\n";
            u.createAccount();
            file.seekp(pos);
            file.write((char*)&u, sizeof(User));
            cout << "Updated.";
            return;
        }
    }
    cout << "Account not found!";
}

void Bank::deleteUser(int accNo) {
    ifstream in("users.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);
    User u; bool found = false;
    while (in.read((char*)&u, sizeof(User))) {
        if (u.accNumber != accNo) out.write((char*)&u, sizeof(User));
        else found = true;
    }
    in.close(); out.close();
    remove("users.dat");
    rename("temp.dat", "users.dat");
    if (found) cout << "Deleted.";
    else cout << "Not found!";
}

void Bank::transferMoney(int fromAcc, int toAcc, double amt) {
    fstream file("users.dat", ios::binary | ios::in | ios::out);
    User u1, u2; streampos pos1, pos2;
    bool found1 = false, found2 = false;

    while (file.read((char*)&u1, sizeof(User))) {
        if (u1.accNumber == fromAcc) {
            pos1 = file.tellg();
            pos1 -= static_cast<streamoff>(sizeof(User));
            found1 = true;
            break;
        }
    }
    if (!found1) { cout << "Sender not found!"; return; }

    file.clear();
    file.seekg(0);
    while (file.read((char*)&u2, sizeof(User))) {
        if (u2.accNumber == toAcc) {
            pos2 = file.tellg();
            pos2 -= static_cast<streamoff>(sizeof(User));
            found2 = true;
            break;
        }
    }
    if (!found2) { cout << "Receiver not found!"; return; }

    if (u1.balance < amt) { cout << "Insufficient funds!"; return; }
    u1.withdraw(amt); u2.deposit(amt);

    file.seekp(pos1); file.write((char*)&u1, sizeof(User));
    file.seekp(pos2); file.write((char*)&u2, sizeof(User));
    cout << "Transfer complete.";
}