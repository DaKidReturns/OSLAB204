#include<stdlib.h>
#include<limits.h>

#include "shedl_utils.c"


void fcfs(struct Proc* process, int n){
    int time = 0, i = 0,completion_time;
    sort_procs(process, n);
    print_procs(process,n);
    while(i < n){
        if(process[i].at <= time){
            //run process
            printf("Running process %d \n", process[i].pid);
            completion_time = process[i].bt + time;
            process[i].tat = completion_time - process[i].at;
            process[i].wt  = process[i].tat - process[i].bt;
            time += process[i].bt;
            i++;
        }
        else{
            printf("Arrival time of process %d is %d which is greater than current time %d\n",process[i].pid, process[i].at,time);
            time++;
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
    fcfs(procs,n);
    gant_chart(procs,n);

    return 0;
}
