#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // Required for mutex and lock_guardlong 
using namespace std;

long shared_counter_safe = 0; // The shared resource
mutex counter_mutex;         // The mutex protecting shared_counter_safe

void increment_counter_safe_lock_guard() {
    for (int i = 0; i < 1000000; ++i) {
        // lock_guard acquires the lock on counter_mutex in its constructor.
        // The mutex is locked here.
        lock_guard<mutex> lock(counter_mutex); 
        
        shared_counter_safe++; // This is the critical section
        
        // The mutex is automatically unlocked when 'lock' goes OUT OF SCOPE
        // (at the end of this iteration's loop body).
    }
}

int main() {
    cout << "Initial counter value: " << shared_counter_safe << endl;

    thread t1(increment_counter_safe_lock_guard);
    thread t2(increment_counter_safe_lock_guard);

    t1.join();
    t2.join();

    // The output will now consistently be 2,000,000 due to proper synchronization.
    cout << "Final counter value (safe with lock_guard): " << shared_counter_safe << endl;
    return 0;
}