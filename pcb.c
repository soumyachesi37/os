#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
    int pno;
    int cpuBT;
    int ioBT;
    int totalBT;
    int pr;
    int status;
    struct node* next;
};
void push(struct node** head, int p, int c, int i, int t, int s)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->pno = p;
    newnode->cpuBT = c;
    newnode->ioBT = i;
    newnode->totalBT = t;
    newnode->status = s;
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
    printf("Process Number\tCPU Burst\tIO Burst\tTotal Burst\tStatus(CPU/IO)\n");
    while(head!=NULL) {
        printf("      %d\t   %d\t\t   %d\t\t     %d\t\t     %d\n",head->pno,head->cpuBT,head->ioBT,head->totalBT,head->status);
        head=head->next;
    }printf("\n");
    return;
}

void pr_display(struct node* head)
{
    if(head == NULL)
    {
        printf("Empty Q\n");
        return;
    }
    printf("Process Number\tCPU Burst\tIO Burst\tTotal Burst\tStatus(CPU/IO)\tPriority\n");
    while(head!=NULL) {
        printf("      %d\t   %d\t\t   %d\t\t     %d\t\t     %d\t\t    %d\n",head->pno,head->cpuBT,head->ioBT,head->totalBT,head->status,head->pr);
        head=head->next;
    }printf("\n");
    return;
}

void FrontBackSplit(struct node* source,struct node** frontRef, struct node** backRef)
{
	struct node* fast;
	struct node* slow;
	slow = source;
	fast = source->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

struct node* SortedMerge(struct node* a, struct node* b)
{
	struct node* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (a->totalBT <= b->totalBT) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}

void MergeSort(struct node** headRef)
{
	struct node* head = *headRef;
	struct node* a;
	struct node* b;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	FrontBackSplit(head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	*headRef = SortedMerge(a, b);
}

void assignPR(struct node** head,int n)
{
    if (*head == NULL) {
        printf("Empty Q pop\n");
        return;
    }
    if((*head)->next == NULL)
    {
        (*head)->pr = 0;
        return;
    }
    struct node* temp = *head;
    int pr_count = 0;
    while (temp!=NULL)
    {
        temp->pr = pr_count;
        if(temp->next!=NULL)
        {
            if(temp->totalBT != (temp->next)->totalBT)
                pr_count++;
        }
        temp = temp->next;
    }    
}

int main()
{
    struct node* inq = NULL;
    int n, total=0, cpu = 2, io = 0, status;
    printf("enter number of processes - ");
    scanf("%d",&n);

    srand(time(0));
    for(int i=0;i<n;i++)
    {
        cpu = rand()%10;
        io = rand()%10;
        total = cpu + io;
        status = cpu > io;
        push(&inq,rand()%1000,cpu,io,total,status);   
    }
    printf("\n/Input Queue/\n");
    display(inq);
    MergeSort(&inq);
    assignPR(&inq, n);
    printf("\n/Output Queue/\n");
    pr_display(inq);
}

