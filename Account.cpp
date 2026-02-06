#include "Account.h"
#include <iostream>
#include <ctime>

Account::Account(int accNum, std::string name, std::string pass, double initialBal)
    : accountNumber(accNum), holderName(name), password(pass), balance(initialBal) {}

bool Account::authenticate(std::string inputPass) const {
    return inputPass == password;
}

void Account::addHistory(std::string type, double amt) {
    time_t now = time(0);
    std::string dt = ctime(&now);
    if (!dt.empty()) dt.pop_back(); 
    history.push_back({type, amt, dt});
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        addHistory("Deposit", amount);
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        addHistory("Withdrawal", amount);
        return true;
    }
    return false;
}

void Account::displayHistory() const {
    std::cout << "\n--- History for " << holderName << " ---\n";
    for (const auto& t : history) {
        std::cout << "[" << t.timestamp << "] " << t.type << ": $" << t.amount << "\n";
    }
}
