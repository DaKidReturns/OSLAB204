
#include<stdlib.h>
#include<limits.h>

#include "shedl_utils.c"
void sjfs(struct Proc* procs, int n){
    int i, time=0,completion_time;
    int comp [n]; for(i=0;i<n;i++) comp[i] = 0;
    sort_procs(procs, n);
    print_procs(procs, n);
    for(i = 0; i<n;){
        // select the process with the minimum burst time
        int sj = -1;
        int shortest = INT_MAX;

        for(int j=0; j<n;j++){
            if(!comp[j]&& procs[j].at <= time){
                if(procs[j].bt < shortest){
                    sj = j;
                    shortest = procs[j].bt;
                }
            }
        }
        if (sj == -1){
                printf("No process running at time: %d\n",time);
                time++;
        }
         
        else{
            //printf("P%d is the shortest\n",procs[j].pid);
            comp[sj] = 1;
            completion_time = procs[sj].bt + time;
            printf("Running procs %d || Completion time: %d \n", procs[sj].pid,completion_time);
            procs[sj].tat = completion_time - procs[sj].at;
            procs[sj].wt  = procs[sj].tat - procs[sj].bt;
            time += procs[sj].bt;
            i++;
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
    //sjfs(procs,n);
    gant_chart(procs, n);
    
    return 0;
}
