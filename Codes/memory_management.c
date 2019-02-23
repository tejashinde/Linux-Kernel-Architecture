typedef struct memory_block{
    struct memory_block *next;
    bool isfree;
    size_t size;
    void *memoryAddress;
}MEMORY_BLOCK;


#define BLOCK_SIZE sizeof(MEMORY_BLOCK)

MEMORY_BLOCK *allocateMemBlock(size_t size)
{
    MEMORY_BLOCK *block = (MEMORY_BLOCK*)sbrk(0);
    void *memadr = (void*)sbrk(0);
    void *allocate_mem = (void*)sbrk(BLOCK_SIZE + size);

    if(allocate_mem == (void*)-1){
        return NULL;
    }else{
        block->next = NULL;
        block->isfree = false;
        block->size = size;
        block->memoryAddress = memadr+BLOCK_SIZE;
        return block;
    }
}

void freeMemBlock(MEMORY_BLOCK **head)
{
    if(*head == NULL){}
    else{
        (*head)->isfree = true;
    }
}

#include<stdio.h>
#include<stdbool.h>

typedef struct __s_block{
    struct __s_block *next;
    bool isfree;
    size_t size;
    void *memoryAddress;
}MEMORY_BLOCK;

#define BLOCK_SIZE sizeof(MEMORY_BLOCK)

MEMORY_BLOCK *allocateMemBlock(size_t size)
{
    MEMORY_BLOCK *block = (MEMORY_BLOCK*)sbrk(0);
    void *memadr = (void*)sbrk(0);
    void *allocate_mem = (void*)sbrk(BLOCK_SIZE + size);

    if(allocate_mem == (void*)-1){
        return NULL;
    }else{
        block->next = NULL;
        block->isfree = false;
        block->size = size;
        block->memoryAddress = memadr+BLOCK_SIZE;
        return block;
    }
}

//allocate next memory block
void allocateNextMemBlock(size_t size, MEMORY_BLOCK **head)
{
    MEMORY_BLOCK *current = *head;
    void *allocate_mem = NULL;
    void *memadr = (void*)sbrk(0);

    if(current==NULL){
        *head = allocateMemBlock(size);
    }else{
        while(current->next != NULL){
            current = current->next;
        }
        MEMORY_BLOCK *newblock = sbrk(0);

        allocate_mem = (void*)sbrk(BLOCK_SIZE + size);
        if(allocate_mem == (void*) - 1){ }
        else{
            newblock->next = NULL;
            newblock->isfree = false;
            newblock->size = size;
            newblock->memoryAddress = memadr+BLOCK_SIZE;
            current->next = newblock;
      }
    }
}

void freeMemBlock(MEMORY_BLOCK **head)
{
    if(*head == NULL){}
    else{
        (*head)->isfree = true;
    }
}

void printMemBlocks(MEMORY_BLOCK *current)
{
    while(current != NULL){
        printf("isfree = %d, size = %d, memoryAddress = %p, current = %p, next-node = %p\n",
                current->isfree, current->size, current->memoryAddress, current, current->next);
        current = current->next;
    }
}

int main()
{
    MEMORY_BLOCK *sMemBlock = NULL;
    allocateNextMemBlock(10,&sMemBlock);
    allocateNextMemBlock(35,&sMemBlock);
    allocateNextMemBlock(62,&sMemBlock);
    printMemBlocks(sMemBlock);

    printf("\nAfter freeing second node\n");
    freeMemBlock(&(sMemBlock->next));
    printMemBlocks(sMemBlock);

    return 0;
}

void allocate_allMemory(MEMORY_BLOCK **blockHead,_PROCINTNODE *procinthead)
{
    _PROCINTNODE *current = procinthead;

    printf("\n\t\t[ All Memory allocated to processes]\n");
    printf("-------------------------------------------------------------------------");
    printf("\n|  Process   |   Start Address   |   End Address    |      Size       |\n");
    printf("-------------------------------------------------------------------------\n");

    while(current != NULL){
        void *start_address = sbrk(0) + 1;
        allocateNextMemBlock(current->size + 1, &(*blockHead));
        void *end_address = sbrk(0);
        float size_kb = (current->size)/1024.0;

        printf("|     P%d     |     %p     |    %p     |     %.3fKB     |\n",
                current->process, start_address, end_address, size_kb);

        current = current->next;
    }
    printf("-------------------------------------------------------------------------\n");
    printf("\n\n");
    printf("\n\tCurrent brk pointer is here (sbrk(0)) = %p\n", sbrk(0));

    //release the allocated memory
    printf("\n\t\t\t[ Memory released ]\n\n");
    MEMORY_BLOCK *lastblock, *blockcurrent = *blockHead;
    while(blockcurrent != NULL){
        blockcurrent->isfree = true;
        if(blockcurrent->next == NULL){
                lastblock = blockcurrent;
        }
        blockcurrent = blockcurrent->next;
    }

    blockcurrent = lastblock;
    int proc_length = _countPROCINTNodes(procinthead);

    while(blockcurrent->prev != NULL){
        if(blockcurrent->isfree){
            (blockcurrent->prev)->next = NULL;
            if(blockcurrent->prev == NULL){
                sbrk(0-(BLOCK_SIZE + blockcurrent->size + 1));
                printf("\nProcess P%d : sbrk(0) is %p\n", proc_length, sbrk(0));
            }
            sbrk(0-(BLOCK_SIZE + blockcurrent->size + 1));
            printf("\nProcess P%d : sbrk(0) is %p\n", proc_length, sbrk(0));
        }
        blockcurrent = blockcurrent->prev;
        proc_length--;
    }

    sbrk(0 - (BLOCK_SIZE + blockcurrent->size + 1));
    printf("\nProcess P%d : sbrk(0) is %p\n",proc_length,sbrk(0));
    *blockHead=NULL;
}
