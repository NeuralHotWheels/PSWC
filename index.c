#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct node{
    char name[50];
    struct node*  next;
};

void print(struct node* hPtr){
    struct node* p= hPtr;
    p= p->next;
    int i= 1;
    printf("---START---\n");
    while(p!=NULL){
        printf("%d  %s\n",i, p->name);
        p= p->next;
        i++;
    }
    printf("---END---\n");
}

int lenght(struct node* hPtr){
    struct node* p= hPtr;
    p= p->next;
    int i= 1;
    while(p!=NULL){
        p= p->next;
        i++;
    }
    i--;
    return i;
}

void add(int index, char nm[50], struct node* hPtr){
    if(lenght(hPtr)+1<index){
        printf("add: index out of bound at %d\n",index);
        return;
    }
    struct node* p= hPtr;
    for(int i= 1; i< index; i++){
        p= p->next;
    }
    struct node* new= (struct node*) malloc(sizeof(struct node));
    new->next= p->next;
    p->next= new;
    strcpy(new->name, nm);
}

void del(int index, struct node* hPtr){
    if(lenght(hPtr)<index){
        printf("del: index out of bound at %d\n",index);
        return;
    }
    struct node* p= hPtr;
    for(int i= 1; i< index; i++){
        p= p->next;
    }
    struct node* old= p->next;
    p->next= old->next;
    free(old);
}

void transfer(int i1, int i2, struct node* hPtr){
    int r= 0;
    if(i1==i2){
        return;
    } else if(i1>i2){
        r= 1;
    }
    struct node* p= hPtr;
    for(int i= 1; i< i1; i++){
        p= p->next;
    }
    p= p->next;
    struct node* q= hPtr;
    for(int i= 1; i< i2; i++){
        q= q->next;
    }
    add(i2+1-r, p->name,hPtr);
    del(i1+r,hPtr);
}

int main(){
    //init list
    struct node* head= (struct node*) malloc(sizeof(struct node));
    char t[50];
    strcpy(head->name, "null");
    head->next= NULL;

}