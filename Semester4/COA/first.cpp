#include<iostream>
#include<string>
using namespace std;

bool ANDGATE(string &s){
    for(int i=0;i<s.size();i++){
        if(s[i]=='0')
        return 0;
    }
    return 1;
}

bool ORGATE(string &s){
    for(int i=0;i<s.size();i++){
        if(s[i]=='1')
        return 1;
    }
    return 0;
}

bool NOTGATE(char ch){
    if(ch=='1') return 0;
    else return 1;
}

bool XORGATE(string &s){
    int count=0;
    for(int i=0;i<s.size();i++){
        if(s[i]=='1')
        count+=1;
    }
    return (count%2);
}

bool NANDGATE(string &s){
    bool andres=ANDGATE(s);
    char ch = andres ? '1' : '0'; 
    return NOTGATE(ch);
}

bool NORGATE(string &s){
    bool norres=ORGATE(s);
    char ch = norres ? '1' : '0'; 
    return NOTGATE(ch);
}

bool XNORGATE(string &s){
    bool xorres=XORGATE(s);
    char ch = xorres ? '1' : '0'; 
    return NOTGATE(ch);
}

int main(){
    string s;
    cout<<"Enter a binary string :";
    getline(cin,s);
    cout<<"AND "<<ANDGATE(s)<<endl;
    cout<<"OR "<<ORGATE(s)<<endl;
    cout<<"XOR "<<XORGATE(s)<<endl;
    cout<<"NAND "<<NANDGATE(s)<<endl;
    cout<<"NOR "<<NORGATE(s)<<endl;
    cout<<"XNOR "<<XNORGATE(s)<<endl;

    cout<<"Enter a character to find NOT ";
    char ch;
    cin>>ch;
    cout<<"NOT of "<<ch<<" is "<<NOTGATE(ch);
}