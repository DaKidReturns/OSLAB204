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


proc_list *
create_process()
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
        p->p_num = i+1;

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
}

void 
show_process(proc_list *procs)
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
    printf("%d\n",procs->size);

}

//Comparison function for qsort, for sorting proc 
int 
comp_proc(const void *a, const void *b)
{
    proc *pa = *(proc**) a;
    proc *pb = *(proc**) b;
    
    printf("compred %d and %d \n",pa->arrival_time,pb->arrival_time);

    if ( pa->arrival_time < pb->arrival_time ) return -1;
    if ( pa->arrival_time > pb->arrival_time ) return 1;
    return 0;
}

void
fcfs(proc_list *procs)
{
    if ( procs->size > 0 ){
        printf("In the if \n");
        //Sort the process using their arrival time.
        proc** list = (procs->list);
        qsort(list[0], (procs->size), sizeof(proc),comp_proc);
        
        show_process(procs);

        //Create a list with process names

        //n = procs->size;

        //time_delay = procs -> list[0] -> arrival_time;

        /*for ( i=0 ; i<n ; i++ ){
            
        }*/
    }

}

//void free_process

void 
main()
{
    proc_list *s = create_process();
    show_process(s);
    fcfs(s);

    //fcfs();
}
