#include <stdint.h>
#include <stdio.h>

void print_bin(uint16_t num_bin)
{
    unsigned i;
    for (i = 1 << 15; i > 0; i = i / 2)
    {
        (num_bin & i)? printf("0"): printf(" ");
        printf(" ");
    }
}

void print_column(uint16_t column)
{
    static int cpt=0;
    cpt++;
    printf("| ");
    print_bin(column);
    printf(" |\n");
    if(cpt==16)
    {
        //fin de la frame
        printf(" ----------------------------------\n");
        cpt=0;
    }
}

void select_column(int num_column)
{
    if(num_column==0)
    {
        //"reset" du terminal
        printf("\033[2J\033[1;1H");
        //début de la nouvelle frame
        printf(" ----------------------------------\n");
    }
}