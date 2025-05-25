#include<iostream>
using namespace std;

bool bitwiseoperator(int a){
    if(a&1) return true;
    else return false;
}

int fibo(int n){
    if(n<=1) return n;
    else{
        return fibo(n-1)+fibo(n-2);
    }
}

void swap(int &a , int &b){
    int temp=a;
    a=b;
    b=temp;
}

int quotient(int a, int b){
    return a/b;
}

int remainder(int a , int b){
    return a%b;
}

void printASCII(char c){
    cout<<"ASCII value of "<<c<<" is "<<int(c)<<endl;
}



int main(){

    //fibo
    cout<<"Enter The No. : ";
    int n;
    cin>>n;
    cout<<n<<" th Fibbonacci no. is "<<fibo(n)<<endl;

    //swap
    int x,y;
    cin>>x>>y;
    swap(x,y);
    cout<<x<<" "<<y<<endl;

    //quotient and remainder
    int a,b;
    cin>>a>>b;
    if(b==0) cout<<"Cant divide by 0";
    else{
        cout<<"Quotient : "<<quotient(a,b)<<endl;
        cout<<"Remainder : "<<remainder(a,b)<<endl; 
    }

    //print ASCII
    char c;
    cin>>c;
    printASCII(c);

    // bitwise operator
    int bit;
    cin>>bit;
    if(bitwiseoperator(bit)) cout<<"Odd"<<endl;
    else cout<<"Even"<<endl;


    return 0;
}
