#include<iostream>
#include<string>
using namespace std;

bool check_string(string &a, string &b){
    int max_length = max(a.length(), b.length());
    while (a.length() < max_length) {
        a = "0" + a;
    }
    while (b.length() < max_length) {
        b = "0" + b;
    }
    return a.length() == b.length();
}

string Or(string a, string b){
    check_string(a,b);
    string res = "";
    for (int i = 0; i< a.length(); i++){
        if (a[i] == '1' || b[i] == '1'){
            res +="1";
        }
        else {
            res +="0";
        }
    }
    return res;
}
string And(string a, string b){
    check_string(a,b);
    string res = "";
    for (int i = 0; i< a.length(); i++){
        if (a[i] == '1'&& b[i] == '1'){
            res +="1";
        }
        else {
            res +="0";
        }
    }
    return res;
}

string Not(string a) {
    string res(a.size(), '0');
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '0') {
            res[i] = '1';
        } else {
            res[i] = '0';
        }
    }
    return res;
}

string Xor(string a,string b){
    string res="";
    int length=max(a.length(),b.length());
    check_string(a,b);
    for (int i = 0; i<length; i++){
        if (a[i] != b[i]){
            res +="1";
        }
        else {
            res +="0";
        }
    }
    return res;
}
