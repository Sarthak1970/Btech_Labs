//implement a 4 bit carry look ahead adder

#include <iostream>
#include "gates.h"
using namespace std;

int main() {
    string A0, A1, A2, A3;
    string B0, B1, B2, B3;
    string Cin = "0";

    cout << "Enter 4-bit number A (LSB to MSB, space-separated): ";
    cin >> A0 >> A1 >> A2 >> A3;

    cout << "Enter 4-bit number B (LSB to MSB, space-separated): ";
    cin >> B0 >> B1 >> B2 >> B3;

    string P0 = Xor(A0,B0), G0 = And(A0,B0);
    string P1 = Xor(A1,B1), G1 = And(A1,B1);
    string P2 = Xor(A2,B2), G2 = And(A2,B2);
    string P3 = Xor(A3,B3), G3 = And(A3,B3);

    string C0 = Cin;
    string C1=Or(G0,Cin), C2=Or(G1,C1), C3=Or(G2,C2), C4=Or(G3,C3);

    string S0 = Xor(P0,C0);
    string S1 = Xor(P1,C1);
    string S2 = Xor(P2,C2);
    string S3 = Xor(P3,C3);

    // Output result
    cout << "Sum: " << S3 << S2 << S1 << S0 << endl;
    cout << "Final Carry: " << C4 << endl;

    return 0;
}
