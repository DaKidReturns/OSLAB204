#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#include "banker_util.c"

int* get_safe_sequence(int**,int**,int**, int*,int,int);
int  compare_vects(int*, int*,int);
void run_proc(int*,int*,int);
int modify_mat( int**, int**, int*, int*, int,int, int);

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
    int** need = get_need_mat(max_mat, alloc_mat, p, r);
    if (need == NULL){
        printf("\nERROR in calcualating need matrix\n");
        exit(1);
    }
    printf("\n\nNEED MATRIX\n");
    print_matrix(need, p,r);

    int *safe_seq = get_safe_sequence(max_mat,alloc_mat,need,avail_vec,p,r);

    if (safe_seq != NULL){
        printf("Safe sequence is: ");
        print_sequence(safe_seq,p);
        free(safe_seq);

        int cho = getc(stdin);
        printf("\nRun Resouce request algorithm? (Y/N):");
        //scanf("%d\n",&cho);
        cho = getc(stdin);
        if(cho == 'y'||cho == 'Y'){
            int p_num;
            printf("Enter the process number that sends the request [0-%d]: ",p-1);
            scanf("%d",&p_num);
            int* request = get_req(r,p_num);
            printf("\nRequest Vector: ");
            print_req_vec(request,r,p_num);
            int flag = modify_mat(alloc_mat,need,avail_vec,request,p,r,p_num);
            if(flag){
                //printf("in the flag");
                safe_seq = get_safe_sequence(max_mat, alloc_mat,need, avail_vec,p,r);
                if(safe_seq != NULL){
                    printf("\nThe System is in safe state\nSafe sequence: ");
                    print_sequence(safe_seq,p);
                }
                else
                    printf("It is in an unsafe state.\n");

            } else{
                exit(1);
            }

        }
    }
    else{
        printf("It is in an unsafe state.\n");
    }
    delete_mat(need,p);
    delete_mat(max_mat,p);
    delete_mat(alloc_mat,p);
    return 0;
}

int
modify_mat(int** alloc_mat, int** need, int* avail_vec, int* req_vec, int proc,int res, int proc_num){
    int i;
    int flag = 0; // Used times
    //Check if Request <= Need
    for(i=0; i<res; i++){
        if(req_vec[i] > need[proc_num][i]){
            flag=1;
            break;
        }
    }
    if(flag){
        printf("Process exceeds maximum claim\n");
        return 0;
    }
    
    //Check if Avail<=Need
    for(i=0; i<res; i++){
        if(req_vec[i] > avail_vec[i]){
            flag=1;
            break;
        }
    }
    if(flag){
        printf("No free resource to satisfy request\n");
        return 0;
    }

    for(i=0; i<res; i++){
        avail_vec[i]           =  avail_vec[i] - req_vec[i];
        alloc_mat[proc_num][i] =  alloc_mat[proc_num][i] + req_vec[i];
        need [proc_num][i]     =  need[proc_num][i] - req_vec[i];
    }
    printf("\nAvailable resource vector: ");
    print_avail_vec(avail_vec, res);
    printf("\nRESOURCE ALLOCATION MATRIX\n");
    print_matrix(alloc_mat,proc,res);

    printf("\n\nNEED RESOURCE MATRIX\n");
    print_matrix(need,proc,res);
    return 1;
}

int* 
get_safe_sequence(int ** max, int** alloc, int**need, int* avail,int procs, int res){
    int r = 0; // keeps track of number of process completed //do r++, then safe_seq[r-1] = proc
    int* safe_seq = (int*) malloc(sizeof(int)*procs);
    int temp_avail[res];
    for(int i=0;i<res;i++){
        temp_avail[i] = avail[i];
    }

    int deadlock = 1; // Deadlock flag, if in a single iteration through the process list, no process is run the system is in deadlock

    int comp_vec[procs]; // keeps track of completed process to avoid O(n) searching later on
    for(int i=0;i<procs;i++){
        comp_vec[i] = 0;
    }

    while(r<procs){ //while there are process remaining
        deadlock = 1;
        for(int i = 0; i < procs; i++){ // Loop over all the processes
            if ( !comp_vec[i] && compare_vects(need[i],temp_avail,res)){  //Takes O(n) time
                // Process can be run
                run_proc(alloc[i], temp_avail,res);
                comp_vec[i] = 1;
                deadlock = 0;
                //printf("Running Process %c\n",i+'A');
                safe_seq[r] = i;
                r++;
            }
        }
        if (deadlock){
            return NULL;
        }
    }
    return safe_seq;
}

void run_proc(int* alloc_vec, int* avail, int res){
    for (int i=0; i<res; i++){
        avail[i]=avail[i]+alloc_vec[i];
    }
}
int
compare_vects(int* need, int* avail,int res){
    for(int i=0; i<res; i++){
        if (need[i]>avail[i])
            return 0;
    }
    return 1;
}
