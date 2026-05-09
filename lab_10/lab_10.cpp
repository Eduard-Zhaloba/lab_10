#include <iostream>
#include <thread>
#include <mutex>  
#include <chrono>
#include <condition_variable>
#include <queue>

class SafeQueue {
private:
    std::queue<int> q;
    std::mutex mut3;
    std::condition_variable producer;
    std::condition_variable consumer;
public:
    void enqueue(int value) {
        std::unique_lock<std::mutex> lock(mut3);

        producer.wait(lock, [this]() { return q.size()<5; });

        q.push(value);
        std::cout << "Produced: " << value << " (Size: " << q.size() << ")" << std::endl;
        consumer.notify_one();
    }

    int dequeue() {
        std::unique_lock<std::mutex> lock(mut3);
        consumer.wait(lock, [this]() { return !q.empty(); });
        int value = q.front();
        q.pop();
        std::cout << "Consumed: " << value << " (Size: " << q.size() << ")" << std::endl;

        producer.notify_one();
        return value;
    }
};

void producer_task(SafeQueue& sq) {
    for (int i = 1; i <= 15; ++i) {
        sq.enqueue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
}

void consumer_task(SafeQueue& sq) {
    for (int i = 1; i <= 15; ++i) {
        sq.dequeue();
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
    }
};
/// /////////////////////////////////////////////////////////

std::mutex mut1;
std::mutex mut2;
void thread_A() {
	mut1.lock();
    //mut1.lock();
    std::cout << "Thread A locked mutex 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mut2.lock();
    //mut2.lock();
    //mut2.unlock();
    std::cout << "Thread A locked mutex 2" << std::endl;
    mut1.unlock();
    mut2.unlock();
    //mut1.unlock();
}

void thread_B() {
    mut1.lock();
    //mut2.lock();
    std::cout << "Thread B locked mutex 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mut2.lock();
    //mut1.lock();
    std::cout << "Thread B locked mutex 2" << std::endl;
    mut1.unlock();
    mut2.unlock();
    //mut2.lock();
    //mut2.unlock();
    //mut1.unlock();
}

int main()
{
    int a1 = 5, a2 = 7, a3 = 10, counter = 0;
    
    std::mutex mut;
    std::thread t1([&counter, &mut](int thread_id = 1) {
        for (int i = 0; i < 100; ++i) {
            mut.lock();
            counter += thread_id;
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
            mut.unlock();
           
        }
        });
  
    std::thread t2([&counter, &mut](int thread_id = 2) {
        for (int i = 0; i < 100; ++i) {
            mut.lock();
            counter += thread_id;
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
            mut.unlock();
          
        }
        });
    
    std::thread t3([&counter, &mut](int thread_id = 3) {
        for (int i = 0; i < 100; ++i) {
            mut.lock();
            counter += thread_id;    
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
            mut.unlock();
       
        }
        });
        t1.join();
        t2.join();
        t3.join();
		std::cout << "Final counter value: " << counter << std::endl;
        std::thread t4(thread_A);
        std::thread t5(thread_B);
        t4.join();
        t5.join();
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        SafeQueue sq;
        std::thread t6(producer_task, std::ref(sq));
        std::thread t7(consumer_task, std::ref(sq));

        t6.join();
        t7.join();
		return 0;
    }