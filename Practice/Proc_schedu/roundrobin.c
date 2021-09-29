#include<stdlib.h>
#include<limits.h>

#include "shedl_utils.c"

void round_robin(struct Proc* procs, int n, int tq){
    int i = 0, time = 0, p = 0,c=0,idle;
    int comp[n]; for(int j =0;j<n;j++) comp[j] = 0;
    sort_procs(procs,n);
    print_procs(procs, n);
    time += procs[i].at;
    while(c<n){
        idle = 1;
        for(i=0; i<n; i++){
            //iterate thorugh all the process
            if(!comp[i] && procs[i].at <= time){
                // run the process
                idle=0;
                if(procs[i].rt <= tq){
                    // If the process can be completed in the current time quantum
                    printf("Running process P%d ... for %dms\n",procs[i].pid, procs[i].rt);
                    procs[i].tat = procs[i].rt + time - procs[i].at;
                    procs[i].wt = procs[i].tat - procs[i].bt;
                    time += procs[i].rt;
                    procs[i].rt = 0;
                    comp[i] = 1;
                    c++;
                }
                else{
                    // the process cant be completed in the current time quatum
                    printf("Running process P%d ... for %dms\n",procs[i].pid,tq);
                    procs[i].rt -= tq;
                    time += tq;
                }
            }
        }
        if (idle){
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
    int tq; printf("Enter time quanta for rr: "); scanf("%d", &tq);
    round_robin(procs,n,tq);
    
    gant_chart(procs,n);

    return 0;
}
