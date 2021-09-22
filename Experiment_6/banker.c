#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#include "banker_util.c"

int* get_safe_sequence(int**,int**, int*,int,int);
int  compare_need_alloc(int*, int*,int);
void run_proc(int*,int*,int);

int
main(){
    int p;
    int r;
    printf("Enter the number of processes: ");
    scanf("%d",&p);

    printf("Enter the number of resources: ");
    scanf("%d",&r);

    printf("============== MAX RESOURCE MATRIX ============\n");
    int ** max_mat = get_mat(p,r,"Enter the maximum resource %c needed for process P%d: ");

    printf("============== RESOURCE ALLOCATION MATRIX ============\n");
    int ** alloc_mat = get_mat(p,r,"Enter the allocated resource %c for process P%d: ");

    printf("\n\nMAX RESOURCE MATRIX\n");
    print_matrix(max_mat,p,r);

    printf("\nRESOURCE ALLOCATION MATRIX\n");
    print_matrix(alloc_mat,p,r);

    printf("\n");
    int *avail_vec = get_avail(r);

    int *safe_seq = get_safe_sequence(max_mat,alloc_mat,avail_vec,p,r);

    if (safe_seq != NULL){
        printf("Safe sequence is: ");
        print_sequence(safe_seq,p);
        free(safe_seq);
    }
    else{
        printf("It is in an unsafe state.\n");
    }
    delete_mat(max_mat,p);
    delete_mat(alloc_mat,p);
    return 0;
}

int* 
get_safe_sequence(int ** max, int** alloc, int* avail,int procs, int res){
    int r = 0; // keeps track of number of process completed //do r++, then safe_seq[r-1] = proc
    int* safe_seq = (int*) malloc(sizeof(int)*procs);
    int** need = get_need_mat(max, alloc, procs, res);

    if (need == NULL){
        printf("\nERROR in calcualating need matrix\n");
        exit(1);
    }
    printf("\n\nNEED MATRIX\n");
    print_matrix(need, procs,res);
    int deadlock = 1; // Deadlock flag, if in a single iteration through the process list, no process is run the system is in deadlock

    int comp_vec[procs]; // keeps track of completed process to avoid O(n) searching later on
    for(int i=0;i<procs;i++){
        comp_vec[i] = 0;
    }

    while(r<procs){ //while there are process remaining
        deadlock = 1;
        for(int i = 0; i < procs; i++){ // Loop over all the processes
            if ( compare_need_alloc(need[i],avail,res) && !comp_vec[i] ){  //Takes O(n) time
                // Process can be run
                run_proc(max[i], avail,res);
                comp_vec[i] = 1;
                deadlock = 0;
                //printf("Running Process %c\n",i+'A');
                r++;
                safe_seq[r-1] = i;
            }
        }
        if (deadlock){
            return NULL;
        }
    }
    return safe_seq;
}

void run_proc(int* max, int* avail, int res){
    for (int i=0; i<res; i++){
        avail[i]+=max[i];
    }
}
int
compare_need_alloc(int* need, int* avail,int res){
    for(int i=0; i<res; i++){
        if (need[i]>avail[i])
            return 0;
    }
    return 1;
}
