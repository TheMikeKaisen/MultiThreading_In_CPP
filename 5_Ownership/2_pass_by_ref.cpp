#include <iostream>
#include<thread>
#include <string>

using namespace std;


void modifyByReference(int &a, string &str){
    a += 100;
    str += " how are you all?";

    cout << "Modified Value T2: a= " << a << " str=" << str << endl;
    
}

int main(){
    int a = 10;
    string str = "hello world";

    cout << "Before creating any threads: a= " << a << " str= " << str << endl;

    // The below code will provide an error: because you cannot just call by reference like this.
    thread t1(modifyByReference, ref(a), ref(str));

    t1.join();


    // you will see that the original values are also reflected the changes.
    cout << "Original Thread: a= " << a << " str = " << str << endl;

    cout << "After Joining the thread" << endl;

    return 0;

}