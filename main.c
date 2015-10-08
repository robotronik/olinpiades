#include "text.h"
#include "hardware.h"

int main()
{
	init_hardware();
	//test();
	while(1)
	{
		write_SPI1(0x0FFF);
		//animation();
	}
	return 0;
}