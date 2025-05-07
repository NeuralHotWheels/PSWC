struct node {
    char name[50];
    struct node* next;
};

int length(struct node* hPtr);
void print(struct node* hPtr);
void add(int index, char nm[50], struct node* hPtr);
void del(int index, struct node* hPtr);
void transfer(int i1, int i2, struct node* hPtr);