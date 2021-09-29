#include<unistd.h>
#include<sys/shm.h>
#include<stdio.h>

int main(){
    key_t key = ftok("SHAREDMEM",69);
    int shm_id = shmget(key, 1024,0666|IPC_CREAT);
    char *str = (char*)shmat(shm_id,(void*)0, 0);
    printf("The item in the memory is : %s\n",str);
    
    return 0;
}
