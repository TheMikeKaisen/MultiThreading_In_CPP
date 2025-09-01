#include <iostream>
#include <thread>
#include <mutex>

class Account {
public:
    int balance;
    std::mutex m;

    explicit Account(int initialAmount) : balance(initialAmount) {}
};

void transfer_safe_lock(Account& from, Account& to, int amount) {
    if (&from == &to) return;
    
    // std::lock locks both mutexes without deadlocking
    std::lock(from.m, to.m);

    // lock_guard with adopt_lock takes ownership of the already-locked mutexes
    std::lock_guard<std::mutex> lock_from(from.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_to(to.m, std::adopt_lock);

    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transfer successful.\n";
    } else {
        std::cout << "Transfer failed: insufficient funds.\n";
    }
}