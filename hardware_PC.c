#include <stdint.h>
#include <stdio.h>

static uint16_t actual_frame[16];
static uint16_t actual_column=0;

void print_bin(uint16_t num_bin)
{
    unsigned i;
    for (i = 1 << 15; i > 0; i = i / 2)
    {
        (num_bin & i)? printf("0"): printf(" ");
        printf(" ");
    }
}

uint16_t get_line(int line_num)
{
    uint16_t line_value=0;
    int i;
    for (i = 0; i < 16; i++)
    {
        line_value|=(((actual_frame[i])>>(15-line_num))&1)<<(15-i);
    }
    return line_value;
}

void print_column(uint16_t column)
{
    actual_frame[actual_column]=column;
    if(actual_column==0)
    {
        printf("\033[2J\033[1;1H");
        printf(" ----------------------------------\n");
        int i;
        for(i=0;i<16;i++)
        {
            printf("| ");
            print_bin(get_line(i));
            printf(" |\n");
        }
        printf(" ----------------------------------\n");
    }
}

void select_column(int num_column)
{
    actual_column=num_column;
}