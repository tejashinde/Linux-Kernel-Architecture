#include <stdlib.h>

struct message_buffer
{
    char message;
    long message_type;
}

void main()
{
    int pid;

    pid = fork();
    printf("PID : %d\n" , pid);
    if(pid > 0)
    {
        printf("Parent waits.");
        sleep(50);
    }
}
