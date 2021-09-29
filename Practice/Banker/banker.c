#include<stdio.h>
#include<stdlib.h>

void printmat(int ** mat, int procs, int res){
    for(int i=0; i<procs; i++){
        for(int j=0; j<res; j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }
}

void print_safe_seq(int* safe_seq, int res){
    int i;
    for(i = 0; i<res-1; i++){
        printf("P%d->", safe_seq[i]);
    }
    
    if(res>0){
        printf("P%d\n",safe_seq[i]);
    }
    
}

int comp_res(int *res_vec, int* avail_vec, int res){
    for(int i=0; i<res; i++){
        if(avail_vec[i]< res_vec[i]) return 0;
    }
    return 1;
}

int* get_safe_seq(int** alloc_mat, int** need_mat, int* avail_vec, int procs, int res){
    int *safe_seq = (int* ) malloc(sizeof(int)*procs);
    int r=0;
    int run_p[procs]; for(int i=0; i<procs; i++) run_p[i] = 0;
    int flag = 1;
    int temp[res]; for(int i=0;i<res;i++) temp[i] = avail_vec[i];

    while(r <= procs){
        int i;
        int dflag = 0;
        for(i=0;i<procs;i++){
            //iterate through all the process
            if(!run_p[i]&& comp_res(need_mat[i], temp, res)){
                //Run the process and get the allocated resources
                for(int j = 0; j<res; j++){
                    temp[j] +=alloc_mat[i][j];
                }
                safe_seq[r] = i;
                r++;
                run_p[i] = 1;
                dflag = 1;
            }
        }
        if(!dflag) break;

    }
    if(r==procs)
        return safe_seq;
    else
        return NULL;
}

int main(){
    int proc, res;

    printf("Enter the number of processes: ");
    scanf("%d",&proc);
    printf("Enter the number of resorces: ");
    scanf("%d",&res);

    int ** max_mat  = (int**)malloc(sizeof(int*)*proc);
    int ** alloc_mat  = (int**)malloc(sizeof(int*)*proc);
    int ** need_mat  = (int**)malloc(sizeof(int*)*proc);

    for(int i=0; i<proc; i++){
        max_mat[i] = (int*)malloc(sizeof(int)*res);
        printf("Enter the maximum resource needed for proceess %d: ",i);
        for(int j=0; j<res; j++)
            scanf("%d",&max_mat[i][j]);
    }

    for(int i=0; i<proc; i++){
        alloc_mat[i] = (int*)malloc(sizeof(int)*res);
        need_mat[i] = (int*)malloc(sizeof(int)*res);
        printf("Enter the allocated resource for proceess %d: ",i);
        for(int j=0; j<res; j++){
            scanf("%d",&alloc_mat[i][j]);
            need_mat[i][j] = max_mat[i][j] - alloc_mat[i][j];
        }
    }

    int avail_vec[res];
    printf("Enter the available resource vector: ");
    for(int i=0;i<res; i++)
        scanf("%d",&avail_vec[i]);

    printf("\n\nMAX MATRIX\n");
    printmat(max_mat, proc,res);
    printf("\n\nALLOC MATRIX\n");
    printmat(alloc_mat, proc,res);
    printf("\n\nNEED MATRIX\n");
    printmat(need_mat, proc,res);

    printf("\n\nAvailable Vector\n");
    for(int i=0;i<res; i++)
        printf("%d ",avail_vec[i]);

    printf("\n");


    int* sequence = get_safe_seq(alloc_mat,need_mat, avail_vec,proc,res);
    if(sequence!=NULL){
        printf("Safe Sequence: ");
        print_safe_seq(sequence, proc);
    }
    else{
        printf("System is in unsafe stae\n");
    }

    for(int i=0; i<proc;i++){
        free(max_mat[i]);
        free(alloc_mat[i]);
        free(need_mat[i]);
    }

    free(max_mat);
    free(alloc_mat);
    free(need_mat);

    return 0;
}
