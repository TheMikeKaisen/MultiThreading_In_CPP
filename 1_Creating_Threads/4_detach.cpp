#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void func(){
    this_thread::sleep_for(chrono::seconds(2));
    for(int i = 0; i<10; i++){
        cout << "value " << i << endl;
    }
}
int main(){
    thread t1(func);

    // though the thread completed its execution and provided us the expected result, 
    // it still gave us terminated without exception error.
    // This happens because when main() thread completes its execution, it calls destructor of every thread present
    // destructor calls std::terminate which is responsible to provide that error
    
    
    // main() thread is the parent thread of whatever threads are created inside main() function
    // to detach child threads from main() thread we use detach()
    
    t1.detach();


    this_thread::sleep_for(chrono::seconds(3));

    return 0;
}