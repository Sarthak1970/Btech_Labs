//write a program to search an item in an array using binary search , if found delete that item from array and if not insert so that array remains sorted

#include<iostream>
using namespace std;

void print_array(int *arr , int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int binary_search(int *arr , int target , int n){
    int low=0 , high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==target){
            return mid;
        }
        else if(arr[mid]>target){
            high=mid-1; 
        }
        else{
            low=mid+1;
        }
    }
    return -1;
}

void insert_target(int *arr , int target , int &size){
    int i=0;
    while(i<size && arr[i]<target){
        i++;
    }
    for(int j=size;j>=i;j--){
        arr[j+1]=arr[j];
    }
    arr[i]=target;
    size++;
}

void delete_target(int *arr , int target , int &size , int &index){
    int i=0;
    while(i<=index && arr[i]<target){
        i++;
    }
    for(int j=i;j<size;j++){
        arr[j]=arr[j+1];
    }
    size--;
}

int main(){
    int size=6;
    int arr[10] = {5,10,15,20,25,29};

    int target;
    cout<<"Enter the element to search : ";
    cin>>target;
    int index=binary_search(arr,target,size);
    print_array(arr,size);


    if(index==-1){
        cout<<"Element not found"<<endl;
        insert_target(arr,target,size);
        cout<<"Inserting Element"<<endl;
        print_array(arr,size);
    }
    else{
        cout<<"Element found at index "<<index<<endl;
        delete_target(arr,target,size,index);
        cout<<"Deleting element"<<endl;
        print_array(arr,size);
    }
}