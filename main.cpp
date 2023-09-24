#include <iostream>
#include <chrono>
#include <ctime>    
#include <mutex>
#include <string>
#include <stdio.h>
#include <vector>
#include <sys/utsname.h>
#include <vector>
#include <cctype>
#include <unistd.h>

std::time_t getTime() {
    auto start = std::chrono::system_clock::now();
 
    std::time_t time = std::chrono::system_clock::to_time_t(start);
     
    return time;
}

std::string getUser() {
    #ifdef _WIN32
    #include<windows.h>
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    return GetUserName(username, &username_len);
    #elif _WIN64
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    return GetUserName(username, &username_len);
    #elif __linux__
    return getlogin();
    #endif
    return 0;
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

// Ascii Art of hippo
std::vector<std::string> getHippo() {
    std::vector<std::string> s;
    s= {
        "     ,_,                ",
        "    (0_0)_----------_   ",
        "   (_____)           |~'",
        "   `-\"-\"-'           /  ",
        "     `|__|~-----~|__|   ",
        "                        ",

    };
    /*
    s = {
        "     ,_,                ",
        "    (0_0)_----------_   ",
        "   (_____)           |~'",
        "   `-"-"-'           /  ",
        "     `|__|~-----~|__|   ",
        "                        ",
    }; */
    return s;
}

// penguin ascii art
std::vector<std::string> getLinuxLogo() {
    return {
        "           __      ",
        "             -=(o '.    ",
        "                '.-.\\   ",
        "                /|  \\  ",
        "                '|  ||  ",
        "       snd       _\\_):,_",
    };
}

utsname getDistro() {
   utsname result;
   uname(&result);
   return result; 
}


int main() {
    std::time_t time = getTime();
    std::cout << std::ctime(&time);
    //std::string os = getOsName();
    utsname u; 
    u = getDistro();
    
    std::string infoArr[4];
    infoArr[0] = u.sysname;
    infoArr[1] = u.nodename;
    infoArr[1].append("  ").append(u.machine);
    infoArr[2] = u.release;
    infoArr[3] = getUser();
    
    int counter = 0;
    std::vector<std::string> logo = getHippo();
    for(std::string s : logo) {
        for(char c : s) {
            std::cout << c;
        }
        std::string info = ((counter < end(infoArr) - begin(infoArr)
                            ? infoArr[counter] : ""));
        std::cout << "      "
                  << info
                  << "\n";
        counter++;
    } 
    return 0;
}
