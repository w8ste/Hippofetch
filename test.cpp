#include <iostream>
#include <chrono>
#include <ctime>    
#include <string>
#include <stdio.h>
#include <vector>

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

std::vector<std::string> getLinuxLogo() {
    return {
        "           __      ",
        "             -=(o '.    ",
        "                '.-.\\   ",
        "                /|  \\  ",
        "                '|  ||  ",
        "       snd       _\\_):,_"
    };
}


int main() {
    std::time_t time = getTime();
    std::cout << std::ctime(&time);
    std::cout << getOsName();
    std::vector<std::string> logo = getLinuxLogo();
    for(std::string s : logo) {
        for(char c : s) {
            std::cout << c;
        }
        std::cout << "\n";
    }
    return 0;
}
