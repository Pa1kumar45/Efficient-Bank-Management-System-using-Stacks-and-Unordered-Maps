# Efficient-Bank-Management-System-using-Stacks-and-Unordered-Maps
# Objective
This project aims to implement a banking system where account holders can securely access their accounts, perform transactions, and track transaction history. The focus is on using efficient data structures(Stacks, Unordered Maps) for managing multiple accounts and storing transaction history.
# Challenges
Account Management : Banks need to manage and access multiple accounts securely and efficiently. 
Secure Access : The system must ensure secure access to account details, preventing unauthorized access and protecting sensitive information.
# Background and Motivation
# Background
Modern banking systems handle millions of user accounts and transactions.To manage this efficiently, we need to store and access account details quickly and securely. 
It is essential to maintain a record of all transactions performed by users for accountability and transparency.
# Motivation
The system needs to prioritize security, ensuring only authorized users can access account details using a token and PIN system. Efficiency is also crucial, with the system needing to perform lookups quickly even with a large number of accounts.
# General Solution
Approach
The system utilizes maps to manage accounts, associating a unique token with each account. This allows for efficient access and retrieval of account information.
Account Class
Accounts are defined in a class with private members for name, account number, and balance. Sensitive information can only be accessed or modified through specific public methods, enhancing security.
System Features
Account Creation
Users create a new account by providing details such as a token, name, account number, initial balance, and a PIN. This process ensures secure and unique account identification.
Transactions
Users can deposit or withdraw money, and each transaction will be recorded in a linked list. This provides a detailed and chronological record of all account activity.
Transaction History
Users can view their past transactions in the order they were made. This feature allows for easy tracking and verification of account activity.
# Data Structures Used
Unordered Map for Account Management
The system uses a unordered_map < int , class > to store account information.
Reason :
This data structure provides an average time complexity of O(1) for lookups, making it efficient to access any account by token. This allows the system to scale to a large number of users while maintaining quick access times. 
Stacks for Transaction History
Each account has a linked list to store the history of transactions (deposits and withdrawals).
Reason :
Stacks are ideal for dynamically adding new transactions in the beginning following LIFO rule. Transaction history can grow as needed, and the order of transactions is preserved.
# Implementation
Transaction and TransactionStack Classes Transaction: 
1)Transaction: Represents a bank transaction, including the type (Deposit, Withdrawal, Transfer, or Received), amount, recipient name, and account number (for transfers).
2)TransactionStack: Manages a stack of transactions, with methods to add transactions (push), display them, and save them to a file.
Account Class:
Attributes: Includes account holder details, balance, PIN, and a transaction history (managed using TransactionStack).
Key Methods:
1)deposit and withdraw: For updating balance and logging the transactions.
2)addTransaction: Adds a transaction to the stack.
3)saveAccountToFile: Saves account details and transaction history to a file.
4)displayAccount: Displays account details along with transaction history.

BankSystem Class: 
Manages Multiple Accounts:
Accounts are stored in an unordered_map, using a unique token as the key.
Key Functions:
createAccount: Creates a new account, generating unique tokens and account numbers based on the current time.
accessAccount: Authenticates a user based on token and PIN.
transfer: Handles fund transfers between accounts after validating both sender and receiver details.
Main Function
User Menu: Provides options to create an account, view details, deposit, withdraw, view transactions, and transfer money.
Unique IDs: Tokens and account numbers are dynamically generated using the current time, ensuring uniqueness.
File Storage: Account details and transactions are saved in a text file for persistence.

# OUTPUT :

New Account creation(1):

![image](https://github.com/user-attachments/assets/cea3f9b9-33c1-45e4-bba0-9ad68e574ddc)

Transaction history (5):

![image](https://github.com/user-attachments/assets/93cd0d7d-bf7b-4acb-8ae1-9a00fd7b05cf)

File storage: 

![image](https://github.com/user-attachments/assets/3c94a986-a44e-484c-9237-0f8899c0d961)

# Expected Outputs

Intuitive User Interface
The system should provide an easy-to-navigate interface. This ensures a user-friendly experience for all users.

Efficient System Performance
The system should smoothly manage multiple users and transactions, minimizing lag during account access and transactions. This ensures quick task completion with minimal waiting time.











