#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int* fibonacci(int n){
    if(n<0) return NULL;
    int* fib = (int *)malloc (sizeof(int)*n);
    fib[0] = 0;
    if(n>0){
        fib[1] = 1;
        int f3;
        for(int i = 2; i<n; i++){
            f3 = fib[i-1]+fib[i-2];
            fib[i] = f3;
        }
    }
    return fib;
}

int* n_primes(int n){
    if(n<0) return NULL;
    int* prime = (int *) malloc(sizeof(int)*n);
    prime[0] = 2;
    int i = 3;
    int k = 1;
    while(k<n){
        int j;
        for( j = 2; j<=i/2; j++){
            if(i%j == 0) break;
        }
        if(!(j<=i/2))
            prime[k++] = i;
        i++;
    }
    return prime;
}

void print_arr(int* arr,int n){
    printf("Process %d of parent %d : ", (int)getpid(), (int)getppid());
    for(int i=0;i<n;i++){
        if(i==n-1)
        printf("%d ",arr[i]);
        else
        printf("%d, ",arr[i]);
    }
    printf("\n");

}

int main(){
    int n;
    pid_t parentid = getpid();
    printf("%d is the main process id\n", getpid());
    printf("Enter the value of n: ");
    scanf("%d",&n);
    int cpid = (int)fork();
    if(cpid == 0 ){
        int* fib_arr = fibonacci(n);
        printf("First %d Fibonacci : ",n);
        print_arr(fib_arr, n);
        exit(0);
    }
    int* primes = n_primes(n);
    printf("First %d Primes : ",n);
    print_arr(primes,n);
    wait(NULL);
    return 0;

 } 
