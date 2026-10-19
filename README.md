# Composition Lab
Jareth Franco | CSCI 272 | October 19, 2026

This project extends my Inheritance Lab by giving each bank account its own transaction history. CheckingAccount and SavingsAccount still inherit from BankAccount. BankAccount now owns a vector of Transaction objects.

## UML diagrams
- [Part 1: original inheritance model](Inheritance_UML.png)
- [Part 2: final composition model](Composition_UML.png)

The hollow triangles point to BankAccount. The filled diamond is on BankAccount because it owns the transactions. The final diagram includes the added history vector, printHistory(), and the protected logging helper.

## How it works
Each deposit and withdrawal records its type, amount, and UTC timestamp. Rejected attempts are marked declined and do not change the balance. A checking withdrawal records the full debit, including its fee. Savings interest uses deposit(), so it is recorded too. Initial balances are constructor values, not deposits. Copies receive independent copies of the history vector.

The program starts with several transactions on both account types and prints both histories. The final balances are $621.00 for checking and $1134.50 for savings. It then opens the original interactive account menu. Enter 0 to exit. sample_output.txt contains a real run; timestamps will differ on later runs.

## Build and run
Use a C++14 compiler:
```sh
g++ -std=c++14 -Wall -Wextra -pedantic main.cpp BankAccount.cpp CheckingAccount.cpp SavingsAccount.cpp -o bank_accounts
./bank_accounts
```
Or use CMake if installed:
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Tests
The original BankAccount tests cover the inherited behavior. HistoryTests checks transaction output, fees, declined attempts, savings interest, timestamps, and independent histories after copying and assignment. Both test programs passed with g++.
