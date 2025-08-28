#include <iostream>
#include<thread>
#include <string>

using namespace std;

void modifyByValue(int a, string str){
    a += 100;
    str += " how are you all?";

    cout << "Modified Value T1: a= " << a << " str=" << str << endl;
    
}

void modifyByReference(int &a, string &str){
    a += 100;
    str += " how are you all?";

    cout << "Modified Value T2: a= " << a << " str=" << str << endl;
    
}

int main(){
    int a = 10;
    string str = "hello world";

    cout << "Before creating any threads: a= " << a << " str= " << str << endl;
    thread t1(modifyByValue, a, str);

    // The below code will provide an error: because you cannot just call by reference like this.
    // solution : use ref()
    // thread t2(modifyByReference, a, str);

    t1.join();

    cout << "Original Thread: a= " << a << " str = " << str << endl;

    cout << "After Joining the thread" << endl;

    return 0;

}