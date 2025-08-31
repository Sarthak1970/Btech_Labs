#include <iostream>
using namespace std;

// PARITY
string paritySender(string data) {
    int count = 0;
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '1') count++;
    }
    if (count % 2 == 0)
        data = data + '0';
    else
        data = data + '1';
    return data;
}

bool parityReceiver(string data) {
    int count = 0;
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '1') count++;
    }
    if (count % 2 == 0) return true;
    else return false;
}

// CHECKSUM
string checksumSender(string blocks[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int val = 0;
        for (int j = 0; j < 8; j++) {
            if (blocks[i][j] == '1') val += (1 << (7 - j));
        }
        sum += val;
    }
    sum = 255 - (sum % 256);
    string check = "";
    for (int i = 7; i >= 0; i--) {
        if ((sum >> i) & 1) check += '1';
        else check += '0';
    }
    return check;
}

bool checksumReceiver(string blocks[], int n, string check) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int val = 0;
        for (int j = 0; j < 8; j++) {
            if (blocks[i][j] == '1') val += (1 << (7 - j));
        }
        sum += val;
    }
    int c = 0;
    for (int i = 0; i < 8; i++) {
        if (check[i] == '1') c += (1 << (7 - i));
    }
    sum += c;
    if (sum % 256 == 255) return true;
    else return false;
}

// CRC
string xorBits(string a, string b) {
    string r = "";
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == b[i]) r += '0';
        else r += '1';
    }
    return r;
}

string crcSender(string data, string div) {
    int n = div.length();
    for (int i = 0; i < n - 1; i++) data += '0';
    string temp = data.substr(0, n);
    for (int i = n; i < data.length(); i++) {
        temp = xorBits(temp, div).substr(1) + data[i];
    }
    string rem = xorBits(temp, div).substr(1);
    return data.substr(0, data.length() - (n - 1)) + rem;
}

bool crcReceiver(string data, string div) {
    int n = div.length();
    string temp = data.substr(0, n);
    for (int i = n; i < data.length(); i++) {
        temp = xorBits(temp, div).substr(1) + data[i];
    }
    string rem = xorBits(temp, div).substr(1);
    for (int i = 0; i < rem.length(); i++) {
        if (rem[i] == '1') return false;
    }
    return true;
}

int main(){
    string data = "1011001";
    string sent = paritySender(data);
    cout << "Sent with parity: " << sent << endl;
    if (parityReceiver(sent)) cout << "Parity check: No Error\n";
    else cout << "Parity check: Error Detected\n";

    int n = 3;
    string blocks[3] = {"10101010", "11001100", "11110000"};
    string check = checksumSender(blocks, n);
    cout << "Checksum: " << check << endl;
    if (checksumReceiver(blocks, n, check)) cout << "Checksum check: No Error\n";
    else cout << "Checksum check: Error Detected\n";

    string crcData = "1101011011";
    string crcDiv = "10011";
    string crcSent = crcSender(crcData, crcDiv);
    cout << "Sent with CRC: " << crcSent << endl;
    if (crcReceiver(crcSent, crcDiv)) cout << "CRC check: No Error\n";
    else cout << "CRC check: Error Detected\n";

    return 0;
}

