#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FRAME_LEN 48

static uint16_t frame[]=
{
	0x0000, //            
	0x0060, //      ##    
	0x03E0, //   #####    
	0x0060, //      ##    
	0x0060, //      ##    
	0x0060, //      ##    
	0x0060, //      ##    
	0x0060, //      ##    
	0x0060, //      ##    
	0x0060, //      ##    
	0x03FC, //   ######## 
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //         


	0x0000, //            
	0x00F0, //     ####   
	0x0198, //    ##  ##  
	0x0318, //   ##   ##  
	0x0318, //   ##   ##  
	0x0030, //       ##   
	0x0060, //      ##    
	0x00C0, //     ##     
	0x0180, //    ##      
	0x0300, //   ##       
	0x03F8, //   #######  
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //       


	0x0000, //            
	0x03F0, //   ######   
	0x0618, //  ##    ##  
	0x0018, //        ##  
	0x0030, //       ##   
	0x01F0, //    #####   
	0x0038, //       ###  
	0x0018, //        ##  
	0x0018, //        ##  
	0x0618, //  ##    ##  
	0x03F0, //   ######   
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //            
	0x0000, //
};

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

uint16_t get_frame_line(int indice)
{
	/*static uint16_t frame[]=
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
	 0b0000000000000000};*/

	return frame[indice%FRAME_LEN];
}


uint16_t compute_column(int column_num, int pos)
{
	uint16_t column_value=0;
	int i;
	for (i = 0; i < 16; i++)
	{
		column_value|=(((get_frame_line(i+pos))>>column_num)&1)<<(15-i);
	}
	return column_value;
}

void print_frame(int pos)
{
	int i;
	printf(" ----------------------------------\n");
	for(i=0;i<16;i++)
	{
		print_column(compute_column(i,pos));
	}
	printf(" ----------------------------------\n");
}

void animation()
{
	static int pos=0;
	print_frame(pos);
	printf("\033[2J\033[1;1H");
	usleep(50000);
	pos=(pos+1)%FRAME_LEN;
} 

int main()
{
	while(1)
	{
		animation();
	}
	return 0;
}