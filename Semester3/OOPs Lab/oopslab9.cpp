#include<iostream>
#include<vector>

using namespace std;

float divide(int a,int b){
    if(b==0){
        throw "Division by zero not possible";
    }
    return (float)a/b;
}

int main(){
    int a,b;
    cout<<"Enter two numbers: ";
    cin>>a>>b;
    try{
        cout<<"Result: "<<divide(a,b)<<endl;
    }
    catch(const char* msg){
        cerr<<msg<<endl;
    }

    vector<int> vecA={1,0,3,4,5,};
    vector<int> vecB(5);
    vector<int> vecC(5,0);
    vector<int> vecD(vecC);

    cout << "vecA: ";
    for(int val : vecA) cout << val << " ";
    cout << endl;

    cout << "vecB: ";
    for(int val : vecB) cout << val << " ";
    cout << endl;

    cout << "vecC: ";
    for(int val : vecC) cout << val << " ";
    cout << endl;

    cout << "vecD (copy of vecC): ";
    for(int val : vecD) cout << val << " ";
    cout << endl;

    vecC.push_back(5);

    cout << "vecC after inserting 5 at the end: ";
    for(int val : vecC) cout << val << " ";
    cout << endl;

    vecC.pop_back();
    vecC.pop_back();

    cout << "vecC after removing 2 values from the end: ";
    for(int val : vecC) cout << val << " ";
    cout << endl;



    return 0;
}