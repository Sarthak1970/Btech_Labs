/*limit an input to range 0 to 9 by using a check input function and error handling*/

#include <iostream>
using namespace std;

int checkInput() {
    int input;
    cin >> input;

    if (input<0) throw "Error Code 2";
    else if(input>9) throw "Error Code 3";
    else return input;
}

int main() {
    int num;

    while(1){
        cout<<"Enter a number between 0 and 9 : ";
        try{
            num=checkInput();
            cout<<"You Entered "<<num<<endl;
        }
        catch(const char *msg){
            cerr<<msg<<endl;
        }
        int ch;
        cout<<"Enter 1 to exit and 2 to enter another number"<<endl;;
        cin>>ch;
        if(ch==1) break;
    }
    return 0;
}