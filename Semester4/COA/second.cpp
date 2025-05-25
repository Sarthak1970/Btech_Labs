#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

string reverse_string(string s) {
    reverse(s.begin(), s.end());
    return s;
}

string positive(int n) {
    if (n == 0) return "00000000";
    
    string ans;
    int x = abs(n);
    
    while (x > 0) {
        ans.push_back((x % 2) + '0');
        x /= 2;
    }
    
    while (ans.size() < 8) {
        ans.push_back('0');
    }

    return reverse_string(ans);
}

string signed_rep(int n) {
    string ans = positive(n);
    ans[0] = (n < 0) ? '1' : '0';
    return ans;
}

string ones_rep(int n) {
    if (n >= 0) return positive(n);

    string ans = positive(n);
    for (char &c : ans) {
        c = (c == '0') ? '1' : '0';
    }
    return ans;
}

string twos_rep(int n) {
    if (n >= 0) return positive(n);
    
    string ones = ones_rep(n);
    for (int i = 7; i >= 0; i--) {
        if (ones[i] == '0') {
            ones[i] = '1';
            break;
        } else {
            ones[i] = '0';
        }
    }

    return ones;
}

string biased_rep(int n) {
    int bias = 128;
    int x = n + bias;
    return positive(x);
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Unsigned representation: " << positive(n) << endl;
    cout << "Signed bit representation: " << signed_rep(n) << endl;
    if (n < 0) {
        cout << "1's Complement representation: " << ones_rep(n) << endl;
        cout << "2's Complement representation: " << twos_rep(n) << endl;
    }
    cout << "Biased representation: " << biased_rep(n) << endl;
    return 0;
}
