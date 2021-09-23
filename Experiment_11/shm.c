#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    key_t token = ftok("SHAREDMEM",69);
    int shmId = shmget(token, 1024, 0666|IPC_CREAT);
    char* str = (char*) shmat (shmId, (void*)0, 0);
    //int* str = (int*) shmat (shmld, (void*)0, 0);

    char str[1024] ;
    int choice;
    while(1) {
        printf("\n1. Write\n2. Read\n3. Stop\nEnter Choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: int data;// = rand();
                    printf("Data for the shared memory: ");//, data);
                    scanf("%d",&data);
                    sprintf(str,"%d",data);
                    break;
            case 2: printf("\nValue in the Shared Memory: %s\n",str);
                    break;
            case 3: printf("\nDetaching the shared memory\n");
                    shmdt(str);
                    shmctl(shmId, IPC_RMID,NULL); 
                    exit(0);
                    break;
            default: printf("Invalid option!!! \nEnter 1/2/3\n");
        }
    }
    return 0;
}
