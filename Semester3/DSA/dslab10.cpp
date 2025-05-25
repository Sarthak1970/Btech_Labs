/*
Experiment 10
I.	Write a program to implement Circular QUEUE using Array that performs following operations
(e)	INSERT 
(f)	DELETE 
(g)	DISPLAY

II.	Write a program to implement QUEUE using Linked List that performs following operations
(h)	INSERT 
(i)	DELETE 
(j)	DISPLAY
*/

#include<iostream>
using namespace std;

struct node{
    int data;
    node *next;
};

struct queue{
    node *front;
    node *rear;

    queue(){
        front=rear=NULL;
    }

    void Enqueue(int data){
        node *temp =new node;
        temp->data=data;
        temp->next=NULL;
        if(front==NULL){
            front=rear=temp;
            return;
        }
        rear->next=temp;
        rear=temp;
    }

    void Dequeue(){
        if(front==NULL){
            cout<<"Queue is empty"<<endl;
            return;
        }
        if(front==rear){
            delete front;
            delete rear;
            return;
        }
        node *temp=front;
        front=front->next;
        delete temp;
    }

    void Display(){
        if(front==NULL){
            cout<<"Queue is empty"<<endl;
            return;
        }
        node *temp=front;
        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
};

struct Circular_queue{
    int size;
    int *cq;
    int front,rear;

    Circular_queue(int s){
        size=s;
        cq=new int[size];
        front=rear=-1;
    }

    void Enqueue(int data){
        if((front==0 && rear==size-1) || (rear==front-1)){
            cout<<"Overflow"<<endl;
            return;
        }
        if(front==-1){
            front=rear=0;
            cq[front]=data;
            return;
        }
        if(front != 0 && rear==size-1){
            rear=0;
            cq[rear]=data;
            return;
        }
        rear+=1;
        cq[rear]=data;
    }    

    void Dequeue(){
        if(front==-1){
            cout<<"Underflow"<<endl;
            return;
        }
        if(front==rear){
            front=rear=-1;
            return;
        }
        if(front==size-1 && rear!=front){
            front=0;
            return;
        }
        front+=1;    
    }

    void Display(){
        if(front==-1){
            cout<<"Queue is empty"<<endl;
            return;
        }
        if(rear>=front){
            for(int i=front;i<=rear;i++){
                cout<<cq[i]<<" ";
            }
        }
        else{
            for(int i=front;i<size;i++){
                cout<<cq[i]<<" ";
            }
            for(int i=0;i<=rear;i++){
                cout<<cq[i]<<" ";
            }
        }
        cout<<endl;
    }

    ~Circular_queue(){
        delete cq;
    }
};

int main(){
    queue q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Display();
    q.Dequeue();
    q.Display();

    Circular_queue cq(5);
    cq.Enqueue(1);
    cq.Enqueue(2);
    cq.Enqueue(3);
    cq.Display();
    cq.Dequeue();
    cq.Display();

    return 0;
}