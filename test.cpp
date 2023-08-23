#include <iostream>
#include <chrono>
#include <ctime>    

int main() {
    auto start = std::chrono::system_clock::now();
 
    std::time_t time = std::chrono::system_clock::to_time_t(start);
 
    std::cout << std::ctime(&time);
}
