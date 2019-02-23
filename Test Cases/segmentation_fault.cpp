#include <stdio.h>
#include <stdlib.h>

struct pagetabe
{
    int frame_number;
    int offest;
};

struct segtable
{
    int base_address;
    int size;
};
struct MainMemory{
    int data;
    int key;
    struct MainMemory *next;
};
/* Structure for Swap Space containing data element to store the process, key to store the process id of the swapped process and a self referential pointer to oint the next process in the Swap space*/
struct SwapSpace{
    int data;
    int key;
    struct SwapSpace *next;
};
/* Initialization of two pointers of the main memory as well as  */
struct MainMemory *start_m = NULL;
struct SwapSpace *start_s = NULL;

void create_process(int p,int k){
    struct MainMemory *new_Process,*temp;
    new_Process = (struct MainMemory*) malloc(sizeof(struct MainMemory));
    if(start_m == NULL){
        start_m = new_Process;
        start_m->data = p;
        start_m->key = k;
        start_m->next = NULL;
    }
    else{
        temp = start_m;
        while(temp->next != NULL){
            temp = temp->next;
        }
        new_Process->data = p;
        new_Process->key = k;
        new_Process->next = NULL;
        temp->next = new_Process;
        temp = new_Process;
    }
}


void remove_process(){
    struct MainMemory *rm_process;
    struct SwapSpace *swap_process;
    swap_process = (struct SwapSpace*) malloc(sizeof(struct SwapSpace));
    if(start_m == NULL){
        printf("The memory has no prosess\n");
        return;
    }
        rm_process = start_m;
    rm_process->data = start_m->data;
    rm_process->key = start_m->key;
    start_m = start_m->next;
    printf("%d sized process is moved to swap space\n",rm_process->data);
    swap_process->data = rm_process->data;
    swap_process->key = rm_process->key;
    swap_process->next = start_s;
    start_s = swap_process;
    free(rm_process);
    return;
}

void print_memory_stat(){
    int counter=1;
    struct MainMemory *process_m;
    printf("Main Memory\n");
    printf("Process_id\tSize\n");
    process_m = start_m;
    while(process_m != NULL){
        printf("%d\t%d\n",process_m->key,process_m->data);
        process_m = process_m->next;
    }
    counter = 1;
    struct SwapSpace *process_s;
    printf("Swap Space\n");
    printf("Process_id\tSize\n");
    process_s = start_s;
    while(process_s != NULL){
        printf("%d\t%d\n",process_s->key,process_s->data);
        process_s = process_s->next;
    }
    return;
}

void search(int obj){
    struct MainMemory *trav_m;
    int flag = 0;
    if(start_m == NULL){
        printf("The memory has no prosess\n");
        return;
    }
    trav_m = start_m;
    while(trav_m  != NULL){
        if(trav_m->key == obj){
            printf("Process Found in main memory\n");
            flag = 1;
            break;
        }
        else{
            trav_m = trav_m -> next;
        }
    }
    if (flag == 1){
        return;
    }
    else{
        printf("Page Fault has occured in Main Memory. Now searching in swap space\n");
        struct SwapSpace *trav_s;
        if(start_s == NULL){
            printf("The swap space has no prosess\n");
        }
        trav_s = start_s;
        while(trav_s != NULL){
            if(trav_s->key == obj){
                printf("Process Found in swap space\n");
                flag = 1;
            }
            else{
                trav_s = trav_s->next;
            }
        }
        if(flag == 0){
            return;
        }
        else{
            printf("Page fault has oddured in Swap Space");
        }
    }
}
int main(int argc, char const *argv[])
{
    {
          int choice, total=0,size = 8,id;
    char choiceN;
    while (1){
        printf("Enter your choice of action\n1. Create Process\n2. Search for a Process in Main Memory\n3. Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                total = total + size;
                if(total >= 32){
                    remove_process();
                    total = total - size;
                }
                printf("Put process key\n");
                scanf("%d",&id);
                create_process(size,id);
                break;
            case 2:
                printf("Put process key to be searched in the memory \n");
                scanf("%d",&id);
                search(id);
                break;
            case 3:
                exit(0);
            default :
                break;
        }
    }
    }
    return 0;
}
