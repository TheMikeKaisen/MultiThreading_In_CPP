#include <iostream>
#include <thread>
#include <mutex>
class Account {
public:
    int balance;
    std::mutex m;

    explicit Account(int initialAmount) : balance(initialAmount) {}
};

void transfer_scoped_lock(Account& from, Account& to, int amount) {
    // The single line of code handles deadlock-free locking and RAII-style unlocking
    std::scoped_lock lock(from.m, to.m);
    
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transfer successful.\n";
    } else {
        std::cout << "Transfer failed: insufficient funds.\n";
    }
}