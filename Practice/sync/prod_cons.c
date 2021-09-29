#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

//int * buffer;
int buffer[1000];
int num[] = {0,1,2,3,4,5};

sem_t empty,full;
pthread_mutex_t mutex;

int n;
int out,in;

void* producer(void* pno){
    int item;
    while(1){
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Inseted Item %d at %d\n",*(int *)pno, item, in);
        in = (in+1)%n;
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* cno){
    int item;
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("Consumer %d: Consumed Item %d at %d\n",*(int*)cno, item, out);
        out = (out+1) %n;
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){
    printf("Enter the buffer size: ");
    scanf("%d",&n);
    in = 0;
    out = 0;

    pthread_t prod[5], consum[5];
    pthread_mutex_init(&mutex,NULL);

    //buffer = (int*) malloc(sizeof(int)*n);

    sem_init(&empty, 0, n);
    sem_init(&full , 0, 0);
    
    for(int i=0;i<5;i++){
        pthread_create (&prod[i],NULL, producer, (void*)&num[i]);
    }
    for(int i=0;i<5;i++){
        pthread_create (&consum[i],NULL, consumer, (void*)&num[i]);
    }
    for(int i=0;i<5;i++){
        pthread_join(prod[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(consum[i],NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
