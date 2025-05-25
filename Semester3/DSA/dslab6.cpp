//implement following sorting alog to sort an array
//1)Using merge sort
//2)Using quick sort
//also analyse best,worst,average case time and space complexity in both algorithms

#include<iostream>
using namespace std;

void print_arr(int *arr, int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);     

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quick_sort(int *arr, int low, int high) {
    if (low>=high) return;

    int pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
}

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i=0;i<n1;i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *arr, int left, int right) {
    if (left>=right) return;

        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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

    //quick_sort(arr,0,size-1);
    // cout<<"Array after applying quick sort : ";
    // print_arr(arr,size);

    merge_sort(arr,0,size-1);
    cout<<"Array after applying merge sort : ";
    print_arr(arr,size);

    delete[] arr;
}