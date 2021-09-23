#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int n;
	printf("Enter the value of N: ");
	scanf("%d", &n);
	printf("\nParent pid (Main process) %d at level 0\n", getpid());
	
	for(int i = 1; i <= n; i++)
		if(fork() == 0) // CHILD 1
			printf("Child pid %d from parent pid %d at level %d\n", getpid(), getppid(), i);
		else{ 
            if(fork() == 0){ // CHILD 2
                printf("Child pid %d from parent pid %d at level %d\n", getpid(), getppid(), i);
            }
                else { // PARENT
                    wait(NULL);
                    break;
                }
        }
    return 0;
}
