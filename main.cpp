#include <iostream>
#include "BankManager.h"

using namespace std;

int main() {
    BankManager bank;
    
    // Load existing accounts from data.txt at startup
    bank.loadFromFile(); 

    int choice;
    int id;

    while (true) {
        cout << "\n==============================";
        cout << "\n    BANK MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Transfer Money";
        cout << "\n5. View Transaction History";
        cout << "\n6. Exit";
        cout << "\nChoice: ";

        // Protection against non-numeric input (prevents infinite loops)
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number (1-6).\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue;
        }

        if (choice == 6) {
            cout << "Saving data and exiting... Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                cout << "Enter Account ID: ";
                cin >> id;
                bank.secureTransaction(id, true); // true = deposit
                break;
            case 3:
                cout << "Enter Account ID: ";
                cin >> id;
                bank.secureTransaction(id, false); // false = withdraw
                break;
            case 4:
                bank.performTransfer();
                break;
            case 5:
                cout << "Enter Account ID: ";
                cin >> id;
                bank.showHistory(id);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

        // Save data after every successful action to prevent data loss
        bank.saveToFile();
    }

    return 0;
}
