#include <stdio.h>
#include <stdlib.h>

#include "../frames_get.h"

int main()
{
  uint_32 frame[32];
  get_frame(frame, 0);

  int i,j;
  for(i=0; i<32; i++)
  {
    for(j=0; j<32; j++)
    {
      if((frame[i] >> j) & 1)
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }

  return 0;
}
