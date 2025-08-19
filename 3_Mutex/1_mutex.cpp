#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // for creating mutex
using namespace std;


long long shared_counter = 0; // A global, shared resource
mutex mtx;


void increment_counter_safe() {

    mtx.lock();

    // critical section 
    for (int i = 0; i < 1000000; ++i) {
        shared_counter++; // This is a Read-Modify-Write operation
    }

    mtx.unlock();

}

int main() {
    cout << "Initial counter value: " << shared_counter << endl;

    // Create two threads that will concurrently increment the shared counter
    thread t1(increment_counter_safe);
    thread t2(increment_counter_safe);

    // Wait for both threads to complete their execution
    t1.join();
    t2.join();

    // Expected final value: 2000000
    // Actual output: 2000000; mutex variable will make sure that only one thread can access critical section at a time
    cout << "Final counter value (Safe): " << shared_counter << endl;

    return 0;
}