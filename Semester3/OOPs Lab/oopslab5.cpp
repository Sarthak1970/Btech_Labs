#include <iostream>
using namespace std;
class P{
    protected:
    int prote;
    private:
    int priva;
    public:
    int publ;
    P(){
        prote=1;
        priva=2;
        publ=3;
    }
};
class A: public P{
    public:
    A(){
    cout<<"Calling value of public variable in publicly derived class A from P--"<<P::publ<<endl;}

};
class B: protected P{
public:
    B(){
    cout<<"Calling value of protected variable in protected derived class B from P--"<<P::prote<<endl;}
};
class C: private P{
public:
    C(){
    //cout<<"Calling value of private variable in privately derived class C from P--"<<P::priva;
    }
};
int main(){
    A a;
    B b;
    C c;
    return 0;
}