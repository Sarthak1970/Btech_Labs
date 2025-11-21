#include<iostream>
#include<limits.h>
using namespace std;

int main(){
    int n;
    cout<<"Enter size of array : ";
    cin>>n;

    int arr[n];

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    int maxi=INT_MIN;
    for(int i=0;i<n;i++){
        maxi=max(maxi,arr[i]);
    }

    cout<<"Maximum number in the array is : "<<maxi;
    return 0;
}