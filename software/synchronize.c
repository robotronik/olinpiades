#include "synchronize.h"

#include "lowlevel/uart.h"

#include <stdint.h>

static const uint32_t indice_max = 1 << 30; // should not be 31 for comparison

static uint32_t indice = 0;
static uint32_t indice_received = 0;

void sync_init() {
  indice = 0;
  // interrupt,…
}

void sync_send() {
  echo_int(indice);
}

static int compare(uint32_t local, uint32_t distant) {
  int32_t difference = local - distant;
  difference %= indice_max;
  if (difference == 0)
    return 0;
  else if (difference < indice_max / 2)
    return 1;
  else
    return -1;
}


void sync_resync() {
  // Receive

  switch(compare(indice, indice_received)) {
  case 0:   // do nothing, synced
    break;
  case 1:   // We are in advance, we continue, the other will catch on
    break;
  case -1:  // We need to catch on with the other that does not wait for us
    indice = indice_received;
    break;
  }
}
