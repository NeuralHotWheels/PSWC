#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//[]->[]->[].. []->[]->NULL

//task store in nodes
struct node{
    char name[50];
    struct node*  next;
};

//output number of nodes
int length(struct node* hPtr){
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

//hPtr: list head pointer
//print name of nodes
void print(struct node* hPtr){
    if(length(hPtr)==0){
        printf("no tasks added\n");
        return;
    }
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

//NOTE: NODES ARE 1 INDEXED 
/*
add node
priority->index 
name of node-> nm
*/
void add(int index, char nm[50], struct node* hPtr){
    if(length(hPtr)+1<index){
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

/*
delete node
priority->index 
*/
void del(int index, struct node* hPtr){
    if(length(hPtr)<index){
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

/*
change priority node
initial priority->i1 
final priority-> i2
*/
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

    char cmd[20];
    //state loop
    while(1) {
        /*display loop commands
            -tasks: displays all tasks in list
            -add: add tasks
        */
        printf("COMMAND SET:\n-tasks\n-add\n-update\n-remove\n-quit\n--");
        scanf("%s",cmd);
        
        // add new task
        if(strcmp(cmd,"add")==0){
            int pT;
            char nT[50];
            printf("enter task name: ");
            scanf(" %49[^\n]",nT);
            printf("enter task priority: ");
            scanf("%d",&pT);
            
            if(pT>length(head)+1){
                pT= length(head)+1;
            }
            add(pT,nT,head);
            printf("task added\n");
        }
        //show task list
        else if(strcmp(cmd,"tasks")==0){
            print(head);
            printf("len: %d\n",length(head));
        }
        //update task
        else if(strcmp(cmd,"update")==0){
            print(head);
            int pT1;
            int pT2;
            printf("enter priority of task: ");
            scanf("%d",&pT1);
            printf("enter new priority of task: ");
            scanf("%d",&pT2);
            if(pT1>length(head) | pT2>length(head)){
                printf("index out of bound");
            }
            transfer(pT1,pT2,head);
            print(head);
        }
        //delete
        else if(strcmp(cmd,"remove")==0){
            int pT;
            printf("enter priority of tasks to be removed: ");
            scanf("%d",&pT);
            if(pT>length(head)){
                printf("task with priorty %d does not exist", pT);
            }
            else{
                printf("task removed\n");
            }
            del(pT,head);
            
        }
        //quit
        else if(strcmp(cmd,"quit")==0){
            printf("...exiting...");
            break;
        }
        //default
        else{
            printf("invalid command");
        }
    printf("\n");
    }
}