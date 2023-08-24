#include <iostream>
#include <chrono>
#include <ctime>    
#include <string>
#include <stdio.h>
std::time_t getTime() {
    auto start = std::chrono::system_clock::now();
 
    std::time_t time = std::chrono::system_clock::to_time_t(start);
 
    return time;
    
}

std::string getOsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

int main() {
    std::time_t time = getTime();
    std::cout << std::ctime(&time);
    std::cout << getOsName();
    return 0;
}
