#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
int reader_count = 0;
bool is_writing = false;

void reader(int id) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return !is_writing; });
    reader_count++;
    lock.unlock();

    cout << "Reader " << id << " is reading.\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Reader " << id << " has finished reading.\n";

    lock.lock();
    reader_count--;
    if (reader_count == 0) {
        cv.notify_all();
    }
    lock.unlock();
}

void writer(int id) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return reader_count == 0 && !is_writing; });
    is_writing = true;

    cout << "Writer " << id << " is writing.\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Writer " << id << " has finished writing.\n";

    is_writing = false;
    cv.notify_all();
}

int main() {
    int num_readers = 3, num_writers = 2;
    vector<thread> threads;

    for (int i = 0; i < num_readers; i++)
        threads.push_back(thread(reader, i + 1));

    for (int i = 0; i < num_writers; i++)
        threads.push_back(thread(writer, i + 1));

    for (auto &t : threads)
        t.join();

    return 0;
}