#include <iostream>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>

using namespace std;

int main() {
    struct ifaddrs *interfaces;
    if (getifaddrs(&interfaces) == -1) {
        cout << "Error getting interfaces "<<endl;
        return 1;
    }

    struct ifaddrs *temp = interfaces;

    cout << "IP and MAC Address Finder\n\n";

    while (temp != nullptr) {
        if (temp->ifa_addr != nullptr) {
            string ifaceName = temp->ifa_name;
            if (ifaceName != "lo") {  
                cout << "Interface: " << ifaceName << "\n";

                int family = temp->ifa_addr->sa_family;

                if (family == AF_INET) {  // IPv4
                    char ip[100];
                    inet_ntop(AF_INET, &((struct sockaddr_in *)temp->ifa_addr)->sin_addr, ip, 100);
                    cout << "IPv4 Address: " << ip << "\n";
                } else if (family == AF_INET6) {  // IPv6
                    char ip[100];
                    inet_ntop(AF_INET6, &((struct sockaddr_in6 *)temp->ifa_addr)->sin6_addr, ip, 100);
                    cout << "IPv6 Address: " << ip << "\n";
                }

                string macPath = "/sys/class/net/" + ifaceName + "/address";
                ifstream macFile(macPath);
                string mac;
                if (macFile.is_open()) {
                    getline(macFile, mac);
                    cout << "MAC Address: " << mac << "\n";
                } else {
                    cout << "MAC Address: N/A\n";
                }

                cout << "\n";
            }
        }
        temp = temp->ifa_next;
    }

    freeifaddrs(interfaces);
    return 0;
}
