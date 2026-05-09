#include <iostream>
#include <thread>

int main()
{
	int a1 = 5, a2 = 7, a3 = 10, counter = 0;
    std::thread t1([&counter](int thread_id=1) {
        for (int i = 0; i < 10; ++i) { 
            counter += thread_id;
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
        }
    });
    std::thread t2([&counter](int thread_id = 2) {
        for (int i = 0; i < 10; ++i) {
            counter += thread_id;
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
        }
    });
    std::thread t3([&counter](int thread_id = 3) {
        for (int i = 0; i < 10; ++i) {
            counter += thread_id;
            std::cout << "Thread " << thread_id << " set counter to: " << counter << std::endl;
        }
		});
    t1.join();
    t2.join();
    t3.join();
}
