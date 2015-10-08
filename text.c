#include <stdio.h>
#include <stdint.h>
//#include <unistd.h>
#include "font.h"
#include "affichage.h"

#define LEN_TEXT 13

static char texte[]="Hello World  ";

uint16_t get_char_line(int line_num, char caractere)
{
	return get_font(caractere)[line_num];
}

uint16_t get_column(int column_num, int char_num)
{
	uint16_t column_value=0;
	int i;
	for (i = 0; i < 16; i++)
	{
		column_value|=(((get_char_line(i,texte[char_num]))>>(15-column_num))&1)<<(15-i);
	}
	return column_value;
}

uint16_t get_next_column()
{
	static int char_actuel=0;
	static int column_num=0;
	uint16_t next_column=get_column(column_num,char_actuel);
	column_num+=1;
	if(column_num==11)
	{
		char_actuel=(char_actuel+1)%LEN_TEXT;
	}
	column_num%=11;
	return next_column;
}

void animation()
{
	//shift_columns(get_next_column());
	//print_frame();
	//usleep(50000);
} 