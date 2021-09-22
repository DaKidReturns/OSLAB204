#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESS 2

typedef struct {
    int arrival_time;
    int burst_time;
    int p_num;
    int pr;
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
        printf("Enter the Priority of proc P%d : ",i);   
        scanf("%d",&p->pr);
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
    printf("========================================\n");
    printf("               Processes                \n");
    printf("========================================\n");
    printf("Process        BT        AT      Prioriy\n");
     for(unsigned int i=0;i<procs->size; i++){
    printf("P%d            %d       %d           %d\n", 
            procs->list[i]->p_num,
            procs->list[i]->burst_time,
            procs->list[i]->arrival_time,
            procs->list[i]->pr);
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

int
get_process(proc_list *procs, int time)
/*{{{*/{
    int n = procs -> size;
    proc **list = procs -> list; 

    int i=0;
    int smallest_pos = -1;
    while( i<n ){
        if(list[i] -> comp == 0 && list[i] -> arrival_time <= time)
            smallest_pos = i;
        i++;
    }

    if (smallest_pos == -1 ){
        printf("No Process to be excecuted at time %d\n", time);
        return -1;
    }

    for ( i=0; i < n; i++){

        if( time >= list[i] -> arrival_time && list[i]->comp != 1){
            if (smallest_pos >= 0 && list[i] -> pr < list[smallest_pos] -> pr){
                smallest_pos = i;
            }
        }
    }
    
    return smallest_pos;
}/*}}}*/

void
show_result(proc_summ * psum, proc_list *procs)
/*{{{*/{
    int n = procs->size;
    printf("\n");
    printf("=======================================================\n");
    printf("                   Processes  Summary                  \n");
    printf("=======================================================\n");
    printf("Process      BT       AT      Prio.    TAT      WT     \n");
    int wt_sum = 0;
    int tat_sum = 0;
    for(unsigned int i=0;i<procs->size; i++){

        int pos = procs->list[i]->p_num;
    printf("P%d           %d         %d      %d        %d        %d  \n", 
            procs->list[i]->p_num,
            procs->list[i]->burst_time,
            procs->list[i]->arrival_time,
            procs->list[i]->pr,
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
priority(proc_list *procs)
/*{{{*/{
    if ( procs->size > 0 ){

        int n = procs->size;
        proc_summ *ps = (proc_summ*) malloc (sizeof (proc_summ)*n);

        int time = 0;

        //Sort the process using their arrival time.
        sort_at(procs->list, n-1);
        //show_process(procs);

        //time = procs -> list[get_process(procs,time)] -> arrival_time;

        for (int i = 0 ; i < n; ){
            int p_index = get_process(procs, time);
            if( p_index != -1 ){
                printf("Exccuting process..... %d\n",procs->list[p_index] -> p_num);

                int pos = procs->list[p_index]-> p_num;

                time += procs->list[p_index]->burst_time;

                ps[pos].p_id = pos;
                ps[pos].tat = time - procs -> list[p_index] -> arrival_time;
                ps[pos].wt = ps[pos].tat - procs -> list[p_index] -> burst_time;

                procs -> list[p_index] -> comp = 1;
                i++;
            }
            else{
                time++;
                if(time>1024){
                    printf("Time Limit Exceeded\n");
                    return NULL;
                }
            }
            
        }

        return ps;
    }
    return NULL;

}/*}}}*/


void 
main()
{
    proc_list *s = create_process();
    show_process(s);
    proc_summ *psum = priority(s);
    show_result(psum, s);
}
