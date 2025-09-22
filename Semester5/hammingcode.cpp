#include <iostream>
using namespace std;

void calculateparity(int m, int &r) {
    while ((1 << r) < (m + r + 1)) {
        r++;
    }
}

void Hammingencoder(int data[], int code[], int r, int m) {
    int n = m + r;
    int j = 0;

    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) {
            code[i] = 0; 
        } else {
            code[i] = data[j++];
        }
    }

    for (int i = 0; i < r; i++) {
        int pos = (1 << i); 
        int parity = 0;

        for (int j = 1; j <= n; j++) {
            if (j & pos) {
                parity ^= code[j];
            }
        }
        code[pos] = parity;
    }

    cout << "Encoded Codeword: ";
    for (int i = n; i >= 1; i--) cout << code[i] << " ";
    cout << endl;
}

void Hammingdecoder(int code[], int r, int m) {
    int n = m + r;
    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int pos = (1 << i); 
        int parity = 0;

        for (int j = 1; j <= n; j++) {
            if (j & pos) {
                parity ^= code[j];
            }
        }
        if (parity != 0) {
            errorPos += pos; 
        }
    }

    if (errorPos == 0) {
        cout << "No error detected." << endl;
    } else {
        cout << "Error detected at position: " << errorPos << endl;
        code[errorPos] ^= 1;
        cout << "Corrected Codeword: ";
        for (int i = n; i >= 1; i--) cout << code[i] << " ";
        cout << endl;
    }

    cout << "Decoded Data Bits: ";
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) != 0) { 
            cout << code[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    int m = 4; 
    int r = 0;

    calculateparity(m, r);

    int data[4] = {1, 0, 1, 1}; 
    int code[m + r + 1]; 

    Hammingencoder(data, code, r, m);

    //code[3] ^= 1; // flip bit at position 3
    cout << "Received Codeword: ";
    for (int i = m + r; i >= 1; i--) cout << code[i] << " ";
    cout << endl;

    Hammingdecoder(code, r, m);

    return 0;
}
