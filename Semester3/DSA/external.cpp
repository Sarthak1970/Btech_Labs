#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(int d){
        data=d;
        next=NULL;
    }
};

void Display(Node *head){
    Node *temp=head;
    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
    cout<<"NULL"<<endl;
}

Node* Insert(Node *head, int val){
    Node *newnode = new Node(val);
    newnode->next = head;
    return newnode;
}

void split(Node *head, Node *&L1, Node *&L2){
    if(head == NULL)
        return;

    Node *temp = head;
    while(temp != NULL){
        if(temp->data % 2 == 0){
            L2 = Insert(L2, temp->data);
        }
        else{
            L1 = Insert(L1, temp->data);
        }
        temp = temp->next;
    }
}

int main(){
    Node *head = NULL;
    Node *L1 = NULL;
    Node *L2 = NULL;
    cout << "1) Display head\n2) Insert\n3) Split\n4) Display L1\n5) Display L2\n6) Exit" << endl;

    while(1){
        int choice;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                Display(head);
                break;
            case 2:
                int val;
                cout << "Enter Val to insert: ";
                cin >> val;
                head = Insert(head, val);
                break;
            case 3:
                split(head, L1, L2);
                break;
            case 4:
                Display(L1);
                break;
            case 5:
                Display(L2);
                break;
            case 6:
                exit(0);
            default:
                cout << "Enter Valid Choice: " << endl;
                break;
        }
    }
    return 0;
}