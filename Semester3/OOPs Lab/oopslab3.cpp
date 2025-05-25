//1) searching in array , array of class , operation on string as array 
#include<iostream>
#include<string>
using namespace std;

class Students{
    public:
    int age;
    string name;

    void display(){
        cout<<"Name: "<<name<<" Age: "<<age<<endl;
    }
};

int linear_search(int *arr , int n , int target){
    for(int i=0;i<n;i++){
        if(arr[i]==target) return i;
    }
    return -1;
}

int binary_search(int *arr , int n , int target){
    int low=0 ,high=n-1;

    while(low<=high){
        int mid=(low+high)/2;

        if(arr[mid]==target) return mid;
        else if(arr[mid]<target) low=mid+1;
        else high=mid-1;
    }
    return -1;
}

int main(){
    // searching in array
    int arr[]={5,10,15,20,25};
    int n=sizeof(arr)/sizeof(arr[0]);
    
    int target;
    cout<<"Enter the target element to search: ";
    cin>>target;

    cout<<"Linear search: "<<endl;
    int index=linear_search(arr,n,target);
    if(index==-1) cout<<"Element not found"<<endl;
    else cout<<"Element found at index: "<<index<<endl;

    cout<<"Binary search: "<<endl;
    index=binary_search(arr,n,target);
    if(index==-1) cout<<"Element not found"<<endl;
    else cout<<"Element found at index: "<<index<<endl;  
    cout<<endl;

    //array of class
    Students* s = new Students[3];

    for(int i=0;i<3;i++){
        cout<<"Enter name: ";
        cin>>s[i].name;
        cout<<"Enter age: ";
        cin>>s[i].age;
    }

    for(int i=0;i<3;i++){
        cout<<"Name: "<<s[i].name<<" Age: "<<s[i].age<<endl;
    }
    cout<<endl;

    //operation on string as array;
    string str="SARTHUG";

    int str_len=str.length();

    for(int i=0;i<str_len;i++){
        cout<<str[i]<<" ";
    }

    return 0;
}