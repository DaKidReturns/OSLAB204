#include<stdio.h>
#include<unistd.h>

int main(){
    printf("A");
    fork();
    return 0;
}
