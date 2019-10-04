#include "lowlevel/clock.h"
#include "lowlevel/uart.h"
#include "lowlevel/matrix_driver.h"

#include "synchronize.h"

int main() {
  clock_setup();
  led_driver_setup();
  uart_setup();

  sync_init();


  uint32_t frame[MATRIX_SIZE];
  uint32_t frame_number = 0;

  uint32_t frame_count = get_frame_count();

  while (1) {
    sync_resync();
    sync_send();

    get_frame(frame, frame_number);

    display_matrix(frame);

    // TODO we need to go through this loop more than once per frame ?

    frame_number = (frame_number + 1) % frame_count;
  };

  return 0;
}
