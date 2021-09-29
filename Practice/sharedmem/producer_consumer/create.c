#include<unistd.h>
#include<sys/shm.h>
#include<stdio.h>

int main(){
    key_t key = ftok("SHAREDMEM",39);
    int shm_id = shmget(key, 1024,0666|IPC_CREAT);
    int *arr = (int*)shmat(shm_id,(void*)0, 0);
    printf("Enter buffer size: ");
    scanf("%d",&arr[0]);
    arr[1] = 0;// full
    arr[2] = arr[0]; //empty

    return 0;
}
