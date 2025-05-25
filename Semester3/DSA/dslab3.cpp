//bubble sort 

#include<iostream>
using namespace std;

void swap(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}

void print_arr(int *a , int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

void bubble_sort(int *arr , int n){
    bool flag=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                flag=0;
            }
        }
    if(flag==1) break;
    }
}

int main(){
    int size=5;
    int *arr = new int(size);
    cout<<"Enter the values in array:";
    for (int i=0;i<size;i++)
    {
        cin>>arr[i];
    }
    cout<<"Array before sorting : ";
    print_arr(arr,size);

    bubble_sort(arr,size);

    cout<<"Array after sorting : ";
    print_arr(arr,size);

    delete []arr;
}