#include <iostream>
#include <thread>

int main()
{
	int a1 = 5, a2 = 7, a3 = 10;
    std::thread t1([a1]() {std::cout << "Tread1: " << a1 * a1 << std::endl; });
    std::thread t2([a2]() {std::cout << "Tread2: " << a2 * a2 << std::endl; });
    std::thread t3([a3]() {std::cout<<"Tread3: "<<a3*a3<<std::endl;});
    t1.join();
    t2.join();
    t3.join();
}
