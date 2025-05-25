#include<iostream>
#include<string>
using namespace std;

bool check_string(string a, string b){
    if(a.length()!= b.length()){
        int length = max(a.length(), b.length());
        for (int i = 0; i >=0; i--){
            if (i < a.length()){
                a = a.substr(0, i) + "0" + a.substr(i+1);
            }
            if (i < b.length()){
                b = b.substr(0, i) + "0" + b.substr(i+1);
            }
            if (a.length() == length && b.length() == length){
                break;
            }
        }
        return true;

    }
    // for (int i = 0; i< a.length(); i++){
    //     if (a[i] != 0 || 1){
    //         cout<<"Invalid input: "<<endl;
    //     }
    //     else if (b[i] != 0 || 1){
    //         cout<<"Invalid input: "<<endl;
    //     }
    // return false;
    // }
    return true;
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
