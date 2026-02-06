#include "BankManager.h"
#include <iostream>
#include <fstream> 

using namespace std;

// Private helper to find an account by ID
Account* BankManager::findAccount(int id) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == id) return &acc;
    }
    return nullptr;
}

void BankManager::createAccount() {
    int id;
    string name, pass;
    double bal;

    cout << "Enter Account ID: "; cin >> id;
    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
    cout << "Set Password: "; cin >> pass;
    cout << "Initial Deposit: "; cin >> bal;

    accounts.emplace_back(id, name, pass, bal);
    cout << "Account created successfully!\n";
}

void BankManager::secureTransaction(int id, bool isDeposit) {
    Account* acc = findAccount(id);
    if (!acc) {
        cout << "Account not found.\n";
        return;
    }

    string pass;
    cout << "Enter password: "; cin >> pass;

    if (acc->authenticate(pass)) {
        double amt;
        cout << "Enter amount: "; cin >> amt;
        if (isDeposit) {
            acc->deposit(amt);
            cout << "Deposit successful.\n";
        } else {
            if (acc->withdraw(amt)) cout << "Withdrawal successful.\n";
            else cout << "Insufficient funds.\n";
        }
    } else {
        cout << "Invalid password.\n";
    }
}

void BankManager::performTransfer() {
    int sId, rId;
    string pass;
    double amt;

    cout << "Sender ID: "; cin >> sId;
    Account* sender = findAccount(sId);
    if (!sender) { cout << "Sender not found.\n"; return; }

    cout << "Enter Password: "; cin >> pass;
    if (!sender->authenticate(pass)) { cout << "Wrong password.\n"; return; }

    cout << "Receiver ID: "; cin >> rId;
    Account* receiver = findAccount(rId);
    if (!receiver || sId == rId) { cout << "Invalid receiver.\n"; return; }

    cout << "Amount: "; cin >> amt;
    if (sender->withdraw(amt)) {
        receiver->deposit(amt);
        sender->addHistory("Transfer to #" + to_string(rId), amt);
        receiver->addHistory("Transfer from #" + to_string(sId), amt);
        cout << "Transfer complete.\n";
    } else {
        cout << "Insufficient funds.\n";
    }
}

void BankManager::showHistory(int id) {
    Account* acc = findAccount(id);
    if (acc) {
        string pass;
        cout << "Enter password: "; cin >> pass;
        if (acc->authenticate(pass)) acc->displayHistory();
        else cout << "Access denied.\n";
    } else {
        cout << "Account not found.\n";
    }
}
void BankManager::saveToFile() {
    ofstream outFile("data.txt");
    for (const auto& acc : accounts) {
        outFile << acc.getAccountNumber() << "," 
                << acc.getHolderName() << "," 
                << "pass123" << "," 
                << acc.getBalance() << endl;
    }
    outFile.close();
}

void BankManager::loadFromFile() {
    ifstream inFile("data.txt");
    if (!inFile) return; 
    int id; string name, pass; double bal;
    while (inFile >> id) {
        inFile.ignore(); 
        getline(inFile, name, ',');
        getline(inFile, pass, ',');
        inFile >> bal;
        accounts.emplace_back(id, name, pass, bal);
    }
    inFile.close();
}
