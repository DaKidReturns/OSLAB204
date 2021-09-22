#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESS 10

typedef struct {
    int arrival_time;
    int burst_time;
    int rem_time;
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
        printf("Enter the Arrival time of process P%d : ",i);   
        scanf("%d",&p->arrival_time);
        printf("Enter the Burst time of proc P%d : ",i);   
        scanf("%d",&p->burst_time);
        p->rem_time = p->burst_time;
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
sort_at ( proc** list, int s) 
/*{{{*/{
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
    if (psum == NULL){
        printf("Process summary cant be null ERROR!!!!!\n");
        return;
    }

    int n = procs->size;
    printf("\n");
    printf("==============================================\n");
    printf("            Processes  Summary                \n");
    printf("==============================================\n");
    printf("Process      BT       AT     TAT      WT     \n");
    int wt_sum = 0;
    int tat_sum = 0;
    for(unsigned int i=0;i<procs->size; i++){

        int pos = procs->list[i]->p_num;
        printf("P%d           %d        %d      %d       %d     \n", 
            procs->list[i]->p_num,
            procs->list[i]->burst_time,
            procs->list[i]->arrival_time,
            psum[pos].tat,
            psum[pos].wt);
        wt_sum += psum[pos].wt;
        tat_sum += psum[pos].tat;

    }
    printf("==============================================\n");
    
    float average_wt = (float)wt_sum / n;
    float average_tat = (float)tat_sum / n;

    printf("\nAverage Turnaround time = %.2f\nAverage Waiting time = %.2f\n",average_tat,average_wt);
}/*}}}*/


proc_summ *
round_robin(proc_list *procs, int time_q)
/*{{{*/{
    if ( procs->size > 0 ){

        int n = procs->size;
        int time = 0;        // Time in ms
        int proc_comp = 0;  // Number of process completed

        // Stores the summary of all the process.
        proc_summ *ps = (proc_summ*) malloc (sizeof (proc_summ)*n);

        //Sort the process using their arrival time.
        sort_at(procs->list, n-1);

        while ( proc_comp < n ) {
            //Execute this loop until all the process is completed
            
            int idle = 1;
            //Update the ready queue, ie, add any process that is not completed.
            for( int i =0 ; i< n; i++){
                proc *p = procs -> list[i];
                if ( p -> comp != 1 && time >= p-> arrival_time ){
                    // add the process to the ready queue
                    if (idle) idle = 0;
                    int ex_time = p->rem_time > time_q? time_q : p->rem_time ;
                    int index = p->p_num;
                    printf("Executing Process ... P%d for %dms\n", index, ex_time);

                    time += ex_time;
                    p->rem_time -= ex_time;
                    if (p -> rem_time == 0){
                        p->comp = 1;
                        ps[ index ] . tat = time - p -> arrival_time;
                        ps[ index ] . wt = ps[ index ] . tat - p-> burst_time;
                        proc_comp += 1;
                    }
                }
            }
            if (idle){
                time++;
            }

            if(time > 1024){
                printf("Time Limit exceeded");
                return NULL;
            }
            // Execute the process in the ready queue
        }
        return ps;
    }
    return NULL;

}/*}}}*/


void 
main()
{
    proc_list *s = create_process();
    printf("Enter the time Quantum for round robin: ");
    int tq;
    scanf("%d", &tq);
    show_process(s);
    proc_summ *psum = round_robin(s,tq);
    show_result(psum, s);
}
