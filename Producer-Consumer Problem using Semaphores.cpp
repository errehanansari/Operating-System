#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable read, write;
int readers = 0;

void reader() {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);
        readers++;
        if (readers == 1) {
            write.wait(lock);
        }
        lock.unlock();

        cout << "Reading..." << endl;

        lock.lock();
        readers--;
        if (readers == 0) {
            read.notify_all();
        }
        lock.unlock();
    }
}

void writer() {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);
        write.wait(lock);
        lock.unlock();

        cout << "Writing..." << endl;

        lock.lock();
        write.notify_all();
        read.notify_all();
        lock.unlock();
    }
}

int main() {
    thread readerThreads[3];
    thread writerThread(writer);

    for (int i = 0; i < 3; i++) {
        readerThreads[i] = thread(reader);
    }

    for (int i = 0; i < 3; i++) {
        readerThreads[i].join();
    }

    writerThread.join();

    return 0;
}

