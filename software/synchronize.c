#include "synchronize.h"

#include "lowlevel/uart.h"
void __attribute__((weak)) echo(char* chain) { }

#include <stdint.h>

static const uint8_t indice_max = 255;

static uint32_t indice = 0;
static uint32_t indice_received = 0;
static int      indice_was_received = 0;

void sync_init() {
  indice = 0;
  // interrupt,…
}

void sync_send() {
  char c = indice;
  echo(&c);
}

uint32_t modulo(int x, int N){
  return (x % N + N) % N;
}

int compare(uint32_t local, uint32_t distant) {
  int32_t difference = local - distant;
  uint32_t mod = modulo(difference, indice_max);
  if (mod == 0)
    return 0;
  else if (mod < indice_max / 2)
    return 1;
  else
    return -1;
}


void sync_resync() {
  // Receive

  // Do not resync if no indice was received
  if (!indice_was_received)
    return;

  indice_was_received = 0;

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
