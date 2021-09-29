#include<stdio.h>

struct Proc{
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int rt ;
    int pr;
}temp;

void sort_procs(struct Proc* proc, int n){
    for(int i = 0 ; i<n-1; i++){
        for(int j =0 ; j < n-i-1; j++){
            if(proc[j].at>proc[j+1].at){
                temp = proc[j];
                proc[j] = proc[j+1];
                proc[j+1] = temp;
            }
        }
    }
}

void gant_chart(struct Proc* procs, int n){
    char printstr[] = "%-10s|%-15s|%-15s|%-15s|%-15s|%-15s\n";
    char itemprintstr[] = "%-10d|%-15d|%-15d|%-15d|%-15d|%-15d\n";
    printf(printstr,"Process","Arrival time","Priority","Burst time","TAT", "Wating time");
    for(int i=0;i<n;i++){
        printf(itemprintstr,procs[i].pid,procs[i].at,procs[i].pr,procs[i].bt,procs[i].tat,procs[i].wt);

    }
}

void print_procs(struct Proc* procs, int n){
    char str[] = "|------";
    char str1[10];
    printf("\n");
    for(int i=0;i<n;i++) printf("%s",str);printf("|\n");
    for(int i = 0; i<n; i++){
        sprintf(str1,"%s%d%s","P(",procs[i].pid,")");
        printf("|%6s",str1);
        //printf("|%6d",procs[i].at);
    }printf("|\n");
    for(int i=0;i<n;i++) printf("%s",str);printf("|\n");

}
