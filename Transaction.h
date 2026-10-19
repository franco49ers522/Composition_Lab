// Author: Jareth Franco
// Date: October 19, 2026
// Purpose: Store one transaction as a value owned by a bank account.
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
struct Transaction {
    std::string type;
    double amount;
    std::string timestamp;
};
#endif
