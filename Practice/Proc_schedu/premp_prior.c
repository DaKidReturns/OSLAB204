#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#include"shedl_utils.c"

void premp_prior(struct Proc* procs, int n){
    int time = 0, c = 0;

    int max_pr = INT_MIN;
    int index = -1;
    while(c<n){
        for(int i=0;i<n;i++){
            if(procs[i].rt && procs[i].at <= time){
                if(procs[i].pr > max_pr){
                    max_pr = procs[i].pr;
                    index = i;
                }
            }
        }
        if(index == -1){
            time++;
            continue;
        }

        procs[index].rt -=1;
        time++;
        if(procs[index].rt == 0){
            //Process is completed
            procs[index].tat = time - procs[index].at;
            procs[index].wt = procs[index].tat - procs[index].bt;
            max_pr = INT_MIN;
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
    for(i=0; i<n; i++){
        printf("Enter the priority of the process %d: ", i);
        scanf("%d", & procs[i].pr);
    }

    print_procs(procs,n);
    premp_prior(procs,n);
    gant_chart(procs,n);
    return 0;
}
