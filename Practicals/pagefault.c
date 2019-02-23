#include <stdio.h>
#include <stdlib.h>

main()
{
    int frames_quant,
        pages_quant,
        time[10] ,
        counter = 0 ,
        nFlag ,
        mFlag ,
        iterator ,
        position ,
        faults = 0 ,
        *frames ,
        *pages;

    printf("Enter the quantity/number of frames : ");
    scanf("%d" , &frames_quant);
    frames = (int *) malloc (frames_quant * sizeof(int));

    printf("Enter the quantity/number of pages : ");
    scanf("%d" , &pages_quant);
    pages_quant = (int *) malloc (pages_quant * sizeof(int))

}
