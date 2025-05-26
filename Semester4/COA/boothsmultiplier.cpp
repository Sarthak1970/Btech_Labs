#include <iostream>
#include <bitset>
#include <string>
using namespace std;
// Function to perform arithmetic right shift
int arithmeticRightShift(int x, int shift) {
    return (x >> shift) | (x & (1 << 31) ? ~((1 << 31) - 1) << (32 - shift) : 0);
}
int boothMultiplication(int multiplicand, int multiplier) {
    int product = 0;
    int M = multiplicand;
    int Q = multiplier;
    int A = 0;
    int Q_1 = 0;
    cout << "Initial values:" << endl;
    cout << "A: " << bitset<32>(A) << endl;
    cout << "Q: " << bitset<32>(Q) << endl;
    cout << "Q_1: " << Q_1 << endl;
    cout << "M: " << bitset<32>(M) << endl;
    cout << endl;

    for (int i = 0; i < 32; i++) {
        cout << "Step " << i + 1 << ":" << endl;
        // Check the least significant bit of Q and Q_1
        int QQ_1 = (Q & 1) | (Q_1 << 1);
        switch (QQ_1) {
            case 1: // 01
                A = A + M;
                break;
            case 2: // 10
                A = A - M;
                break;
            default: // 00 or 11
                // Do nothing
                break;
        }
        // Arithmetic right shift the A:Q pair
        Q_1 = Q & 1;
        Q = (Q >> 1) | ((A & 1) << 31);
        A = arithmeticRightShift(A, 1);
        cout << "A: " << bitset<32>(A) << endl;
        cout << "Q: " << bitset<32>(Q) << endl;
        cout << "Q_1: " << Q_1 << endl;
        cout << endl;
    }

    product = (A << 32) | Q;
    return product;
}
int main() {
    int multiplicand, multiplier;
    cout << "Enter the multiplicand: ";
    cin >> multiplicand;
    cout << "Enter the multiplier: ";
    cin >> multiplier;
    int result = boothMultiplication(multiplicand, multiplier);
    cout << "Result of multiplication: " << result << endl;
    cout << "Binary representation: " << bitset<64>(static_cast<unsigned long long>(result)) << endl;
    return 0;
}