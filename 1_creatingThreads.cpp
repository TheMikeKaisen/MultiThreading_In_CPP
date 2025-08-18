#include<iostream>
#include<chrono>
#include<thread>
using namespace std::chrono;
using namespace std;

void func(){
    int i = 0;
    while(i<1900000000){
        i++;
    }
}


//  WITHOUT THREADS, IT TAKES 13 SECONDS TO EXECUTE THE MAIN FUNCTION BELOW

// int main(){


//     auto start = high_resolution_clock::now();
//     func();
//     func();
//     func();
//     auto end = high_resolution_clock::now();
//     auto duration = duration_cast<microseconds>(end - start);

//     // count the time 
//     cout << duration.count()/1000000 << endl;
// }


// WITH MULTITHREADING IT TAKES AROUND 6 SECONDS FOR THE MAIN FUNCTOIN BELOW

int main(){
    auto start = high_resolution_clock::now();

    // using functional Threads to call the function
    thread t1(func);
    thread t2(func);
    thread t3(func);


    t1.join();
    t2.join();
    t3.join();

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // count the time 
    cout << duration.count()<< endl;
}