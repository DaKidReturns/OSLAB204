#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int in_frame(int* frame, int fr, int p){
    int i;
    for(i=0; i<fr; i++){
        if(frame[i] == p)
            return i;
    }
    return -1;
}

void print_pf(int* frame, int fr){
    for(int i=0;i<fr;i++){
        printf("%d ",frame[i]);
    }

    printf("\n");
}

int lifo (int* page_str, int n, int fr){
    int fl = 0,page_fault = 0, i,frame[fr];  for(int i=0;i<fr; i++) frame[i] = -1;
    for(i=0;i<n; i++){
        if(fl<fr){
            if(in_frame(frame,fr, page_str[i])==-1){
                frame[fl] = page_str[i];
                page_fault ++;
                fl++;
                print_pf(frame, fl);
            } 
        }else{
            if(in_frame(frame,fr, page_str[i])==-1){
                frame[fr-1] = page_str[i];
                page_fault ++;
                print_pf(frame, fr);
            }
        }
    }
    return page_fault;
}

int optimal(int* page_str, int n, int fr){
    int fl=0, page_fault = 0, i, frame[fr]; for(int i=0;i<fr; i++)frame[i] = -1;

    for(i=0;i<n;i++){
        // Loops over page string
        if(fl<fr){ 
            if(in_frame(frame,fr, page_str[i]) == -1){
                frame[fl] = page_str[i];
                page_fault ++;
                fl++;
                print_pf(frame, fl);
            }
        }

        else{
            if(in_frame(frame, fr, page_str[i]) == -1){
                //page is not in the page frame.

                int temp[n] ; for(int k = 0; k<fr; k++) temp[k] = INT_MAX;
                int pos;
                for(int j= i+1; j<n; j++){
                    pos = in_frame(frame, fr, page_str[j]);
                    if(pos != -1 && temp[pos] == INT_MAX){
                        temp[pos] = j; 
                    }
                }
                // find the pos with the greatest index value
                int max = temp[0];
                pos = 0;
                for(int j=0; j < fr; j++){
                    if(max < temp[j]){
                        pos = j;
                        max = temp[j];
                    }
                }
                // page fault happes at index j
                frame[pos] = page_str[i];
                page_fault++;
                print_pf(frame, fl);
            }
        }
    }
    return page_fault;
}

int main(){
    int n,fr;
    printf("Enter the page string size: ");
    scanf("%d",&n);
    int page_string[n];
    printf("Enter the page string: ");
    for(int i = 0; i<n; i++){
        scanf("%d", &page_string[i]);
    }
    printf("Enter Page frame : ");
    scanf("%d",&fr);

    int page_fault = optimal(page_string, n,fr);
    printf("Number of page fault: %d\n", page_fault);

    return 0;
}
