//demonstrate order of execution in constructor and destructor in base class and derived class

#include<iostream>
using namespace std;

class Base{
    int x;

    public:
    Base(int val){
        cout<<"Base Constructor"<<endl;
        int x=val;
    }
    Base(){
        cout<<"Base Constructor called within derived class"<<endl;
    }

    ~Base(){
        cout<<"Base Destructor"<<endl;
    }
};

class Derived : public Base{
    int y;

    public:
    Derived(int val){
        cout<<"Derived Constructor"<<endl;
        int y=val;
    }

    ~Derived(){
        cout<<"Derived Destructor"<<endl;
    }
};

int main(){
    // Base a(1);
    Derived b(2);
}

