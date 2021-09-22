#include<stdio.h>
#include<stdlib.h>

int mutex=1, full=0, empty=3, x=0;

int wait(int s){
    s--;
    return s;
}

int signal(int s){
    s++;
    return s;
}

void producer(){
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("Producer produced item %d\n",x);
    mutex = signal(mutex);
}

void consumer(){
    mutex = wait(mutex);
    empty = signal(empty);
    full = wait(full);
    printf("Consumer consumed item %d\n",x);
    x--;
    mutex = signal(mutex);
}

int main(){
    int n,bs;
    printf("Enter the buffer size: ");
    scanf("%d",&bs);
    empty = bs;
    while (1){
        printf("\n1.Producer\n2.Consumer\n3.Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&n);
        switch(n){
            case 1: if ((mutex==1)&& empty != 0){
                        producer();
                    }else{
                        printf("Buffer is full!!\n");
                    }
                    break;
            case 2: if((mutex==1)&& full!=0){
                        consumer();
                    }
                    else{
                        printf("Buffer is empty\n");
                    }
                    break;
            case 3: exit(0);
                    break;

        }
    }
    return 0;
}

