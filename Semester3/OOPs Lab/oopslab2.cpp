#include<iostream>
using namespace std;

int avg_using_arr(int *arr,int n){
    int sum=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    return sum/n;
}

int largest_in_arr(int *arr,int n){
    int max=0;
    for(int i=0;i<n;i++){
        if(arr[i]>max) max=arr[i];
    }
    return max;
}

void matrix_insert(int matrix[][10], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> matrix[i][j];
        }
    }
}

void matrix_add(int mat1[][10], int mat2[][10], int result[][10], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}


int main(){
    //average and largest in array
    int n;
    cout<<"Enter the no. of elements of array : ";
    cin>>n;
    int arr[n];
    cout<<"Average of given numbers is: "<<avg_using_arr(arr,n)<<endl;
    cout<<"Largest number in the array is : "<<largest_in_arr(arr,n)<<endl;

    cout<<endl;

    //Addition of matrices
    cout<<"Enter no of rows of matrix1:"<<endl;
    int r1;
    cin>>r1;
    cout<<"Enter no of columns of matrix1:"<<endl;
    int c1;
    cin>>c1;
    
    int matrix1[10][10];  
    int matrix2[10][10];  
    int result[10][10];   

    // Insert elements
    cout << "Insert elements into matrix1:" << endl;
    matrix_insert(matrix1, r1, c1);

    int r2,c2;
    cout<<"Enter no of rows of matrix2:"<<endl;
    cin>>r2;
    cout<<"Enter no of columns of matrix2:"<<endl;
    cin>>c2;
    cout << "Insert elements into matrix2:" << endl;
    matrix_insert(matrix2, r2, c2);

    if(r1!=r2 && c1!=c2) cout<<"Addition of matrices not possible ."<<endl;
    else{
        matrix_add(matrix1, matrix2, result, r1, c1);        
    }

    // Print the result of matrix addition
    cout << "Result of matrix addition:" << endl;
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }


}