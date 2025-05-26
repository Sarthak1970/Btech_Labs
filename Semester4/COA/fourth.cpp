//Consensus Theorem
//AB + A'C + BC = AB + A'C

#include"gates.h"
#include<iostream>
using namespace std;

int main(){
    string a,b,c;
    cout<<"According to Consensus Theorem : AB + A'C + BC = AB + A'C"<<endl;
    cout<<"Enter First String (A):";
    cin>>a;
    cout<<"Enter Second String (B):";
    cin>>b;
    cout<<"Enter Third String (C):";
    cin>>c;

    string LHS=Or(Or(And(a,b),And(Not(a),c)),And(b,c));
    string RHS=Or(And(a,b),And(Not(a),c));

    cout<<"LHS="<<LHS<<endl;
    cout<<"RHS="<<RHS<<endl;
    if(LHS==RHS) cout<<"Hence Proved Consensus Theorem"<<endl;
    else cout<<"Consensus Theorem Failed"<<endl;
    return 0;
}