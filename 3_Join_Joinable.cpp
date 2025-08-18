#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void printFunc(int count){
    while(count){
        cout << "count value: " << count << endl;
        count--;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){
    thread p1(printFunc, 5);
    cout << "inside main function" << endl;

    // without join(), the main thread will complete its execution
    // without waiting for p1 thread to complete.
    p1.join();

    // below code will provide will FAIL. p1 thread is already completed above
    // so the below code will provide an invalid argument error.
    // p1.join();

    // to safely check if a thread can be joined, you can use: joinable()
    if(p1.joinable()){
        p1.join();
    }
    else{
        cout << "p1 thread has already been joined!" << endl;
    }
    return 0;
}
