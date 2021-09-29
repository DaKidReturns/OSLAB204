#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

int value;
int mutex, rw_mutex;
int read_c;
int name[] = {0,1,2,3,4,5};

void wait(int * sem){
    while((*sem) ==0);
    (*sem)--;
}
void signal(int * sem){
    while((*sem) ==1);
    (*sem)++;
}

void* reader(void* rnum){
    while(1){
        wait(&mutex);
        read_c++;
        if(read_c == 1)
            wait(&rw_mutex);
        signal(&mutex);

        printf("Reader %d reads %d\n", *(int*)rnum, value);

        wait(&mutex);
        read_c--;
        if(read_c == 0)
            signal(&rw_mutex);
        signal(&mutex);
        sleep(1);
    }
}

void* writer(void* wnum){
    while(1){
        wait(&rw_mutex);
        value = rand();
        printf("Writer %d worte value %d\n", *(int*)wnum, value);
        signal(&rw_mutex);
        sleep(1);
    }
}

int main(){
    read_c = 0;
    pthread_t read[5], writ[5];
    //pthread_mutex_init(&mutex,NULL);
    //pthread_mutex_init(&rw_mutex,NULL);
    mutex = 1;
    rw_mutex = 1;


    for(int i=0;i<5;i++){
        pthread_create(&writ[i],NULL, writer, (void*) &name[i]);
    }
    for(int i=0;i<5;i++){
        pthread_create(&read[i],NULL, reader, (void*) &name[i]);
    }

    for(int i=0;i<5;i++){
        pthread_join(writ[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(read[i],NULL);
    }
    return 0;

}
