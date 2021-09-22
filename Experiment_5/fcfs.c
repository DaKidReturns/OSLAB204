#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESS 2

typedef struct {
    int arrival_time;
    int burst_time;
    int p_num;
    int comp;
} proc;

typedef struct{
    proc** list ;
    int size; 
    int cap;
} proc_list;

typedef struct {
    int p_id;
    int tat;
    int wt;
} proc_summ;


proc_list *
/*{{{*/create_process()
{
    proc_list* p_list = (proc_list *) malloc(sizeof(proc_list));
    p_list->size = 0;
    p_list->cap = MAX_PROCESS;

    p_list->list = (proc**)malloc(sizeof(proc)*p_list->cap);

    int RUN=1;
    int i=0;
    int c;

    while(RUN)
    {
        proc *p = (proc*)malloc(sizeof(proc));
        printf("Enter the Arrival time of proc P%d : ",i);   
        scanf("%d",&p->arrival_time);
        printf("Enter the Burst time of proc P%d : ",i);   
        scanf("%d",&p->burst_time);
        p->p_num = i;
        p->comp = 0;

        p_list->list[i] = p;

        i++;
        p_list->size = i;
        
        printf("Is there anymore Processes? (N for no): ");
        getc(stdin);
        c = getc(stdin);
        if(c == 'n' || c == 'N'){
            RUN=0;
            break;
        }

        if(! i < p_list -> cap){
            p_list -> cap = p_list->cap*2;
            p_list->list= (proc**) realloc(p_list->list, sizeof(proc)*p_list->cap);
        }
    }

    return p_list;
}/*}}}*/

void 
/*{{{*/show_process(proc_list *procs)
{
    printf("\n");
    printf("=======================================\n");
    printf("               Processes               \n");
    printf("=======================================\n");
    printf("Process          BT                  AT\n");
     for(unsigned int i=0;i<procs->size; i++){
    printf("P%d               %d                   %d\n", 
            procs->list[i]->p_num,
            procs->list[i]->burst_time,
            procs->list[i]->arrival_time);
     }
    printf("=======================================\n");

}/*}}}*/

void 
/*{{{*/sort ( proc** list, int s) {
    for(int i=0 ; i<s; i++){
        for (int j=0 ;j<=s-i-1 ;j++){
            if(list[j]->arrival_time > list[j+1]->arrival_time){
                proc *temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}/*}}}*/

void
show_result(proc_summ * psum, proc_list *procs)
/*{{{*/{
    if (psum == NULL) return;
    int n = procs->size;
    printf("\n");
    printf("==============================================\n");
    printf("            Excecution  Summary               \n");
    printf("==============================================\n");
    printf("Process      BT       AT     TAT      WT     \n");
    int wt_sum = 0;
    int tat_sum = 0;
    for(unsigned int i=0;i<procs->size; i++){
        printf("P%d           %d        %d      %d       %d     \n", 
            procs->list[i]->p_num,
            procs->list[i]->burst_time,
            procs->list[i]->arrival_time,
            psum[i].tat,
            psum[i].wt);
        wt_sum += psum[i].wt;
        tat_sum += psum[i].tat;

    }
    printf("==============================================\n");
    
    float average_wt = (float)wt_sum / n;
    float average_tat = (float)tat_sum / n;

    printf("\nAverage Turnaround time = %.2f\nAverage Waiting time = %.2f\n",average_tat,average_wt);
}/*}}}*/


proc_summ *
fcfs(proc_list *procs)
/*{{{*/{
    if ( procs->size > 0 ){

        int n = procs->size;
        proc_summ *ps = (proc_summ*) malloc (sizeof (proc_summ)*n);

        int time = 0;

        //Sort the process using their arrival time.
        sort(procs->list, n-1);
        //show_process(procs);

        time = procs -> list[0]->arrival_time;

        for (int i = 0 ; i < n; ){
            if (time >= procs->list[i] -> arrival_time){
                time = time + procs->list[i]->burst_time;
                ps[i].p_id = procs->list[i] -> p_num;
                ps[i].tat = time - procs -> list[i] -> arrival_time;
                ps[i].wt = ps[i].tat - procs -> list[i] -> burst_time;
                i++;
            }
            else{
                time++;
            }
        }

        return ps;
    }
    return NULL;

}/*}}}*/


int
main()
{
    proc_list *s = create_process();
    show_process(s);
    proc_summ *psum = fcfs(s);
    show_result(psum, s);
    return 0;
}
