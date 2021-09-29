#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int n[] = {0,1,2,3,4};
int chopsticks[5] = {1,1,1,1,1};

void wait(int *n){
    while((*n)==0);
    (*n) -- ;
}

void signal(int * n){
    while((*n)==1);
    (*n) ++ ;
}

void eat(int n){
    printf("Philosopher %d is eating his food\n",n);
}

void* philostuff(void* num){
    int ph = * (int*)num;
    do{

        wait(&chopsticks[ph]);
        printf("Philosopher %d picked up Left chopstick\n",ph);

        wait(&chopsticks[(ph+1)%5]);
        printf("Philosopher %d picked up Right chopstick\n",ph);

        eat(ph);

        printf("Philosopher %d has finished eating\n",ph);
        signal(&chopsticks[(ph+1)%5]);
        signal(&chopsticks[ph]);


        printf("Philosopher %d begins to think\n\n", ph);

        sleep(1);
    }while(1);

}

int main(){
    pthread_t philos[5];

    for(int i=0; i<5; i++){
        pthread_create(&philos[i],NULL, philostuff, (void*)& n[i]);
        //sleep(0.2);
    }

    for(int i=0; i< 5 ; i++){
        pthread_join(philos[i],NULL);
    }

    return 0;
}
