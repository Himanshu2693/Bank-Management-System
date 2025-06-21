#ifndef BANK_H
#define BANK_H

#include "user.h"

class Bank {
public:
    void bankMenu();
    void addUser();
    void viewAll();
    void depositMoney(int, double);
    void withdrawMoney(int, double);
    void searchUser(int);
    void editUser(int);
    void deleteUser(int);
    void transferMoney(int, int, double);
};

#endif