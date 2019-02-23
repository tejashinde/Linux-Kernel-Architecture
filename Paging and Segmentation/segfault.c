#include <stdio.h>
#include <stdlib.h>
// int main()
// {
//     int number;
//     printf("Enter an integer : ");
//     scanf("%d",&number);
//     printf("Integer is : %d",number);
// }



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

int main(int argc, char const *argv[])
{
        int segments;
        printf("Enter the number of segments\n");
        scanf("%d", &segments);
        struct segtable s[segments];
        for (int i = 0; i < segments; i++)
        {
            int segment_size;
            printf("Enter the segment size of segment %d : ", i + 1);
            scanf("%d", &segment_size);
            struct segtable entry;
            if (i == 0)
            {
                entry.base_address = i;
                entry.size = segment_size;
                s[i] = entry;
            }
            else
            {
                entry.base_address = 1 + s[i - 1].size;
                entry.size = segment_size;
                s[i] = entry;
            }
        }
        printf("Frame\tBase Address\t Size\n");
        for (int i = 0; i < sizeof(s) / sizeof(s[0]); i++)
        {
            printf("%d\t%d\t\t %d\n", i + 1, s[i].base_address, s[i].size);
        }

        printf("Logical Address To Phycical address conversion\n");
        while (1)
        {
            int base_1;
            int size_1;
            printf("Enter base address: ");
            scanf("%d", &base_1);
            printf("Enter offset : ");
            scanf("%d", &size_1);
            if (size_1 > s[base_1].size)
            {
                printf("Segmentation Fault");
                break;
            }
            else
            {
                printf("Phyical address is %d\n", base_1 + size_1);
                continue;
            }
        }
    return 0;
}
