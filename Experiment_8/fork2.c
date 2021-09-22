#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main(){
    int n ;
    int i = 0;
    int p = 0;
    int ch = 0;
    printf("Enter the number of process to be created: ");
    scanf("%d", &n);

    for(i =0; i<n ; i++){
        p++;
        if(ch == 0){
            printf("Line %d:  Process id: %d, Parent id: %d \n",p,getpid(),getppid());
            ch = fork();
        }else{
            break;
        }
    }
    wait(NULL);
    return 0;
}
