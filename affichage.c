#include <stdint.h>
#include <stdio.h>
#include "font.h"

#define LEN_TEXT 9

static int debut_frame=15;
static uint16_t frame[16];

static char texte[]="bonjour  ";
static uint16_t text_display[7*16];

void init_text_display()
{
	int i,j;
	for(i=0;i<7;i++)
	{
		for(j=0;j<16;j++)
		{
			text_display[i*16+j]=(get_font(texte[i])[j]);
		}
	}
}

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

uint16_t get_text_line(int indice)
{
	return text_display[indice%(LEN_TEXT*16)];
}

uint16_t get_frame_line(int indice)
{
	return frame[(debut_frame+indice)%16];
}


uint16_t compute_column(int column_num, int pos)
{
	uint16_t column_value=0;
	int i;
	for (i = 0; i < 16; i++)
	{
		column_value|=(((get_text_line(i+pos))>>(15-column_num))&1)<<(15-i);
	}
	return column_value;
}

void print_frame()
{
	int i;
	printf(" ----------------------------------\n");
	for(i=0;i<16;i++)
	{
		print_column(get_frame_line(i));
	}
	printf(" ----------------------------------\n");
}

void compute_next_frame()
{
	static int char_actuel=0;
	static int column_num=0;
	frame[debut_frame]=compute_column(column_num,char_actuel*16);
	debut_frame-=1;
	if(debut_frame==-1)
	{
		debut_frame=15;
	}
	column_num+=1;
	if(column_num==16)
	{
		char_actuel=(char_actuel+1)%LEN_TEXT;
	}
	column_num%=16;
}

void animation()
{
	compute_next_frame();
	print_frame();
	printf("\033[2J\033[1;1H");
	usleep(50000);
} 