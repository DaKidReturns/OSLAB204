#include<unistd.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
int* arr;
void wait(int* n){
    printf("Producer is producing..... \n");
    int flag = 0;
    while((*n)<=0)
        if(!flag){
            printf("Waiting for consumer to consume\n");
            flag=1;
        }
    (*n)--;
}

void signal(int* n){
    while((*n)==1);
    (*n)++;
}

int main(){
    key_t key = ftok("SHAREDMEM",69);
    int shm_id = shmget(key, 1024,0666|IPC_CREAT);
    arr = (int*)shmat(shm_id,(void*)0, 0);

    //printf("The item in the memory is : %s\n",str);
    int item =rand();
    wait(arr+2);
    signal(arr+1);
    printf("Item entered: %d\n",item);
    arr[arr[1]+3] = item;
    
    return 0;
}
