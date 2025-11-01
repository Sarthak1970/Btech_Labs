#include<stdio.h>
#include<stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* createLinkedList(int data){
    struct ListNode *newnode;

    newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(newnode == NULL){
        printf("Memory Allocation failed\n");
        return NULL;
    }

    newnode->val = data;
    newnode->next = NULL;

    return newnode;
}

void addnewnodeatend(struct ListNode *head, int data){
    struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(newnode == NULL){
        printf("Memory Allocation failed\n");
        return;
    }
    newnode->val = data;
    newnode->next = NULL;

    struct ListNode* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode;
}

void traversal(struct ListNode *head){
    struct ListNode* temp = head;
    if(temp == NULL){
        printf("List is empty\n");
        return;
    }
    while(temp != NULL){
        printf("%d", temp->val);
        if(temp->next != NULL)
            printf(" --> ");
        temp = temp->next;
    }
    printf(" --> NULL\n");
}

int main(){
    struct ListNode* head = NULL;
    int choice, data;

    while(1){
        printf("\nEnter Your Choice:\n1. Enter a node\n2. Traverse\n3. Exit\n");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Enter Data for the node: ");
            scanf("%d", &data);
            if(head == NULL){
                head = createLinkedList(data);
            }
            else{
                addnewnodeatend(head, data);
            }
        }
        else if(choice == 2){
            traversal(head);
        }
        else if(choice == 3){
            printf("Exiting\n");
            break;
        }
        else{
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}