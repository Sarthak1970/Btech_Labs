//create a structure for students containing name, roll no. ,cgpi and semester, create an array of struct of 10 students to store the above given information for all the studnets
//write another function to perform the following task --insert information at the kth position where the k is given by the user
//display the record of all students
//display records of all students having cgpi greater than k, value of k to be entered by the user
//write a menu driven program to implement above operations
#include <stdio.h>
struct student
{
    char name[20];
    int roll;
    float cg;
    int sem;
}index[10];
void displayAll(){
    for(int i=0;i<9;i++){
        printf("Name of the student: %s\n",index[i].name);
        printf("Roll number of the student: %d\n",index[i].roll);
        printf("CGPI of the student: %f\n",index[i].cg);
        printf("Semester: %d\n", index[i].sem);
    }
}

void greatercg(){
    float cgp;
    printf("Enter CGPI:");
        scanf("%f",&cgp);
    for(int i=0;i<9;i++){
        if(index[i].cg>cgp){
        printf("Name of the student: %s \n",index[i].name);
        printf("Roll number of the student: %d\n",index[i].roll);
        printf("CGPI of the student: %f\n",index[i].cg);
        printf("Semester: %d\n", index[i].sem);}
    }
}
void insert(){     //function to insert info about kth student
        int k=0;
        printf("Enter index at which info is to be inserted:");
        scanf("%d",&k);
        printf("Name of the student:");
        scanf("%s",&index[k].name);
        printf("Roll number of the student:");
        scanf("%d",&index[k].roll);
        printf("CGPI of the student:");
        scanf("%f",&index[k].cg);
        printf("Semester:");
        scanf("%d",&index[k].sem);
}
int main(){
   
   int choice=0;
   
   
   int opt=0;
   
   while(opt==0){
    
   printf("Enter 1 for displaying records of all students, 2 for displaying records for all student above a specific cgpi,3 for inserting information about the student");
   scanf("%d",&choice);
   switch (choice)
   {
   case 1: displayAll();
    break;
   case 2: greatercg();
   break;
   case 3: insert();
   break;
   
   }
   printf("Enter 0 for continuing and 1 to exit:");
   scanf("%d",&opt);
   }
}