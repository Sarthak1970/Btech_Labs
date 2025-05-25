/*write a menu driven program to implement following 
1)insert a node at front of a linked list
2)insert a node at end
3)insert a node at a given user
4)delete first node of a linked list
5)delete last node of a list
6)delete a node from a given position
7)display elements of a linked list*/

#include<iostream>
using namespace std;

struct node{
    int data;
    struct node *next;
}*head=NULL;

void insert_at_start(int val){
    struct node *newNode = new node;
    newNode->data=val;
    newNode->next=head;
    head=newNode;
}

void insert_at_end(int val){
    struct node *newNode=new node;
    newNode->data=val;
    newNode->next=NULL;

    if(head==NULL){
        head=newNode;
        return;
    }
    struct node* temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newNode;
}

void insert_at_pos(int val,int pos){
    if(pos<1){
        cout<<"Invalid position"<<endl;
        return;
    }
    struct node *newNode=new node;
    newNode->data=val;
    newNode->next=NULL;

    if(pos==1){
        newNode->next=head;
        head=newNode;
        return;
    }
    struct node *temp=head;
    for(int i=1;i<pos-1 && temp!=NULL;i++){
        temp=temp->next;
    }

    if(temp==NULL){
        cout<<"Invalid position"<<endl;
        return;
    }
    newNode->next=temp->next;
    temp->next=newNode;
}

void delete_first(){
    if(head==NULL){
        cout<<"Underflow"<<endl;
        return;
    }
    struct node *temp=head;
    head=head->next;
    delete temp;
}

void delete_last(){
    if(head==NULL){
        cout<<"Underflow"<<endl;
        return;
    }
    struct node*temp=head;
    struct node*prev=NULL;
    while(temp->next!=NULL){
        prev=temp;
        temp=temp->next;
    }
    if(temp==head){
        head=NULL;
    }
    else{
        prev->next=NULL;
        delete temp;
    }
}

void delete_at_pos(int pos){
    if(pos<1){
        cout<<"Invalid position"<<endl;
        return;
    }
    if(head==NULL){
        cout<<"Underflow"<<endl;
        return;
    }
    struct node *temp=head;
    struct node *prev=NULL;
    for(int i=1;i<pos && temp!=NULL;i++){
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        cout<<"Invalid position"<<endl;
        return;
    }
    if(temp==head){
        head=head->next;
        delete temp;
    }
    else{
        prev->next=temp->next;
        delete temp;
    }
}

void display(){
    struct node *temp=head;
    while(temp!=NULL){
        cout<<temp->data<<"-->";
        temp=temp->next;
    }
    cout<<"NULL"<<endl;
    return;
}

int main(){
    int choice,val,pos;
    cout<<"1. Display linked list"<<endl;
    cout<<"2. Insert Node at start"<<endl;
    cout<<"3. Insert Node at end"<<endl;
    cout<<"4. Insert Node at position"<<endl;
    cout<<"5. Delete first Node"<<endl;
    cout<<"6. Delete Last Node"<<endl;
    cout<<"7. Delete Node at position"<<endl;
    cout<<"8. Exit"<<endl;

    while(1){
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1: 
                display();
                break;
            case 2:
                cout<<"Enter Value to insert:";
                cin>>val;
                insert_at_start(val);
                break;
            case 3:
                cout<<"Enter Value to insert:";
                cin>>val;
                insert_at_end(val);
                break;
            case 4:
                cout<<"Enter Value to insert:";
                cin>>val;
                cout<<"Enter position to insert:";
                cin>>pos;
                insert_at_pos(val,pos);
                break;
            case 5:
                delete_first();
                break;
            case 6:
                delete_last();
                break;
            case 7:
                cout<<"Enter position to delete:";
                cin>>pos;
                delete_at_pos(pos);
                break;
            case 8:
                cout<<"Exiting...";
                exit(0);

            default:
            cout<<"Invalid choice! Try again.\n";
        }
    }
    delete[] head;
}