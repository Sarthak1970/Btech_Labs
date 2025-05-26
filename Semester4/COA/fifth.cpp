#include<iostream>
#include"gates.h"

using namespace std;

void HalfAdder(string a,string b){
    string sum=Xor(a,b);
    string carry=And(a,b);
    cout<<"Sum using Half Adder: "<<sum<<endl;
    cout<<"Carry using Half Adder: "<<carry<<endl;
}

void FullAdder(string a,string b,string c){
    string sum1=Xor(a,b);
    string carry1=And(a,b);
    string sum2=Xor(sum1,c);
    string carry2=Or(carry1,And(sum1,c));
    cout<<"Sum using Full Adder: "<<sum2<<endl;
    cout<<"Carry using Full Adder: "<<carry2<<endl;
}

int main(){
    string a,b;
    cout<<"Enter first binary string :";
    cin>>a;
    cout<<"Enter second binary string :";
    cin>>b;

    HalfAdder(a,b);
    FullAdder(a,b,"0");
}