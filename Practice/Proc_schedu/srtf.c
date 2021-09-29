#include<stdlib.h>
#include<limits.h>

#include "shedl_utils.c"

void srtf(struct Proc* procs, int n){
    sort_procs(procs, n);
    print_procs(procs,n);

    int c=0/*keep track of finished process*/, time=0;
    int shortest = INT_MAX/*a high fucking value*/;
    int index = -1/* assume that we have not found our smallest reamainig time process*/;

    // itereate while until all process are completed
    while(c<n){
        for(int i=0;i<n;i++){ // choose the process with the smallest remaining time.
            if(procs[i].rt /*if process is not completed*/ && time >= procs[i].at /*and the process has arrived*/ ){
                if(procs[i].rt < shortest){
                    /*choose i as the process to be executed if remaining time of i is the samllest
                      In case of equat remaining time fifo will be taken as the process are sorted
                      by the arrival time */
                    index = i;
                    shortest = procs[i].rt;
                }  
            }
        }

        if(index == -1){
            // if no process is found
            printf("No process to run at : %dms\n",time);
            time ++;
            continue;
        }
        
        // if a process is found:
        printf("Running process P(%d)\n" ,procs[index].pid);
        procs[index].rt -= 1;
        time +=1;
        if(procs[index].rt == 0) {  // the process has completed
            printf("Process P(%d) completed at : %dms\n",procs[index].pid,time);
            procs[index].tat = time - procs[index].at;
            procs[index].wt  =  procs[index].tat - procs[index].bt;
            shortest = INT_MAX;
            index = -1;
            c++;
        }
    }
}

int main(){
    int n,i;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    struct Proc procs[n];
    for(i =0 ;i<n; i++){
        printf("Enter the arrival time of process %d: ",i);
        scanf("%d",& procs[i].at);
        procs[i].pid = i;
        procs[i].wt = 0;
        procs[i].tat = 0;
    }
    for(i=0; i<n; i++){
        printf("Enter the burst time of process %d: ",i);
        scanf("%d",& procs[i].bt);
        procs[i].rt =  procs[i].bt;
    }

    print_procs(procs,n);
    srtf(procs,n);
    gant_chart(procs,n);

    return 0;
}
