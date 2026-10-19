// Author: Jareth Franco
// Date: October 19, 2026
// Purpose: Manage owned memory, account operators, and static utility functions.

#include "BankAccount.h"
#include "Input.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <ctime>
#include <sstream>

BankAccount::BankAccount()
    : accountNumber("Unassigned"), accountHolderName(new std::string("Unknown")),
      balance(0.0) {}

BankAccount::BankAccount(const std::string& number, const std::string& name,
                         double initialBalance)
    : accountNumber(number), accountHolderName(nullptr), balance(initialBalance) {
    if (number.find_first_not_of(" \t\r\n") == std::string::npos ||
        name.find_first_not_of(" \t\r\n") == std::string::npos ||
        !std::isfinite(initialBalance) || initialBalance < 0.0) {
        throw std::invalid_argument("Invalid account details.");
    }
    // Validate before allocating: a throwing constructor must not leak memory.
    accountHolderName = new std::string(name);
}

BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber),
      accountHolderName(new std::string(*other.accountHolderName)),
      balance(other.balance), transactionHistory(other.transactionHistory) {}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        // Make the entire copy first. If allocation fails, this object is unchanged.
        BankAccount copy(other);
        accountNumber.swap(copy.accountNumber);
        std::swap(accountHolderName, copy.accountHolderName);
        std::swap(balance, copy.balance);
        transactionHistory.swap(copy.transactionHistory);
        // copy's destructor releases this object's previous allocation.
    }
    return *this;
}

BankAccount::~BankAccount() {
    delete accountHolderName;
}

std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return *accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

bool BankAccount::setAccountHolderName(const std::string& name) {
    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        return false;
    }
    *accountHolderName = name;
    return true;
}

bool BankAccount::deposit(double amount) {
    // Reject invalid amounts and balance overflow before changing the account.
    if (!std::isfinite(amount) || amount <= 0.0 ||
        !std::isfinite(balance + amount)) {
        logTransaction("Deposit declined", amount);
        return false;
    }
    logTransaction("Deposit", amount);
    balance += amount;
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (!std::isfinite(amount) || amount <= 0.0 || amount > balance) {
        logTransaction("Withdrawal declined", amount);
        return false;
    }
    logTransaction("Withdrawal", amount);
    balance -= amount;
    return true;
}

BankAccount& BankAccount::operator+=(double amount) {
    if (!deposit(amount)) {
        throw std::invalid_argument("Deposit must be positive and finite, without balance overflow.");
    }
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    if (!withdraw(amount)) {
        throw std::invalid_argument("Withdrawal must be positive and finite, with sufficient funds.");
    }
    return *this;
}

bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

void BankAccount::printAccount(const BankAccount& account) {
    const auto oldFlags = std::cout.flags();
    const auto oldPrecision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2)
              << account.getAccountType() << " account: " << account.accountNumber
              << " | Holder: " << *account.accountHolderName
              << " | Balance: $" << account.balance << '\n';
    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}

BankAccount BankAccount::createAccountFromInput() {
    std::string number;
    std::string name;
    double initialBalance;
    if (!Input::readText("Account number: ", number) ||
        !Input::readText("Account holder name: ", name) ||
        !Input::readAmount("Initial balance: $", initialBalance, true)) {
        throw std::runtime_error("Account creation cancelled: input ended.");
    }
    return BankAccount(number, name, initialBalance);
}

// Store records by value: each account owns its own transaction history.
void BankAccount::logTransaction(const std::string& type, double amount) {
    const std::time_t now = std::time(nullptr);
    const std::tm* utc = std::gmtime(&now);
    std::ostringstream timestamp;
    if (utc) timestamp << std::put_time(utc, "%Y-%m-%d %H:%M:%S UTC");
    else timestamp << "Time unavailable";
    transactionHistory.push_back(Transaction{type, amount, timestamp.str()});
}

void BankAccount::printHistory() {
    const auto oldFlags = std::cout.flags();
    const auto oldPrecision = std::cout.precision();
    std::cout << "\n" << getAccountType() << " transaction history ("
              << accountNumber << ")\n";
    if (transactionHistory.empty()) std::cout << "No transactions yet.\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const Transaction& transaction : transactionHistory) {
        std::cout << transaction.timestamp << " | " << transaction.type
                  << " | $" << transaction.amount << '\n';
    }
    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}
