#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

//task
struct node{
        char name[45];
        struct node*  next;
};

//gives length of list
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


void add(int index, char nm[45], struct node* hPtr){
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

int main(int argc, char **argv){

        //initialize list
        struct node* head= (struct node*) malloc(sizeof(struct node));
        head->next= NULL;

        //initialize variables
        int maxY, maxX;
        int cursorX= 0;
        int cursorY= 0;

        //initialize main window;
        initscr();
        noecho();
        getmaxyx(stdscr, maxY, maxX);
        WINDOW * mainWin= newwin(maxY-2, 70, 2, 37);
        refresh();
        box(mainWin, 0, 0);
        keypad(mainWin, true);
        wrefresh(mainWin);

        struct node* p= head;
        p= p->next;
        if(cursorX==0 & cursorY==0){
             wattron(mainWin, A_REVERSE);
        }
        mvwprintw(mainWin, 1,55,"add");
        if(cursorX==0 & cursorY==0){
                wattroff(mainWin, A_REVERSE);
        }

        if(cursorX==1 & cursorY==0){
                wattron(mainWin, A_REVERSE);
        }
        mvwprintw(mainWin, 1,62,"quit");
        if(cursorX==1 & cursorY==0){
                wattroff(mainWin, A_REVERSE);
        }
        for(int i= 1; i<=length(head); i++){
                if(cursorX==0 & cursorY==i){
                        wattron(mainWin, A_REVERSE);
                }
                mvwprintw(mainWin, i+1,1,"%s",p->name);
                if(cursorX==0 & cursorY==i){
                        wattroff(mainWin, A_REVERSE);
                }

                if(cursorX==1 & cursorY==i){
                        wattron(mainWin, A_REVERSE);
                }
                mvwprintw(mainWin, i+1,55,"update");
                if(cursorX==1 & cursorY==i){
                        wattroff(mainWin, A_REVERSE);
                }

                if(cursorX==2 & cursorY==i){
                        wattron(mainWin, A_REVERSE);
                }
                mvwprintw(mainWin, i+1,62,"delete");
                if(cursorX==2 & cursorY==i){
                        wattroff(mainWin, A_REVERSE);
                }
                p= p->next;
                wrefresh(mainWin);
        }


        //main loop
        int move;
        char out= 0;

        while(1){
                char name[45];
                char pty[4];
                int priority;
                move= wgetch(mainWin);
                switch(move){
                        case KEY_UP:
                                cursorY--;
                                if(cursorY==0){
                                        cursorY= 0;
                                }
                                break;
                        case KEY_DOWN:
                                cursorY++;
                                if(cursorY==length(head)){
                                        cursorY= length(head);
                                }
                                break;
                        case KEY_RIGHT:
                                cursorX++;
                                if(cursorX==2){
                                    cursorX= 2;
                                }
                                if(cursorY==0 & cursorX==1){
                                        cursorX= 1;
                                }
                                break;
                        case KEY_LEFT:
                                cursorX--;
                                if(cursorX==0){
                                        cursorX= 0;
                                }
                                break;
                        case 10:
                                //quit
                                if(cursorX==1 & cursorY==0){
                                        out= 1;
                                        break;
                                }
                                //add
                                else if(cursorX==0 & cursorY==0){
                                        echo();
                                        WINDOW * addWin= newwin(6, 50, 16, 47);
                                        refresh();
                                        box(addWin, 0, 0);
                                        wrefresh(addWin);

                                        mvwprintw(addWin, 1, 1, "Enter task: ");
                                        mvwprintw(addWin, 3, 1, "set priority of task: ");

                                        mvwgetnstr(addWin, 2, 1, name, 45);
                                        wrefresh(addWin);
                                        mvwgetnstr(addWin, 4, 1, pty, 4);
                                        wrefresh(addWin);
                                        priority= atoi(pty);
                                        if(priority>length(head)+1 | priority==0){
                                                priority= length(head)+1;
                                        }
                                        add(priority,name,head);
                                        werase(addWin);
                                        wrefresh(addWin);
                                        delwin(addWin);
                                        noecho();
                                }
                                //update
                                else if(cursorX==1  & cursorY!=0){
                                        echo();
                                        WINDOW * inWin= newwin(6, 50, 16, 47);
                                        refresh();
                                        box(inWin, 0, 0);
                                        wrefresh(inWin);

                                        mvwprintw(inWin, 1, 1,"update priorty");
                                        mvwprintw(inWin, 3, 1, "set new priority of task: ");

                                        mvwgetnstr(inWin, 4, 1, pty, 4);
                                        wrefresh(inWin);

                                        priority= atoi(pty);
                                        if(cursorY>length(head) | priority>length(head)){}
                                        transfer(cursorY,priority,head);
                                        werase(inWin);
                                        wrefresh(inWin);
                                        delwin(inWin);
                                        noecho();
                                }
                                //delete
                                else if(cursorX==2 & cursorX!=0){
                                     del(cursorY,head);
                                        mvwprintw(mainWin, cursorY, 1, "                                                                     ");                                }
                                break;
                        default:
                                continue;
                                break;
                        }

                //quiting procedure
                if(out==1){
                        break;
                }

                struct node* p= head;
                p= p->next;
                if(cursorX==0 & cursorY==0){
                        wattron(mainWin, A_REVERSE);
                }
                mvwprintw(mainWin, 1,55,"add");
                if(cursorX==0 & cursorY==0){
                        wattroff(mainWin, A_REVERSE);
                }

                if(cursorX==1 & cursorY==0){
                        wattron(mainWin, A_REVERSE);
                }
                mvwprintw(mainWin, 1,62,"quit");
                if(cursorX==1 & cursorY==0){
                        wattroff(mainWin, A_REVERSE);
                }
                for(int i= 1; i<=length(head); i++){
                        if(cursorX==0 & cursorY==i){
                                wattron(mainWin, A_REVERSE);
                                }
                        mvwprintw(mainWin, i+1,1,"%s",p->name);
                        if(cursorX==0 & cursorY==i){
                                wattroff(mainWin, A_REVERSE);
                        }

                        if(cursorX==1 & cursorY==i){
                                wattron(mainWin, A_REVERSE);
                        }
                        mvwprintw(mainWin, i+1,55,"update");
                        if(cursorX==1 & cursorY==i){
                                wattroff(mainWin, A_REVERSE);
                        }

                        if(cursorX==2 & cursorY==i){
                                wattron(mainWin, A_REVERSE);
                        }
                        mvwprintw(mainWin, i+1,62,"delete");
                        if(cursorX==2 & cursorY==i){
                                wattroff(mainWin, A_REVERSE);
                        }
                        p= p->next;
                        wrefresh(mainWin);
                }
        }
        endwin();
        return 0;
}
