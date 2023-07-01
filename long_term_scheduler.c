#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
    int pno;
    int bound;
    struct node* next;
};
void push(struct node** head, int x, int b)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->pno = x;
    newnode->bound = b;
    if(*head==NULL)
    {
        *head = newnode;
        newnode->next = NULL;
        return;
    }
    struct node* temp = *head;
    while(temp->next!=NULL) {
        temp=temp->next;
    } 
    temp->next = newnode;
    newnode->next = NULL;
}
void display(struct node* head)
{
    if(head == NULL)
    {
        printf("Empty Q\n");
        return;
    }
    printf("PNO Bound(CPU/IO)\n");
    while(head!=NULL) {
        printf("%d %d\n",head->pno,head->bound);
        head=head->next;
    }printf("\n");
    return;
}
int* pop(struct node** head, int *x) 
{
    if (*head == NULL) {
        printf("Empty Q pop\n");
        return 0;
    }
    if((*head)->next == NULL)
    {
        x[0] = (*head)->pno;
        x[1] = (*head)->bound;
        free(*head);
        *head = NULL;
        return x;
    }
    struct node* temp = *head;
    struct node* prev = *head;
    while(temp->next!=NULL) {
        prev = temp;
        temp=temp->next;
    }
    x[0] = temp->pno;
    x[1] = temp->bound;
    prev->next = NULL;
    free(temp);
    return x;
}
int main()
{
    struct node* inq = NULL;
    struct node* outq = NULL;
    int n, P[2], count=0, cpu = 2, io = 0;
    int *a;
    printf("enter number of processes - ");
    scanf("%d",&n);
    srand(time(0));
    for(int i=0;i<n;i++)
        push(&inq,rand()%1000,rand()%2);   
    printf("\n/Input Queue/\n");
    display(inq);
    for (int i = 0; i < n;)
    {
        while(count < 2)
        {   
            a = pop(&inq,P);
            i++;
            if(a[1]==1)
            {
                push(&outq,a[0],a[1]);
                count++;
            }
        }
        a = pop(&inq,P);
        i++;
        if (a[1] == 1)
        {
            push(&outq,a[0],a[1]);
            cpu++;
        }
        if (a[1]==0 && cpu>io)
        {
            push(&outq,a[0],a[1]);
            io++;
        }
    }
    printf("\n/Output Queue/\n");
    display(outq);   
}

