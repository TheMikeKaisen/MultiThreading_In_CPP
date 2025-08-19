#include <iostream>
#include <thread>
#include <vector>
#include <chrono> // For this_thread::sleep_for (chrono.seconds())
using namespace std;

long long shared_counter = 0; // A global, shared resource

void increment_counter_unsafe() {
    for (int i = 0; i < 1000000; ++i) {
        shared_counter++; // This is a Read-Modify-Write operation
    }
}

int main() {
    cout << "Initial counter value: " << shared_counter << endl;

    // Create two threads that will concurrently increment the shared counter
    thread t1(increment_counter_unsafe);
    thread t2(increment_counter_unsafe);

    // Wait for both threads to complete their execution
    t1.join();
    t2.join();

    // Expected final value: 1000000 (from t1) + 1000000(from t2) = 2000000
    // Actual output: Will vary with each run, often less than 2,000000
    cout << "Final counter value (unsafe): " << shared_counter << endl;

    return 0;
}