#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>

#define THREAD_NUM 2

using namespace std;

queue<int> buffer;

mutex bufferMutex;


void producer(){
    while(1){
        bufferMutex.lock();
        if(buffer.size()<10){
            int x = rand() % 100;

            buffer.push(x);
            std::cout << "Added " << x << std::endl;
        }

        bufferMutex.unlock();
    }

}

void consumer(){
    while(1){
        int x=-1;

        bufferMutex.lock();
        if(!buffer.empty()){
            x = buffer.front();
            buffer.pop();
        }


        bufferMutex.unlock();

        std::cout << x << std::endl;
    }
}



int main() {
    srand(time(NULL));
    vector<thread> producers, consumers;

    for(int i=0; i<THREAD_NUM; i++){
        if(i%2==0){
            producers.emplace_back(thread(producer));
        }else{
            consumers.emplace_back(thread(consumer));
        }
    }

    for(thread &T: producers){
        T.join();
    }

    for(thread &T: consumers){
        T.join();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
