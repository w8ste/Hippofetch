#include <cmath>
#include <ios>
#include <iostream>
#include <chrono>
#include <ctime>    
#include <limits>
#include <linux/sysinfo.h>
#include <mutex>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
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
        "   \\     ,_,                ",
        "    \\   (0_0)_----------_   ",
        "       (_____)           |~'",
        "       `-\"-\"-'           /  ",
        "         `|__|~-----~|__|   ",
        "                            ",
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

std::string getUptime() {
    struct sysinfo info;
    sysinfo(&info);
    double up = info.uptime / 3600.0;
    int upHours = std::floor(info.uptime / 3600);
    int upMinutes = (up - upHours) * 60;
    return std::to_string(upHours).append(" hours, ")
           .append(std::to_string(upMinutes).append(" minutes"));
}

std::vector<std::string> getBubble(std::string user, std::string os) {
  std::string mid = "< ";
  mid.append(user.append("@").append(os).append(" >"));
  std::string top = " ";
  std::string bottom = " ";
  for(int i = 0; i < mid.length() - 2; i++) {
    top.append("_");
    bottom.append("-");
  }
  std::vector<std::string> bubble = {
    top,
    mid,
    bottom,
  }; 
  return bubble;
}

int main() {
    std::time_t time = getTime();
    std::cout << std::ctime(&time);
    utsname u; 
    u = getDistro();
    
    std::string infoArr[4];
    infoArr[0] = "OS: ";
    infoArr[0].append(u.nodename).append(" ").append(u.machine);
    infoArr[1] = "Kernel: ";
    infoArr[1].append(u.release);
    infoArr[2] = "User: ";
    infoArr[2].append(getUser());
    infoArr[3] = "Uptime: ";
    infoArr[3].append(getUptime());

    std::vector<std::string> bubble = getBubble(getUser(), u.nodename);
    int c = 0;
    for(std::string s : bubble) {
      for(char c : s) {
	std::cout << c ;
      }
      std::cout << "\n";
    }
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
