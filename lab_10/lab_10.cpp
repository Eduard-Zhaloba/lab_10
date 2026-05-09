#include <iostream>
#include <thread>
#include <mutex>   
int main()
{
	int a1 = 5, a2 = 7, a3 = 10, counter = 0;
	std::mutex mut;
    std::thread t1([&counter, &mut](int thread_id=1) {
        for (int i = 0; i < 10; ++i) { 
            mut.lock();
            counter += thread_id;
            std::cout << "Thread " << thread_id << " made value: " << counter << std::endl;
			mut.unlock();
        }
    });
    std::thread t2([&counter, &mut](int thread_id = 2) {
        for (int i = 0; i < 10; ++i) {
            mut.lock();
            counter += thread_id;
            std::cout << "Thread " << thread_id << " made value: " << counter << std::endl;
            mut.unlock();
        }
    });
    std::thread t3([&counter, &mut](int thread_id = 3) {
        for (int i = 0; i < 10; ++i) {
            mut.lock();
            counter += thread_id;
            std::cout << "Thread " << thread_id << " made value: " << counter << std::endl;
            mut.unlock();
        }
		});
    t1.join();
    t2.join();
    t3.join();
}
