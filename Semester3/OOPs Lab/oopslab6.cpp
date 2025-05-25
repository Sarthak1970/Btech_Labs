#include <iostream>
using namespace std;

// class S1 {
// private:
//     int l1;

// public:
//     S1(int val) : l1(val) {}

//     friend class S2;

//     int getL1() {
//         return l1;
//     }
// };

// class S2 {
// private:
//     int l2;

// public:
//     S2(int val) : l2(val) {}

//     void compareL1L2(S1& obj) {
//         if (obj.l1 == l2) {
//             cout << "l1 and l2 are equal." << endl;
//         } else if (obj.l1 > l2) {
//             cout << "l1 is greater than l2." << endl;
//         } else {
//             cout << "l1 is smaller than l2." << endl;
//         }
//     }

//     int getL2() {
//         return l2;
//     }
// };

// void externalCompare(S1& obj1, S2& obj2) {
//     if (obj1.getL1() == obj2.getL2()) {
//         cout << "l1 and l2 are equal (External comparison)." << endl;
//     } else if (obj1.getL1() > obj2.getL2()) {
//         cout << "l1 is greater than l2 (External comparison)." << endl;
//     } else {
//         cout << "l1 is smaller than l2 (External comparison)." << endl;
//     }
// }

// int main() {
//     S1 obj1(8);  
//     S2 obj2(5);  
//     obj2.compareL1L2(obj1); 

//     externalCompare(obj1, obj2); 

//     return 0;
// }

class C1{
    int x;
    int y;

    public:
    C1(int a,int b):x(a),y(b){};

    friend class C2;

    int getx(){
        return x;
    }
    int gety(){
        return y;
    }
};

class C2{
    int a;
    int b;

    public:
    C2(int c,int d):a(c),b(d){};

    void compare(C1 &obj){
        if(obj.x==b && obj.y==a){
            cout<<"x and y are equal"<<endl;
        }
        else if(obj.x>b && obj.y>a){
            cout<<"x and y are greater"<<endl;
        }
        else{
            cout<<"x and y are smaller"<<endl;
        } 
    }

    int geta(){
        return a;
    }
    int getb(){
        return b;
    }
};

void externalcomparison(C1 &obj1 , C2 &obj2){
    if(obj1.getx()==obj2.getb() && obj1.gety()==obj2.geta()){
        cout<<"x and y are equal"<<endl;
    }
    else if(obj1.getx()>obj2.getb() && obj1.gety()>obj2.geta()){
        cout<<"x and y are greater"<<endl;
    }
    else{
        cout<<"x and y are smaller"<<endl;
    }
}

int main(){
    C1 obj1(8,9);
    C2 obj2(5,6);
    C1 obj3();
    cout<<obj3.getx()<<endl;
    obj2.compare(obj1);
    externalcomparison(obj1,obj2);
    return 0;
}

