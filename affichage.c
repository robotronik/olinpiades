#include <stdint.h>
#include "hardware.h"

static int debut_frame=15;
static uint16_t frame[16];

uint16_t get_frame_line(int indice)
{
	return frame[(debut_frame+indice)%16];
}

void print_frame()
{
	int i;
	for(i=0;i<16;i++)
	{
		select_column(i);
		print_column(get_frame_line(i));
	}
}

void shift_frame(uint16_t new_column)
{
	frame[debut_frame]=new_column;
	debut_frame-=1;
	if(debut_frame==-1)
	{
		debut_frame=15;
	}
}

void compute_next_frame()
{

}