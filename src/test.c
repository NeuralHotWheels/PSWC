#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
//gcc -o test test.c lib.c  use this to create executable test.exe
int main() {
    struct node* head = (struct node*) malloc(sizeof(struct node));
    strcpy(head->name, "null");
    head->next = NULL;

    char cmd[20];

    while(1) {
        printf("COMMAND SET:\n-tasks\n-add\n-update\n-remove\n-quit\n--");
        scanf("%s", cmd);

        if(strcmp(cmd, "add") == 0){
            int pT;
            char nT[50];
            printf("enter task priority: ");
            scanf("%d", &pT);
            printf("enter task name: ");
            scanf("%s", nT);

            if(pT > length(head)+1){
                pT = length(head)+1;
            }
            add(pT, nT, head);
            printf("task added\n");
        }
        else if(strcmp(cmd, "tasks") == 0){
            print(head);
            printf("len: %d\n", length(head));
        }
        else if(strcmp(cmd, "update") == 0){
            print(head);
            int pT1, pT2;
            printf("enter priority of task: ");
            scanf("%d", &pT1);
            printf("enter new priority of task: ");
            scanf("%d", &pT2);
            if(pT1 > length(head) || pT2 > length(head)){
                printf("index out of bound\n");
            } else {
                transfer(pT1, pT2, head);
                print(head);
            }
        }
        else if(strcmp(cmd, "remove") == 0){
            int pT;
            printf("enter priority of task to be removed: ");
            scanf("%d", &pT);
            if(pT > length(head)){
                printf("task with priority %d does not exist\n", pT);
            } else {
                del(pT, head);
                printf("task removed\n");
            }
        }
        else if(strcmp(cmd, "quit") == 0){
            printf("...exiting...\n");
            break;
        }
        else{
            printf("invalid command\n");
        }
        printf("\n");
    }

    return 0;
}
