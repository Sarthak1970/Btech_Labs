#include<string>
#include <iostream>
using namespace std;

int iterativemultiplier(int a, int b){
    int result = 0;
   while (b>0){
       if (b & 1){
        result +=a;
       }
       a<<=1;
       b>>=1;
   }
   return result;
}

int main() {
    int a, b;
    cout <<"Enter first number";
    cin >> a;
    cout << "enter second number";
    cin >> b;
    int product = iterativemultiplier(a,b);
    cout <<"product"<<product<<endl;
    return 0;
}
