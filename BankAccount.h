// Author: Jareth Franco
// Date: October 19, 2026
// Purpose: Define the shared account interface, operators, and virtual behavior.

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
private:
    std::string accountNumber;
    std::string* accountHolderName; // Owned allocation; never shared by copies.
    double balance;
    std::vector<Transaction> transactionHistory;

protected:
    void logTransaction(const std::string& type, double amount);

public:
    BankAccount();
    BankAccount(const std::string& number, const std::string& name,
                double initialBalance);
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);
    virtual ~BankAccount();
    virtual const char* getAccountType() const { return "Bank"; }

    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();

    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;
    bool setAccountHolderName(const std::string& name);
    void printHistory();
    bool deposit(double amount);
    virtual bool withdraw(double amount);
};

#endif
