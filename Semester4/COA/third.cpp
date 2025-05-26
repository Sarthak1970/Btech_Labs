#include<iostream>
#include"gates.h"
using namespace std;

/*
NOT(A AND B)=(NOT A)OR(NOT B)

NOT(A OR B)=(NOT A)AND(NOT B)
*/

void demorgan1(string a,string b){
    string s1=Not(And(a,b));
    string s2=Or(Not(a),Not(b));
    cout<<"NOT OF A AND B ="<<s1<<endl;
    cout<<"NOT A OR NOT B ="<<s2<<endl;

    if(s1==s2) cout<<"Hence Implemented Demorgan's first law"<<endl;
    else cout<<"First law failed."<<endl;
}

void demorgan2(string a,string b){
    string s1=Not(Or(a,b));
    string s2=And(Not(a),Not(b));
    cout<<"NOT OF A OR B ="<<s1<<endl;
    cout<<"NOT A AND NOT B ="<<s2<<endl;

    if(s1==s2) cout<<"Hence Implemented Demorgan's second law"<<endl;
    else cout<<"Second Lae Failed."<<endl;
}


int main(){
    string s1="01001";
    string s2="01100";
    demorgan1(s1,s2);
    demorgan2(s1,s2);
    return 0;
}
