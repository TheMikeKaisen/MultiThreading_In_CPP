#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;

void task(int id) {
    if (m.try_lock()) { // Attempt to lock
        cout << "Thread " << id << " got the lock\n";
        this_thread::sleep_for(chrono::seconds(1)); // simulate work
        m.unlock();
    } else {
        cout << "Thread " << id << " could not get the lock\n";
    }
}

int main() {
    thread t1(task, 1);
    thread t2(task, 2);

    t1.join();
    t2.join();
    return 0;
}
