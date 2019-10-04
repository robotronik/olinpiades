#ifndef __CRC_16_H_
#define __CRC_16_H_

#include <stdint.h>

extern uint16_t crc_table[256];

#define CRC_INIT ((uint16_t) 0x0000)
#define UPDATE_CRC(crc_accum,byte) \
  crc_accum = (crc_accum << 8) ^ crc_table[((uint16_t) (crc_accum >> 8) ^ byte) & 0xFF]

#endif
