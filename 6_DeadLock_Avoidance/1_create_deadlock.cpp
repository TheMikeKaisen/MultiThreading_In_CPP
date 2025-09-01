#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>// Define two shared resources, each protected by a mutex

using namespace std;
mutex mtx1;
mutex mtx2;

// function to do the work(here, print a simple message!)
void do_some_work(const char* msg) {
    cout << msg << endl;
}

// t1 is going to call this function
void thread_task_1() {
    do_some_work("Thread 1: Acquiring mtx1...");
    mtx1.lock(); // Holds mtx1

    this_thread::sleep_for(chrono::seconds(2)); // by this time, t2 would have already locked mtx2

    do_some_work("Thread 1: Acquired mtx1. Now trying to acquire mtx2...");
    // This thread will block here if mtx2 is held by another thread

    mtx2.lock(); // Waits for mtx2

    do_some_work("Thread 1: Acquired both locks and performing work.");
    
    // Critical section work...

    // Release locks in the reverse order of acquisition
    mtx2.unlock();
    mtx1.unlock();
    do_some_work("Thread 1: Released both locks.");
}

// t2 thread is going to call this function
void thread_task_2() {
    do_some_work("Thread 2: Acquiring mtx2...");
    mtx2.lock(); // Holds mtx2
    this_thread::sleep_for(chrono::seconds(2)); // by this time, t1 would already have locked mtx1


    do_some_work("Thread 2: Acquired mtx2. Now trying to acquire mtx1...");
    // This thread will block here if mtx1 is held by another thread
    mtx1.lock(); // Waits for mtx1

    do_some_work("Thread 2: Acquired both locks and performing work.");

    // Critical section work...

    // Release locks
    mtx1.unlock();
    mtx2.unlock();
    do_some_work("Thread 2: Released both locks.");
}

int main() {
    cout << "Starting threads...\n";
    thread t1(thread_task_1);
    thread t2(thread_task_2);

    t1.join();
    t2.join();
    
    cout << "Program finished without deadlock.\n";
    return 0;
}