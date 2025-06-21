#ifndef ATM_H
#define ATM_H

#include "user.h"

class ATM {
public:
    void atmMenu();
    void checkBalance(int);
    void withdrawAmount(int);
    void viewAccount(int);
};

#endif