#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "font.h"
#include "affichage.h"

#define LEN_TEXT 9

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

uint16_t get_text_line(int indice)
{
	return text_display[indice%(LEN_TEXT*16)];
}

uint16_t get_column(int column_num, int pos)
{
	uint16_t column_value=0;
	int i;
	for (i = 0; i < 16; i++)
	{
		column_value|=(((get_text_line(i+pos))>>(15-column_num))&1)<<(15-i);
	}
	return column_value;
}

uint16_t get_next_column()
{
	static int char_actuel=0;
	static int column_num=0;
	uint16_t next_column=get_column(column_num,char_actuel*16);
	column_num+=1;
	if(column_num==16)
	{
		char_actuel=(char_actuel+1)%LEN_TEXT;
	}
	column_num%=16;
	return next_column;
}

void animation()
{
	shift_columns(get_next_column());
	print_frame();
	usleep(50000);
} 