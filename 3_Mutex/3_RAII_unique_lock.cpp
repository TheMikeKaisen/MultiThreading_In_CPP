#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // Required for chrono::milliseconds

using namespace std;

mutex my_mutex;
int shared_data = 0;

void process_data_flexible() {
    // Create unique_lock WITHOUT IMMEDIATELY LOCKING the mutex (deferred locking).
    // The mutex is NOT locked at this point.
    unique_lock<mutex> lock(my_mutex, defer_lock);

    // Simulate some non-critical work that doesn't require the mutex
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Thread " << this_thread::get_id() << " doing non-critical work.\n";

    // Now, explicitly acquire the lock for the critical section.
    // This call will block if the mutex is currently held by another thread.
    lock.lock();
    
    shared_data++; // This is the critical section
    cout << "Thread " << this_thread::get_id()
              << " incremented shared_data to " << shared_data << ".\n";
    
    // The mutex will be automatically released when 'lock' goes out of scope.
}

int main() {
    cout << "Initial shared_data: " << shared_data << endl;
    
    thread t1(process_data_flexible);
    thread t2(process_data_flexible);

    t1.join();
    t2.join();

    cout << "Final shared_data: " << shared_data << endl;
    return 0;
}