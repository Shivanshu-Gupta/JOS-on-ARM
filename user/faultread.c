// buggy program - faults with a read from location zero

#include <lib/stdio.h>

void _start()
{
        printf("I read %08x from location 0xf0100000!\n", *(unsigned*)0xf0100000);
        exit(0);
}

