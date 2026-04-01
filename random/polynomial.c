#include <stdio.h>
#include <stdlib.h>
struct node {
    int coiff;
    int pow;
    struct node * next;
};
struct node* head;

struct node* createnode(int coiff, int pow){
    struct node * newnode=(struct node*)malloc(sizeof(struct node));
    newnode->coiff=coiff;
    newnode->pow=pow;
    newnode->next=NULL;
    return newnode;
}
void insertnode(struct node** head,int coiff,int pow){
    struct node * newnode=createnode(coiff,pow);
    if(*head==NULL){
        *head=newnode;
    }
    struct node * temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
        temp->next=newnode;
    }
    return;
}

void dispoly(struct node* head){
    struct node* temp=head;
    while(temp!=NULL){
        printf("%dx^%d",temp->coiff,temp->pow);
        if(temp->next!= NULL){
            printf("+");
        }
        temp=temp->next;
    }
    printf("\n");
}
int main() {
    struct node* poly1=NULL;
    insertnode(&poly1,4,2);
    printf("the first polynomial is:");
    dispoly(poly1);
   

    return 0;
}