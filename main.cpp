#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <syncstream>
#include <vector>

using namespace std;

void perform_task(const string& name, int time) {
    this_thread::sleep_for(chrono::seconds(time));
    osyncstream(cout) << name << " completed (" << time << "s) in thread " << this_thread::get_id() << endl;
}

void work() {
    cout << "Start work()" << endl;
    auto start_time = chrono::steady_clock::now();

    auto A_future = async(launch::async, []() {
        perform_task("A1", 1); // f
        perform_task("A2", 7); //s
        perform_task("A3", 1); //f
    });

    perform_task("B1", 1); //f
    perform_task("B2", 7); //s
    perform_task("B3", 1); //f

    A_future.get();

    perform_task("C", 1);  //f

    auto end_time = chrono::steady_clock::now();
    auto elapsed_seconds = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    
    cout << "Work is done!." << endl;
    cout << "Total  time: " << elapsed_seconds.count() << " seconds" << endl;
}

int main() {
    work();
    
    cout << "\nPress Enter to exit" << endl;
    cin.get();
    
    return 0;
}