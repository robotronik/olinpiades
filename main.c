#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "font.h"
#include "affichage.h"

int main()
{
	init_text_display();
	/*int i;
	for(i=0;i<7*16;i++)
	{
		print_bin(get_text_line(i));
		printf("\n");
	}
	while(1);*/
	while(1)
	{
		animation();
	}
	return 0;
}