#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*******************************************************

Coding Assignment 1: Process Scheduling

Fahid AlKhatieb
20191501006

********************************************************/
// used pthreads to implement multithreading concept.
pthread_t tid0,tid1,tid2;
// condition will be used for context switch.
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct process{
int ID;
int duration;
char processname[10];
int priority;
struct process *next;
struct process *prev;
};

struct process *head = NULL;
struct process *tail = NULL;
int counter =0; //counter to keep track for # of processes
int prcs_starvation = 0;
struct process *newprocess;


struct process *new_process(int a,int t, char n[10],int p){
struct process *newprocess;
//size of string
size_t size = strlen(n) + 1;
newprocess = (struct process*)malloc(sizeof(struct process)+size);
newprocess->next=NULL;
newprocess->prev=NULL;
newprocess->ID=a;
newprocess->duration=t;
strcpy(newprocess->processname, n);
newprocess->priority=p;
counter++;
prcs_starvation++;
return newprocess;
}


void addprocesss(int a,int t,char n[],int p){
newprocess=new_process(a,t,n,p);
if(head == NULL)
{
head = newprocess;
tail = newprocess;
}
else
{
tail->next = newprocess;
newprocess->prev = tail;
tail = newprocess;
tail->next=head;
head->prev=tail;
}


}
void display(){
    struct process *temp;
    temp = head;
    int i;
    if (counter == 0)
        printf("list is empty\n");
    else
    {
        for (i = 0;i<counter;i++){
            printf(" %s -->> ",temp->processname);
            temp = temp->next;
    }
    printf("\n");
    }
}


void firstinsert(int a,int t, char n[], int p){
if(head == NULL)
{
head = newprocess;
tail = newprocess;
newprocess->next = head;
printf("\nprocess inserted successfully\n");
}
else
{
newprocess = new_process(a,t,n,p);
newprocess->next=head;
head->prev=newprocess;
head = newprocess;
newprocess->prev=tail;
tail->next=head;
printf("\nprocess inserted successfully\n");
}
}


void lastinsert(int a,int t,char n[], int p){
if(head == NULL)
 {
head = newprocess;
tail = newprocess;
newprocess->next = head;
printf("\nprocess inserted successfully\n");
 }
else
   {
    newprocess = new_process(a,t,n,p);
        tail->next=newprocess;
        newprocess->prev=tail;
        tail = newprocess;
        head->prev = tail;
        tail->next = head;
        printf("\nprocess inserted successfully\n");
    }
}


void midinsert(int pos, int a, int t, char n[], int p){
    struct process *temp,*temp2;
    newprocess = new_process(a,t,n,p);
if(head == NULL)
{
head = newprocess;
tail = newprocess;
newprocess->next = head;
printf("\nprocess inserted successfully\n");
}
else
{
    temp = head;
    temp2 = head;
    for(int i=1;i<pos;i++)
        temp=temp->next;
    for(int i=1;i<pos+1;i++)
        temp2=temp2->next;
    temp->next=newprocess;
    newprocess->prev=temp;
    newprocess->next=temp2;
    temp2->prev=newprocess;
    printf("\nprocess inserted successfully\n");
}}


void insert_alphabetically(int a,int t,char n[],int p){
nullprocessterminate(); // replace the null process with the new process
struct process *temp;
if(p > head->priority){ //checks priority to see if context switch is needed
    firstinsert(a,t,n,p);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    return;
}
int compare = strcmp(n, head->processname); // compares strings
printf("%d", compare);
if(head == NULL || compare <= 0){
    firstinsert(a,t,n,p);
    }
else if(strcmp(n, tail->processname) >= 0){
    lastinsert(a,t,n,p);
    }
else{
    temp = head->next;
    int pos=1;
    while(strcmp(n, temp->processname)>0){
        temp = temp->next;
        pos++;
        }
    midinsert(pos,a,t,n,p);
}}


void processexecute(){
       if(head == NULL)
{
    printf("\nQueue is empty\n");
   return;
}
else
{
 counter--;
 struct process *temp,*temp2;
 temp=head;
 temp2=head->next;
 tail->next=temp2;
 temp2->prev=tail;
 head=temp2;
 int id = temp->ID;
 free(temp);
 printf("\nprocess with the ID: %d has been Executed\n", id);
}}

void nullprocessterminate(){
   if(head == NULL)
{
   return;
}
else
{
    struct process *temp;
    struct process *temp2;
    temp = head->next;
    temp2 = head->next;
    int pos=1;
    while(temp->next->ID!=-1){
        temp = temp->next;
        pos++;
        }
     for(int i=1;i<=pos+1;i++){
        temp2 = temp2->next;
        }
    free(temp->next);
        counter--;
        temp->next=temp2;
        temp2->prev=temp;
}}


void process_starvation(){
struct process *temp1 = head;
struct process *temp2 = tail;
tail= temp2->prev;
tail->next=temp2;
head = temp2;
head->next=temp1;
printf("\nlast process moved to the head of the queue to avoid process starvation\n");
}

void *VirtualCPU(void *tid) {
    while(1){
    struct process *temp = head;
    if(counter == 0 || temp->ID==-1)
    {
        Sleep(5000);
        continue;
    }
    else
    {
        int processduration = temp->duration*1000;
        Sleep(processduration);
        processexecute();
    }
}}

void *ContextSwitch(void *tid) {
    while(1){
    pthread_mutex_lock(&lock);  //mutex may be unlocked only from insert_alphabetically function
    pthread_cond_wait(&cond, &lock);
    pthread_mutex_unlock(&lock);
    printf("\nprocess with higher priority has been created, context switch\n");
    pthread_cancel(tid0); //restarts the VirtualCPU
    pthread_create(&tid0, NULL, VirtualCPU,NULL);
    pthread_join( VirtualCPU, NULL);
    }
}

void *processes()
{
    int z;
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    addprocesss(-1,-1,"NULL",-1);
    printf("********* MENU *********\n");
    printf("Press 1 to Create a new Process\n");
    printf("Press 2 to Display processing queue\n");
    printf("Press 3 to Exit\n");
    printf("\nEnter your choice from Menu: ");
        scanf("%d",&z);
        printf("\n");
        int a,t,p,choice;
        char c[10];
    while(z>0 && z<=3)
    {
        switch(z)
        {
        case 1:
            printf("Enter the Process Name: ");
            scanf("%s",c);
            printf("Enter the Duration of the process in seconds: ");
            scanf("%d",&t);
            do{
            printf("Enter the Priority of the process between(0-10): ");
            scanf("%d",&p);}while(p<0&&p>10);
            printf("\n\nThe Process will be given Unique ID: %d\n\n", counter);
            insert_alphabetically(counter,t,c,p);
            if(((prcs_starvation-10)%3)==0 && prcs_starvation-10>1)
                process_starvation(); //every 3 processes added the tail becomes the head
        break;
        case 2 :
             display();
            break;
        case 3 :
            printf("\nYou exited the Program\n");
            return 0;
            break;
        }
        Sleep(10); //in order to let the below message to get displayed last
        printf("\nEnter your choice from the menu: ");
        scanf("%d",&z);
    }
    if(z>3||z<=0)
        printf("Enter a valid value ,, please restart the program");
    return;

}

int main(){
    pthread_create(&tid1, NULL, processes,NULL);
    pthread_create(&tid0, NULL, VirtualCPU,(void *)&tid0);
    pthread_create(&tid2, NULL, ContextSwitch,(void *)&tid2);
    pthread_join( tid1, NULL);
    pthread_join( tid0, NULL);
    pthread_exit(NULL);
    return 0;
}
