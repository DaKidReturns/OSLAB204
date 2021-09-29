#include<unistd.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
int* arr;
void wait(int* n){
    printf("Consumer is consuming..... \n");
    int flag = 0;
    while((*n)<=0)
        if(!flag){
            printf("Buffer is empty\n");
            flag=1;
        }
    (*n)--;
}

void signal(int* n){
    while((*n)<=arr[0]);
    (*n)++;
}

int main(){
    key_t key = ftok("SHAREDMEM",69);
    int shm_id = shmget(key, 1024,0666|IPC_CREAT);
    arr = (int*)shmat(shm_id,(void*)0, 0);

    //printf("The item in the memory is : %s\n",str);
    int item =rand();
    wait(arr+1);
    signal(arr+2);

    printf("Consumed item is %d\n",arr[arr[2]+3]);
    
    return 0;
}
