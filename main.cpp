#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <ios>
#include <iostream>
#include <chrono>
#include <ctime>    
#include <limits>
#include <linux/sysinfo.h>
#include <mutex>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <vector>
#include <cctype>
#include <unistd.h>
#include <filesystem>

using namespace std;

string getUser() {
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

string getOsName()
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
vector<std::string> getHippo() {
    vector<std::string> s;
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
vector<std::string> getLinuxLogo() {
    return {
        "           __      ",
        "             -=(o '.    ",
        "                '.-.\\   ",
        "                /|  \\  ",
        "                '|  ||  ",
        "       snd       _\\_):,_",
    };
}

vector<string> getBubble(string user, string os) {
  string mid = "< ";
  mid.append(user.append("@").append(os).append(" >"));
  string top = " ";
  string bottom = " ";
  for(int i = 0; i < mid.length() - 2; i++) {
    top.append("_");
    bottom.append("-");
  }
  vector<string> bubble = {
    top,
    mid,
    bottom,
  }; 
  return bubble;
}

string runCommand(string cmd) {
    cmd.append(" 2>&1");

    FILE *file;
    const int max = 256;
    char buffer[max];

    string data;

    file = popen(cmd.c_str(), "r");
    if (file) {
      while (!feof(file))
        if (fgets(buffer, max, file) != NULL)
          data.append(buffer);
      pclose(file);
    }
    return data;
}

time_t getTime() {
    auto start = chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(start);
    return time;
}

string getPackageCount(char *distro) {
  //string pack = 0;
    namespace fs = filesystem;
    fs::path arch{"/etc/arch-release"};
    if (fs::exists(arch)) {
      return runCommand("pacman -Q | wc -l");
    }
    fs::path deb{"/etc/debian_version"};
    if (fs::exists(deb)) {
      return runCommand("apt list --installed | wc -l");
    }
    fs::path red{"/etc/redhat-release"};
    if (fs::exists(red)) {
      return runCommand("yum list | wc -l");
    }
    fs::path gent{"/etc/gentoo-release"};
    if (fs::exists(gent)) {
      return runCommand("equery list \"*\" | wc -l");
    }
    fs::path alp{"/etc/alp-release"};
    if (fs::exists(alp)) {
      return runCommand("apk info | wc -l");
    }
    fs::path sus{"/etc/SuSE-release"};
    if (fs::exists(sus)) {
      return runCommand("zypper se -i -t package | wc -l");
    }

    

    return "Error, please create an issue, which includes your distrobution";
}

utsname getDistro() {
   utsname result;
   uname(&result);
   return result; 
}

string getUptime() {
    struct sysinfo info;
    sysinfo(&info);
    double up = info.uptime / 3600.0;
    int upHours = floor(info.uptime / 3600);
    int upMinutes = (up - upHours) * 60;
    return to_string(upHours).append(" hours, ")
           .append(to_string(upMinutes).append(" minutes"));
}

int main() {
    time_t time = getTime();
    cout << std::ctime(&time);
    utsname u;
    u = getDistro();
    string infoArr[5];
    string packageCount = getPackageCount(u.nodename);
    std::stringstream trimmer;
    trimmer << packageCount;
    packageCount.clear();
    trimmer >> packageCount;
    infoArr[0] = "OS: ";
    infoArr[0].append(u.nodename).append(" ").append(u.machine);
    infoArr[1] = "Kernel: ";
    infoArr[1].append(u.release);
    infoArr[2] = "Packages: ";
    infoArr[2].append(packageCount);
    infoArr[3] = "Uptime: ";
    infoArr[3].append(getUptime());
    infoArr[4] = "Shell: ";
    string s = runCommand("echo $SHELL");
    infoArr[4].append(s.substr(s.size() - 5));

    vector<std::string> bubble = getBubble(getUser(), u.nodename);
    int c = 0;
    for(string s : bubble) {
      for(char c : s) {
	cout << c ;
      }
      cout << "\n";
    }

    int counter = 0;
    vector<std::string> logo = getHippo();
    for(string s : logo) {
        for(char c : s) {
            cout << c;
        }
        string info = ((counter <
			end(infoArr) - begin(infoArr)
                            ? infoArr[counter] : ""));
        cout << "      "
                  << info
                  << "\n";
        counter++;
    } 
    return 0;
}
