/*Experiment 8
Write a menu driven program to implement following operations on the circular doubly linked list. Please make sure that all the functions are working for all the possible test cases.
(a) Insert a node at the front of the linked list.
(b) Insert a node at the end of the linked list.
(c) Insert a node at the given position in the link list where position will be entered by the user.
(d) Delete first node of the linked list.
(e) Delete last node of the list.
(f) Delete a node at the given position where position will be entered by the user.
(g) Display the elements of the link list.*/

#include<iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
    struct node* prev;
}*head=NULL;

void display(){
    if(head == NULL){ 
        cout << "List is empty!" << endl;
        return;
    }

    struct node* temp = head;
    do {
        cout << temp->data << " <-> ";
        temp = temp->next;
    } while(temp != head);
    cout << "HEAD" << endl;
}

void insert_at_start(int val){
    struct node* newNode = new node;
    newNode->data = val;

    if(head == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }

    struct node* tail = head->prev;
    newNode->next = head;
    newNode->prev = tail;
    head->prev = newNode;
    tail->next = newNode;
    head = newNode;  
}

void insert_at_end(int val){
    struct node* newNode = new node;
    newNode->data = val;

    if(head == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
        return;
    }
    struct node* tail = head->prev;
    tail->next = newNode; 
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
}

void insert_at_pos(int val, int pos){
    if(pos < 1){
        cout << "Invalid position" << endl;
        return;
    }

    if(pos == 1){
        insert_at_start(val);
        return;
    }

    struct node* newNode = new node;
    newNode->data = val;

    struct node* temp = head;
    for(int i = 1; i < pos - 1; i++){
        temp = temp->next;
        if(temp == head){
            cout << "Invalid position" << endl;
            return;
        }
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

void delete_start(){
    if(head == NULL){
        cout << "List is empty!" << endl;
        return;
    }

    if(head->next == head){
        delete head;
        head = NULL;
        return;
    }

    struct node* tail = head->prev;
    struct node* temp = head;
    head = head->next;
    head->prev = tail;
    tail->next = head;

    delete temp;
}

void delete_at_end(){
    if(head == NULL){
        cout << "List is empty!" << endl;
        return;
    }

    if(head->next == head){
        delete head;
        head = NULL;
        return;
    }

    struct node* tail = head->prev;
    struct node* second_last = tail->prev;

    second_last->next = head;
    head->prev = second_last;

    delete tail;
}

void delete_at_pos(int pos){
    if(head == NULL){
        cout << "List is empty!" << endl;
        return;
    }

    if(pos == 1){
        delete_start();
        return;
    }

    struct node* temp = head;
    for(int i = 1; i < pos; i++){
        temp = temp->next;
        if(temp == head){
            cout << "Invalid position" << endl;
            return;
        }
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    delete temp;
}

int main(){
    int choice, val, pos;
    cout << "1. Display linked list" << endl;
    cout << "2. Insert Node at start" << endl;
    cout << "3. Insert Node at end" << endl;
    cout << "4. Insert Node at position" << endl;
    cout << "5. Delete first Node" << endl;
    cout << "6. Delete last Node" << endl;
    cout << "7. Delete Node at position" << endl;
    cout << "8. Exit" << endl;

    while(1){
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                display();
                break;
            case 2:
                cout << "Enter value to insert at start: ";
                cin >> val;
                insert_at_start(val);
                break;
            case 3:
                cout << "Enter value to insert at end: ";
                cin >> val;
                insert_at_end(val);
                break;
            case 4:
                cout << "Enter value to insert: ";
                cin >> val;
                cout << "Enter position to insert: ";
                cin >> pos;
                insert_at_pos(val, pos);
                break;
            case 5:
                delete_start();
                break;
            case 6:
                delete_at_end();
                break;
            case 7:
                cout << "Enter position to delete: ";
                cin >> pos;
                delete_at_pos(pos);
                break;
            case 8:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
