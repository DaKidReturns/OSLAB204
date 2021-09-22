#ifndef BANKER_UTIL 
#define BANKER_UTIL
int** get_need_mat(int**, int**, int, int);
int** get_mat(int, int, char[]);
int* get_req(int,int);
int* get_avail(int);
void delete_mat(int **,int row);
void print_sequence(int*,int);
void print_matrix(int**, int, int);

int** 
get_need_mat(int** max, int** alloc, int proc, int res){
    int** need = (int**)malloc(sizeof(int*)*proc);
    for (int p = 0; p<proc; p++){
        need[p] = (int*) malloc(sizeof(int)*res);
    }

    for (int i=0;i<proc;i++)
        for(int j = 0; j< proc; j++){
            int c = max[i][j]-alloc[i][j];
            if (c<0){
                delete_mat(need,proc);
                return NULL; // Need Cant be less than 0 if it is then it is an error
            }
            need[i][j] = c;
        }
    return need;
}

void print_avail_vec(int* avail_vec, int len){
    for(int i=0; i<len; i++)
        printf("%d ",avail_vec[i]);
    printf("\n");
}
void print_req_vec(int* req_vec, int res, int proc_num){
    printf("Resource requested by process p%d\n",proc_num);
    for(int i=0;i<res;i++){
        printf("%d ",req_vec[i]);
    }
    printf("\n");
}

int **
get_mat(int procs, int res, char mod_string[]){ //Returns an procs x res matrix with the max demand of each process
    int i;
    int** max_mat = (int**) malloc(sizeof(int*)*procs); //row initilation
    for (i=0;i<procs; i++)
        max_mat[i] = (int*) malloc(sizeof(int)*res); //initilize all the columns
    int j; // control variable for resources

    for (i=0;i<procs; i++){
        for (j=0;j<res;j++){
            printf(mod_string, j+'A',i);
            scanf("%d",&max_mat[i][j]);
        }
        printf("\n");
    }
    return max_mat;
}

int*
get_avail(int res){
    int * avail_vec = (int*) malloc(sizeof(int)*res);
    for (int i =0 ; i<res;i++){
        printf("Enter availablity of resource %c: ",i+'A');
        scanf("%d",avail_vec+i);
    }
    return avail_vec;
}

int*
get_req(int res, int proc_num){
    int* req_vec = (int*) malloc(sizeof(int)*res);
    for(int i=0;i<res;i++){
        printf("Enter the need of resource %c for process P%d: ",i+'A',proc_num);
        scanf("%d",req_vec+i);
    }
    return req_vec;
}

void 
delete_mat(int** mat, int row){
    for (int i=0;i< row; i++){
        free(mat[i]);
    }
    free(mat);
}

void
print_sequence(int* seq, int proc){
    if (seq!=NULL){
        for (int i = 0; i<proc; i++){
            printf("P%d ",seq[i]);
        }
        printf("\n");
    }
}

void print_matrix(int** mat,int row,int col){
    for(int i=0;i<row; i++){
        printf("P%d: ",i);
        for(int j=0;j<col;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}


/*
int** 
get_need_mat(int** max, int** alloc, int proc, int res){
    int** need = (int**)malloc(sizeof(int*)*proc);
    for (int p = 0; p<proc; p++){
        need[p] = (int*) malloc(sizeof(int)*res);
    }

    for (int i=0;i<proc;i++)
        for(int j = 0; j< proc; j++){
            int c = max[i][j]-alloc[i][j];
            if (c<0){
                delete_mat(need,proc);
                return NULL; // Need Cant be less than 0 if it is then it is an error
            }
            need[i][j] = c;
        }
    return need;
}


int **
get_mat(int procs, int res, char mod_string[]){ //Returns an procs x res matrix with the max demand of each process
    int i;
    int** max_mat = (int**) malloc(sizeof(int*)*procs); //row initilation
    for (i=0;i<procs; i++)
        max_mat[i] = (int*) malloc(sizeof(int)*res); //initilize all the columns
    int j; // control variable for resources

    for (i=0;i<procs; i++){
        for (j=0;j<res;j++){
            printf(mod_string, j,i+'a');
            scanf("%d",&max_mat[i][j]);
        }
    }
    return max_mat;
}

int*
get_avail(int res){
    int * avail_vec = (int*) malloc(sizeof(int)*res);
    for (int i =0 ; i<res;i++){
        printf("Enter availablity of resource: R%d",i);
        scanf("%d",avail_vec+i);
    }
}

void 
delete_mat(int** mat, int row){
    for (int i=0;i< row; i++){
        free(mat+i);
    }
    free(mat);
}

void
print_sequence(int* seq, int proc){
    if (seq!=NULL){
        for (int i = 0; i<proc; i++){
            printf("%c ",seq[i]+'A');
        }
        printf("\n");
    }
}
*/
#endif

