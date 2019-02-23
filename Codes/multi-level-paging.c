#include <stdio.h>
#include <stdlib.h>
#DEFINE BASE_ADDRESS(420)

struct PageDirectory
{
      int offset;
      int page_table_id;
};

struct PageTable
{
    // int physical_address;
    // int physical_address_space;
    // int pages;
    // int page_size;
    int offset;
    int page_number;
    // int page_frame_number;
};

struct MainMemory
{
    int frame;
    int page_frame;
};

int main()
{

}
