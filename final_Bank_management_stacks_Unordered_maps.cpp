#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <ctime>
#include <chrono>
using namespace std;

struct Transaction {
    string type;
    double amount;
    string recipientName;
    long int recipientAccount;

    Transaction(const string& t, double a, const string& rName = "", long int rAcc = 0)
        : type(t), amount(a), recipientName(rName), recipientAccount(rAcc) {}
};

class TransactionStack {
private:
    stack<Transaction> transactions;
    int maxSize;  // Maximum number of transactions to store

public:
    TransactionStack(int limit = 100) : maxSize(limit) {}
    void push(const Transaction& trans) {
    // Check if the transaction stack has reached the max size.
    if (transactions.size() < maxSize) {
        transactions.push(trans);
    } else {
        cout << "Transaction stack is full. Cannot add more transactions.\n";
    }
}


    void display() const {
        stack<Transaction> temp = transactions;
        while (!temp.empty()) {
            const Transaction& trans = temp.top();
            cout << trans.type << " of " << trans.amount;
            if (trans.type == "Transfer") {
                cout << " to " << trans.recipientName << " (Account Number: " << trans.recipientAccount << ")";
            } else if (trans.type == "Received") {
                cout << " from " << trans.recipientName << " (Account Number: " << trans.recipientAccount << ")";
            }
            cout << "\n";
            temp.pop();
        }
    }

    void saveToFile(ofstream& file) const {
        stack<Transaction> temp = transactions;
        while (!temp.empty()) {
            const Transaction& trans = temp.top();
            file << trans.type << " of " << trans.amount;
            if (trans.type == "Transfer") {
                file << " to " << trans.recipientName << " (Account Number: " << trans.recipientAccount << ")";
            } else if (trans.type == "Received") {
                file << " from " << trans.recipientName << " (Account Number: " << trans.recipientAccount << ")";
            }
            file << "\n";
            temp.pop();
        }
    }
};

class Account {
private:
    string name;
    long int accountNumber;
    double balance;
    int pin;
    TransactionStack transactionHistory;  // Use stack for transaction history

public:
    Account() : name(""), accountNumber(0), balance(0.0), pin(0), transactionHistory(10) {}

    Account(string n, long int accNum, double bal, int p)
        : name(n), accountNumber(accNum), balance(bal), pin(p), transactionHistory(10) {}

    bool verifyPin(int enteredPin) {
        return enteredPin == pin;
    }

    bool verifyAccountNumber(long int accNum) {
        return accNum == accountNumber;
    }

    void deposit(double amount) {
        balance += amount;
        addTransaction("Deposit", amount);
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            addTransaction("Withdrawal", amount);
            return true;
        }
        return false;
    }

    void addTransaction(const string& type, double amount, string rName = "", long int rAcc = 0) {
        transactionHistory.push(Transaction(type, amount, rName, rAcc));
    }

    void saveAccountToFile(const string& filepath) const {
        ofstream file(filepath, ios::app);
        if (!file) {
            cout << "Error: Unable to open file.\n";
            return;
        }
        file << "Account Holder: " << name << "\n";
        file << "Account Number: " << accountNumber << "\n";
        file << "Balance: " << balance << "\n";
        file << "Transaction History:\n";
        transactionHistory.saveToFile(file);
        file << "--------------------------------------\n";
        file.close();
    }

    void displayAccount() const {
        cout << "Account Holder: " << name << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Balance: " << balance << "\n";
        cout << "Transaction History (Most Recent First):\n";
        transactionHistory.display();
    }

    double getBalance() const { return balance; }
    const string& getName() const { return name; }
    long int getAccountNumber() const { return accountNumber; }
};

class BankSystem {
private:
    unordered_map<int, Account> bankAccounts;

public:
    void createAccount(int token, string name, long int accountNumber, double balance, int pin, const string& filePath) {
        Account account(name, accountNumber, balance, pin);
        bankAccounts[token] = account;
        bankAccounts[token].saveAccountToFile(filePath);
    }

    Account* accessAccount(int token, int pin) {
        if (bankAccounts.find(token) != bankAccounts.end() && bankAccounts[token].verifyPin(pin)) {
            return &bankAccounts[token];
        }
        return nullptr;
    }

    void transfer(int senderToken, int senderPin, int receiverToken, const string& receiverName, long int receiverAccountNumber, double amount, const string& filePath) {
        Account* sender = accessAccount(senderToken, senderPin);
        if (sender == nullptr) {
            cout << "Transfer failed: Incorrect sender token or PIN.\n";
            return;
        }

        if (bankAccounts.find(receiverToken) == bankAccounts.end()) {
            cout << "Transfer failed: Receiver's account not found.\n";
            return;
        }

        Account* receiver = &bankAccounts[receiverToken];
        if (receiver->getName() != receiverName || !receiver->verifyAccountNumber(receiverAccountNumber)) {
            cout << "Transfer failed: Invalid receiver account information.\n";
            return;
        }

        if (sender->withdraw(amount)) {
            receiver->deposit(amount);
            sender->addTransaction("Transfer", amount, receiver->getName(), receiver->getAccountNumber());
            receiver->addTransaction("Received", amount, sender->getName(), sender->getAccountNumber());
            sender->saveAccountToFile(filePath);
            receiver->saveAccountToFile(filePath);

            cout << "Transfer of " << amount << " from " << sender->getName() << " to " << receiver->getName() << " successful!\n";
        } else {
            cout << "Transfer failed: Insufficient funds.\n";
        }
    }
};

int main() {
    BankSystem bank;
    string filePath = "C:\\Users\\Hp\\Desktop\\C Tutorials\\C++\\DSA - 1 LAB\\DSA Project\\a.txt";
    int choice;

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create New Account\n";
        cout << "2. View Account Details\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. View Transaction History\n";
        cout << "6. Transfer Money\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                auto now = chrono::system_clock::now();
                time_t currentTime = chrono::system_clock::to_time_t(now);
                tm* localTime = localtime(&currentTime);
                
        int seconds = localTime->tm_sec;
        int minutes = localTime->tm_min;      int day = localTime->tm_mday;
        int month = localTime->tm_mon + 1;    int year = localTime->tm_year + 1900;

        string y=to_string(year%100);                           string d=to_string(day%10); if(day<10){d='0'+d;}
        string m=to_string(minutes); if(minutes<10){m='0'+m;}   string sec=to_string(seconds); if(seconds<10){sec='0'+sec;}
        string mnth=to_string(month);  if(month<10){mnth='0'+mnth;}
 
        string acc=mnth+d+m+sec;       string tok=sec+d+m;

             int token=stoul(tok) ;long int accountNumber=stoul(acc);
                int pin;
                double balance;
                string name;

                cout << "Your unique token: " << token << endl;
                cout << "Enter account holder's name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Your account number: " << accountNumber << "\n";
                cout << "Enter initial balance: ";
                cin >> balance;
                cout << "Enter a 4-digit PIN: ";
                cin >> pin;

                bank.createAccount(token, name, accountNumber, balance, pin, filePath);
                cout << "Account created successfully!\n";
                break;
            }
            case 2: {
                int token, pin;
                cout << "Enter your token: ";
                cin >> token;
                cout << "Enter your PIN: ";
                cin >> pin;

                Account* account = bank.accessAccount(token, pin);
                if (account) {
                    account->displayAccount();
                } else {
                    cout << "Invalid token or PIN.\n";
                }
                break;
            }
            case 3: {
                int token, pin;
                double amount;
                cout << "Enter your token: ";
                cin >> token;
                cout << "Enter your PIN: ";
                cin >> pin;

                Account* account = bank.accessAccount(token, pin);
                if (account) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                    account->saveAccountToFile(filePath);
                    cout << "Deposit successful.\n";
                } else {
                    cout << "Invalid token or PIN.\n";
                }
                break;
            }
            case 4: {
                int token, pin;
                double amount;
                cout << "Enter your token: ";
                cin >> token;
                cout << "Enter your PIN: ";
                cin >> pin;

                Account* account = bank.accessAccount(token, pin);
                if (account) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    if (account->withdraw(amount)) {
                        account->saveAccountToFile(filePath);
                        cout << "Withdrawal successful.\n";
                    } else {
                        cout << "Insufficient funds.\n";
                    }
                } else {
                    cout << "Invalid token or PIN.\n";
                }
                break;
            }
            case 5: {
                int token, pin;
                cout << "Enter your token: ";
                cin >> token;
                cout << "Enter your PIN: ";
                cin >> pin;

                Account* account = bank.accessAccount(token, pin);
                if (account) {
                    account->displayAccount();
                } else {
                    cout << "Invalid token or PIN.\n";
                }
                break;
            }
            case 6: {
                int senderToken, receiverToken, senderPin;
                string receiverName;
                long int receiverAccountNumber;
                double amount;
                cout << "Enter sender's token: ";
                cin >> senderToken;
                cout << "Enter sender's PIN: ";
                cin >> senderPin;
                cout << "Enter receiver's token: ";
                cin >> receiverToken;
                cout << "Enter receiver's name: ";
                cin.ignore();
                getline(cin, receiverName);
                cout << "Enter receiver's account number: ";
                cin >> receiverAccountNumber;
                cout << "Enter amount to transfer: ";
                cin >> amount;

                bank.transfer(senderToken, senderPin, receiverToken, receiverName, receiverAccountNumber, amount, filePath);
                break;
            }
            case 0:
                cout << "Thank you for using the Bank Management System. Visit Again!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}