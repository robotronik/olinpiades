#include "lowlevel/clock.h"
#include "lowlevel/uart.h"
#include "lowlevel/matrix_driver.h"

#include "frames_generator/frames_get.h"
#include "synchronize.h"


void vers_left(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,0);
  display_matrix(frame,300);
  get_frame(frame,1);
  display_matrix(frame,300);
  get_frame(frame,2);
  display_matrix(frame,300);
}

void ret_left(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,2);
  display_matrix(frame,300);
  get_frame(frame,1);
  display_matrix(frame,300);
  get_frame(frame,0);
  display_matrix(frame,300);
}

void vers_right(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,0);
  display_matrix(frame,300);
  get_frame(frame,3);
  display_matrix(frame,300);
  get_frame(frame,4);
  display_matrix(frame,300);
}

void ret_right(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,4);
  display_matrix(frame,300);
  get_frame(frame,3);
  display_matrix(frame,300);
  get_frame(frame,0);
  display_matrix(frame,300);
}

void ouvrir(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=19;i>4;i--){
    get_frame(frame,i);
    display_matrix(frame,100);
  }
  get_frame(frame,0);
  display_matrix(frame,100);
}

void fermer(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=5;i<20;i++){
    get_frame(frame,i);
    display_matrix(frame,100);
  }
}

int main() {
  clock_setup();
  led_driver_setup();
  uart_setup();

  sync_init();


  uint32_t frame[MATRIX_SIZE];

  uint32_t frame_number = 0;
  uint32_t frame_count = get_frames_number();

  while (1) {
    sync_resync();
    sync_send();

    int real_frame;
    if (frame_number > frame_count) {
        real_frame = 2 * frame_count - frame_number;
    } else {
        real_frame = frame_number;
    }

/*
    get_frame(frame, real_frame);

    display_matrix(frame);
*/

    while(1){
      /* gauche
      vers_left();
      ret_left();
      vers_right();
      ret_right();
      */
      vers_right();
      ret_right();
      vers_left();
      ret_left();
      fermer();
      ouvrir();
    }

    // TODO we need to go through this loop more than once per frame ?

    frame_number = (frame_number + 1) % (frame_count*2);
  };

  return 0;
}
