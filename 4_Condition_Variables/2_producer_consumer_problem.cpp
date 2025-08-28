#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadsafeQueue {
private:
    mutex mut;
    queue<T> data_queue;
    condition_variable data_cond;

public:
    void push(T new_value) {
        // lock_guard is sufficient for push because we don't block
        lock_guard<mutex> lk(mut);
        data_queue.push(move(new_value));
        data_cond.notify_one(); // Notify one waiting thread that data is available
    }

    void wait_and_pop(T& value) {
        // unique_lock is required for wait()
        unique_lock<mutex> lk(mut);

        // The predicate lambda handles spurious wakeups internally
        data_cond.wait(lk, [this]{ return!data_queue.empty(); });

        value = move(data_queue.front());
        data_queue.pop();
    }
};

void producer(ThreadsafeQueue<int>& tsq, int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Producer: Pushing " << i << "\n";
        tsq.push(i);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(ThreadsafeQueue<int>& tsq, int count) {
    for (int i = 0; i < count; ++i) {
        int value;
        tsq.wait_and_pop(value);
        cout << "Consumer: Popped " << value << "\n";
    }
}

int main() {
    ThreadsafeQueue<int> tsq;
    thread prod_thread(producer, ref(tsq), 10);
    thread cons_thread(consumer, ref(tsq), 10);

    prod_thread.join();
    cons_thread.join();

    return 0;
}