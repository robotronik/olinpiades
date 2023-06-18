#include "lowlevel/clock.h"
#include "lowlevel/uart.h"
#include "lowlevel/matrix_driver.h"

#include "frames_generator/frames_get.h"
#include "synchronize.h"

#include <libopencm3/stm32/gpio.h>


void vers_left(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,31);
  display_matrix(frame,100);
  get_frame(frame,34);
  display_matrix(frame,100);
  get_frame(frame,35);
  display_matrix(frame,100);
}

void ret_left(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,35);
  display_matrix(frame,100);
  get_frame(frame,34);
  display_matrix(frame,100);
  get_frame(frame,31);
  display_matrix(frame,100);
}

void vers_right(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,31);
  display_matrix(frame,100);
  get_frame(frame,32);
  display_matrix(frame,100);
  get_frame(frame,33);
  display_matrix(frame,100);
}

void ret_right(){
  uint32_t frame[MATRIX_SIZE];
  get_frame(frame,33);
  display_matrix(frame,100);
  get_frame(frame,32);
  display_matrix(frame,100);
  get_frame(frame,31);
  display_matrix(frame,100);
}

void ouvrir(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=40;i>=36;i--){
    get_frame(frame,i);
    display_matrix(frame,75);
  }
}

void fermer(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=36;i<41;i++){
    get_frame(frame,i);
    display_matrix(frame,75);
  }
}

void tatouage(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=0;i<7;i++){
    get_frame(frame,i);
    display_matrix(frame,75);
  }
  for(int i=6;i>=0;i--){
    get_frame(frame,i);
    display_matrix(frame,75);
  }
}

void fire(){
  uint32_t frame[MATRIX_SIZE];
  for(int ix=0; ix<10; ix++){
     for(int i=7;i<15;i++){
      get_frame(frame,i);
      display_matrix(frame,20);
    }
  } 
}

void bonhomme(){
  uint32_t frame[MATRIX_SIZE];
  for(int i=19;i<31;i++){
    get_frame(frame,i);
    display_matrix(frame,50);
  }
  for(int i=30;i>=19;i--){
    get_frame(frame,i);
    display_matrix(frame,50);
  }
}

int main() {
  clock_setup();
  led_driver_setup();
  //uart_setup();

  //sync_init();


  uint32_t frame[MATRIX_SIZE];

  uint32_t frame_number = 0;
  uint32_t frame_count = get_frames_number();

  gpio_mode_setup(GPIOA,GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN, GPIO2);
  gpio_mode_setup(GPIOA,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3);


  while (1) {
    //sync_resync();
    //sync_send();

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
     ouvrir();

      gpio_clear(GPIOA, GPIO3);
      get_frame(frame,31);
      while(gpio_get(GPIOA, GPIO2)!=0){
        display_matrix(frame,1);
      }
      display_matrix(frame,2);
      gpio_set(GPIOA, GPIO3);
      
      // uint32_t frame[MATRIX_SIZE];
      // get_frame(frame,13);
      // while (1)
      // {
      //   display_matrix(frame,15000);
      // }
      
      vers_right();
      ret_right();
      vers_left();
      ret_left();
      fermer();

      bonhomme();

      ouvrir();
      vers_right();
      ret_right();
      vers_left();
      ret_left();
      fermer();

      fire();

      ouvrir();
      vers_right();
      ret_right();
      vers_left();
      ret_left();
      fermer();

      tatouage();

      
    }

    // TODO we need to go through this loop more than once per frame ?

    frame_number = (frame_number + 1) % (frame_count*2);
  };

  return 0;
}
