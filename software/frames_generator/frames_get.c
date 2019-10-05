#include "frames_get.h"
#include "frames_definition.h"

int get_frame(uint32_t frame[32], int number)
{
  int i = 0;
  for(i=0; i<32; i++)
    frame[i] = internal_frames[number][i];
  return 0;
}

int get_frame_duration(int number)
{
  return internal_frames_duration[number];
}

int get_frames_number()
{
  return internal_n_frames;
}
