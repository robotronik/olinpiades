#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


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
	printf("| ");
	print_bin(column);
	printf(" |\n");
}

void print_frame(uint16_t * frame, int pos)
{
	int i;
	printf(" ----------------------------------\n");
	for(i=0;i<16;i++)
	{
		print_column(*(frame+(i+pos)%19));
	}
	printf(" ----------------------------------\n");
}

void animation()
{
	static int pos=0;
	static uint16_t frame[]=
	{0b0000000000000000,
	 0b0000000110000000,
	 0b0000001110000000,
	 0b0000011110000000,
	 0b0000110110000000,
	 0b0001100110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000000110000000,
	 0b0000111111110000,
	 0b0000111111110000,
	 0b0000000000000000,
	 0b0000000000000000,
	 0b0000000000000000,
	 0b0000000000000000};
	print_frame(frame,pos);
	printf("\033[2J\033[1;1H");
	usleep(50000);
	pos=(pos+1)%19;
} 

int main()
{
	while(1)
	{
		animation();
	}
	return 0;
}