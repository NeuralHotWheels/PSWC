#include <ncurses/ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

//gcc -o task task.c lib.c -lncurses -DNCURSES_STATIC -> compile using this command

int main(){
    struct node* head = (struct node*) malloc(sizeof(struct node));
    strcpy(head->name, "null");
    head->next = NULL;
    initscr();
    noecho();
    cbreak();
    int height = 10; 
    int width = 20;
    int start_y = 10; 
    int start_x = 10;
    WINDOW * menuwin = newwin(height, width, start_y, start_x);
    box(menuwin,0,0);
    refresh();       
    wrefresh(menuwin);
    keypad(menuwin,true);
    char * choices[] = {"add","remove","update","view tasks"};    
    int choice;
    int highlight = 0;

    while(1){
        //print menu
        for(int i =0;i<4;i++){
            if(i==highlight){
                wattron(menuwin,A_REVERSE);
            }
            mvwprintw(menuwin,i+1,1, choices[i]);
            wattroff(menuwin,A_REVERSE);
        }
        choice = wgetch(menuwin);
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            case 10:
                if(strcmp(choices[highlight],"add")==0){
                    werase(menuwin);
                    box(menuwin,0,0);
                    mvwprintw(menuwin,1,1,"enter priority");
                    wrefresh(menuwin);
                    
                    char pT[10];
                    char task[50];
                    
                    echo();
                    mvwgetnstr(menuwin, 2, 1, pT, 50);
                    noecho();


                    mvwprintw(menuwin, 4, 1, "Priority:%s", pT);
                    mvwprintw(menuwin, 5, 1, "press any key to continue");
                    wrefresh(menuwin);

                    wgetch(menuwin);

                    werase(menuwin);
                    box(menuwin,0,0);
                    mvwprintw(menuwin, 1, 1, "enter task name");
                    echo();
                    mvwgetnstr(menuwin, 2, 1, task, 50);
                    noecho();
                    int priority = atoi(pT);
                    if(priority > length(head)+1){
                    priority = length(head)+1;
                    }
                    add(priority, task, head);
                    
                    mvwprintw(menuwin, 4, 1, "Press any key to return back to main menu");
                    wrefresh(menuwin);
                    wgetch(menuwin);
                    
                    werase(menuwin);
                    box(menuwin, 0, 0);

                }
                if(strcmp(choices[highlight],"view tasks")==0){
                    struct node *q = display(head);
                    int i = 3;
                    werase(menuwin);
                    box(menuwin,0,0);
                    mvwprintw(menuwin,2,1,q->name);
                    //printf("---START---\n");
                    if (q == NULL) {
                    mvwprintw(menuwin, 2, 1, "No tasks added.");
                    } else {
                    mvwprintw(menuwin, 2, 1, "--- Task List ---");
                    while (q != NULL) {
                    mvwprintw(menuwin, i, 1, "%d:%s",i-2,q->name);
                    q = q->next;
                    i++;
                            }
                    }
                    wrefresh(menuwin); 
                    wgetch(menuwin);
                    werase(menuwin);
                    box(menuwin, 0, 0);    
                }
                break;
        }
    }

    return 0;
}

