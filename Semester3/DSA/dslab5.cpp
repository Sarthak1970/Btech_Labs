//selection sort && insertion sort

#include<iostream>
using namespace std;

void swap(int &x,int &y){
    int temp=x;
    x=y;
    y=temp;
}

void print_arr(int *a,int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

void selection_sort(int *arr,int size){
    for(int i=0;i<size;i++){
        int index=i;
        for(int j=i+1;j<size;j++){
            if(arr[j]<arr[index]){
                swap(arr[j],arr[index]);
            }
        }
    }    
}

void insertion_sort(int *arr,int size){
    for(int i=1;i<size;i++){
        int key=arr[i];
        int j=i-1;
        while(arr[j]>key && j>=0){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

int main(){
    int size=5;
    int *arr = new int(size);
    cout<<"Enter elements of array : "<<endl;
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }

    cout<<"Array before sorting : ";
    print_arr(arr,size);

    selection_sort(arr,size);
    cout<<"Array after applying selection sort : ";
    print_arr(arr,size);

    insertion_sort(arr,size);
    cout<<"Array after applying insertion sort : ";
    print_arr(arr,size);

    delete[] arr;
}