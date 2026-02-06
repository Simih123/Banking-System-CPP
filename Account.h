#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

struct Transaction {
    std::string type;
    double amount;
    std::string timestamp;
};

class Account {
private:
    int accountNumber;
    std::string holderName;
    std::string password;
    double balance;
    std::vector<Transaction> history;

public:
    Account(int accNum, std::string name, std::string pass, double initialBal);
    
    bool authenticate(std::string inputPass) const;
    void deposit(double amount);
    bool withdraw(double amount);
    void addHistory(std::string type, double amt);
    void displayHistory() const;

    int getAccountNumber() const { return accountNumber; }
    std::string getHolderName() const { return holderName; }
    double getBalance() const { return balance; }
};

#endif
