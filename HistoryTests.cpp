// Author: Jareth Franco
// Date: October 19, 2026
// Purpose: Check history output, fees, rejected attempts, and independent copies.
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>
std::string history(BankAccount& account) {
    std::ostringstream output;
    auto* previous = std::cout.rdbuf(output.rdbuf());
    account.printHistory();
    std::cout.rdbuf(previous);
    return output.str();
}
int main() {
    CheckingAccount checking("C1", "Test", 100, 2);
    assert(history(checking).find("No transactions yet.") != std::string::npos);
    assert(checking.deposit(50));
    BankAccount& base = checking;
    assert(base.withdraw(20));
    assert(checking.getBalance() == 128);
    assert(!checking.withdraw(200));
    assert(!checking.withdraw(-1));
    assert(!checking.deposit(0));
    const auto original = history(checking);
    assert(original.find("Withdrawal | $22.00") != std::string::npos);
    assert(original.find("Withdrawal declined | $202.00") != std::string::npos);
    assert(original.find("Deposit declined | $0.00") != std::string::npos);
    assert(original.find("UTC") != std::string::npos);
    CheckingAccount copy(checking);
    assert(history(copy) == original);
    copy.deposit(7);
    assert(history(checking) == original);
    CheckingAccount assigned("C2", "Other", 1, 1);
    assigned = checking;
    assert(history(assigned) == original);
    assigned.withdraw(5);
    assert(history(checking) == original);
    SavingsAccount savings("S1", "Test", 1000, 0.03);
    savings.deposit(300);
    savings.withdraw(150);
    savings.calculateInterest();
    savings.withdraw(50);
    assert(std::abs(savings.getBalance() - 1134.50) < 0.001);
    assert(history(savings).find("Deposit | $34.50") != std::string::npos);
    std::cout << "All transaction history tests passed.\n";
}
