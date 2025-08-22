#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>// Essential triad for thread coordination
using namespace std;

mutex m;
condition_variable cv;
bool data_ready = false;
string shared_data;

void worker_thread() {
    cout << "Worker: Waiting for data...\n";

    // A unique_lock is required for wait()
    unique_lock<mutex> lk(m);

    // Block until the condition 'data_ready' is true
    // This atomically releases the lock and suspends the thread
    cv.wait(lk, [] { return data_ready; });

    cout << "Worker: Data received: " << shared_data << "\n";
    cout << "Worker: Processing...\n";
    shared_data += " (processed)";

    // Manually unlock before notifying for efficiency
    lk.unlock();

    // Signal back that work is done
    // cv.notify_one(); // In a real scenario, this would notify a waiting master thread
}

void master_thread() {
    cout << "Master: Preparing data...\n";
    {
        // Use a lock_guard to protect shared_data
        lock_guard<mutex> lk(m);
        shared_data = "Hello, World!";
        data_ready = true;
    } // lock_guard releases the lock automatically here

    cout << "Master: Signaling worker...\n";
    cv.notify_one(); // Wakes up one waiting thread
}

int main() {
    thread worker(worker_thread);
    thread master(master_thread);

    worker.join();
    master.join();

    return 0;
}