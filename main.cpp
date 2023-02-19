#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>

#define THREAD_NUM 2

using namespace std;

queue<int> buffer;

mutex bufferMutex;


void producer() {
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        bufferMutex.lock();

        if (buffer.size() < 10) {
            int x = rand() % 100;

            buffer.push(x);
            std::cout << "Added " << x << std::endl;
        }
        bufferMutex.unlock();
    }
}

void consumer() {

    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int x = -1;

        bufferMutex.lock();
        if (!buffer.empty()) {
            x = buffer.front();
            buffer.pop();
            std::cout << x << std::endl;
        }
        bufferMutex.unlock();
    }
}

int main() {
    srand(time(NULL));
    vector<thread> producers, consumers;

    for (int i = 0; i < THREAD_NUM; i++) {
        if (i % 2 == 0) {
            producers.emplace_back(thread(producer));
        }
        else {
            consumers.push_back(std::move(thread(consumer)));
        }
    }

    for (thread& T : producers) {
        T.join();
    }

    for (thread& T : consumers) {
        T.join();
    }

    return 0;
}
