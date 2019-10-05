#include "frames_get.h"
#include "frames_definition.h"

int get_frame(uint32_t frame[32], int number)
{
  if(number >= internal_n_frames)
    return 0;
  int i = 0;
  for(i=0; i<32; i++)
    frame[i] = internal_frames[number][i*4]
            + (internal_frames[number][i*4 + 1]<<8)
            + (internal_frames[number][i*4 + 2]<<16)
            + (internal_frames[number][i*4 + 3]<<24);
  return 1;
}

int get_frame_duration(int number)
{
  if(number >= internal_n_frames)
    return -1;
  return internal_frames_duration[number];
}

int get_frames_number()
{
  return internal_n_frames;
}
