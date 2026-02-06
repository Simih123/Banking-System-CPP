#ifndef BANKMANAGER_H
#define BANKMANAGER_H

#include "Account.h"
#include <vector>

class BankManager {
private:
    std::vector<Account> accounts;
    Account* findAccount(int id);

public:
    void createAccount();
    void secureTransaction(int id, bool isDeposit);
    void performTransfer();
    void showHistory(int id);
// Saving files 
void saveToFile();
void loadFromFile();
};

#endif
