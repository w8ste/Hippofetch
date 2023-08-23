#include <iostream>
#include <chrono>
#include <ctime>    
#include <string>

std::time_t getTime() {
    auto start = std::chrono::system_clock::now();
 
    std::time_t time = std::chrono::system_clock::to_time_t(start);
 
    return time;
    
}
int main() {
    std::time_t time = getTime();
    std::cout << std::ctime(&time);
    return 0;
}
