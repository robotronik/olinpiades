/**
 * Library Robotronik Protocol
 * robotronik_protocol.c
 *
 * This library is meant to implement a light and reliable protocol
 * for communication between two MCUs. The protocol was designed for
 * request-response oriented communications. It is why it focuses on
 * performance for asynchronous reception.
 * 
 * It uses the Consistent Overhead Byte Stuffing algorithm to delimit
 * the frames and for synchronization purposes. CRC-16/BUYPASS is
 * used to detect corrupted frames.
 *
 * Copyright 2018 Antonin Hirschy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "robotronik_protocol.h"

#define RP_EOF 0x00
#define WRITE_BUFF(p_buffer,byte) *(p_buffer++) = byte;
#define ENCODE_BYTE(byte,p_buffer,p_code) {\
    if(byte == RP_EOF){			   \
      byte = p_buffer - p_code;		   \
      *p_code = byte;			   \
      p_code = p_buffer++;		   \
    }					   \
    else{				   \
      *(p_buffer++) = byte;		   \
    }					   \
  }

static uint16_t err;

static void RP_FSM_INIT(RP_Interface *interface);
static void RP_FSM_SIZE(RP_Interface *interface);
static void RP_FSM_DATA(RP_Interface *interface);
static void RP_FSM_CRC_LOW(RP_Interface *interface);
static void RP_FSM_CRC_HIGH(RP_Interface *interface);
static void RP_FSM_END(RP_Interface *interface);

//==================================================
//           Initialization functions
//==================================================

void RP_Init_Interface(RP_Interface *interface,
		       uint8_t (*send)(uint8_t *, uint16_t, uint32_t),
		       uint32_t (*get_tick)()){
  interface->send = send;
  interface->get_tick = get_tick;
  interface->received = false;
  
  //FSM
  interface->update_state = RP_FSM_INIT;
  interface->p_in = interface->buffer_in;
  interface->p_out = interface->r_packet.data;
  interface->crc_accum = 0;
}

void __attribute__((weak)) RP_Packet_Received(RP_Interface* interface, RP_Packet* packet){
  //Avoid compiler warnings.
  (void)interface;
  (void)packet;
}

void __attribute__((weak)) RP_Error_Handler(RP_Interface* interface, uint16_t err){
  //Avoid compiler warnings.
  (void)interface;
  (void)err;
 }

//==================================================
//           Sending functions
//==================================================

int RP_Build_Frame(RP_Packet *packet, uint8_t buffer[RP_BUFFER_SIZE]){
  if((packet->len <= 0) || (packet->len + 5 > RP_BUFFER_SIZE) || (packet->len > RP_MAX_PACKET_SIZE)){
    err =  RP_ERR_INTERNAL | RP_ERR_ILLEGAL_ARGUMENTS;
    return -1;
  }

  uint8_t *p_buffer = buffer;
  uint8_t *p_code = p_buffer++;
  uint16_t crc_accum = CRC_INIT;

  //Size (remaining bytes)
  const uint8_t size = 3 + packet->len;
  *(p_buffer++) = size;
  UPDATE_CRC(crc_accum, size);
  
  int i;
  for(i = 0; i < packet->len; i++){
    uint8_t byte = packet->data[i];
    UPDATE_CRC(crc_accum,byte);
    ENCODE_BYTE(byte,p_buffer, p_code);
  }
  
  //CRC-16
  uint8_t crc_low = crc_accum & 0xFF;
  uint8_t crc_high = crc_accum >> 8;
  ENCODE_BYTE(crc_low, p_buffer, p_code);
  ENCODE_BYTE(crc_high, p_buffer, p_code);
  
  //RP_EOF
  *p_code = p_buffer - p_code;
  *(p_buffer++) = RP_EOF;

  return p_buffer - buffer;
}

int RP_Sync(RP_Interface *interface, uint32_t timeout){
  uint8_t byte = RP_EOF;

  if(interface->send(&byte, 1, timeout) != 0){
    err = RP_ERR_LINK | RP_ERR_TIMEOUT;
    return -1;
  }
  
  return 0;
}

int RP_Send(RP_Interface *interface, RP_Packet *packet, uint32_t timeout){
  int len = RP_Build_Frame(packet, interface->buffer_out);

  if(len == -1){
    return -1;
  }

  if(interface->send(interface->buffer_out, len, timeout) != 0){
    err = RP_ERR_LINK | RP_ERR_TIMEOUT;
    return -1;
  }
  
  return 0;
}

//==================================================
//           Receiving functions
//==================================================

void RP_Process_Data(RP_Interface *interface, uint8_t *data, uint16_t len){
  interface->p_in = data;

  while(len--){
    interface->update_state(interface);
  }
}

int RP_Wait_Packet(RP_Interface *interface, uint32_t timeout_ms){
  int start = interface->get_tick();
  
  //interface->received = false;
  while(!interface->received && (interface->get_tick() - start < timeout_ms));
  
  if(!interface->received){
    return -1;
  }
  
  interface->received = false;
  
  return 0;
}

#define FSM_UPDATE(fsm,state_function) fsm->update_state = state_function

#define FSM_GET_BYTE(fsm) uint8_t byte = *(fsm->p_in++);

#define FSM_BYTE byte

#define FSM_RESET(fsm) {						\
    FSM_UPDATE(fsm, RP_FSM_INIT);					\
    fsm->crc_accum = 0;							\
    fsm->p_out = fsm->r_packet.data;					\
    return;								\
  }

#define FSM_ERR(fsm, err_code) {		\
  err = err_code;				\
  RP_Error_Handler(fsm, err);			\
  FSM_RESET(fsm);				\
  }

#define FSM_CHECK_ERR(fsm, err_code) {		\
    if(FSM_BYTE == RP_EOF){			\
      FSM_ERR(fsm, err_code);			\
    }						\
  }

#define FSM_CHECK_EOF(fsm) {			\
    if(FSM_BYTE == RP_EOF) {FSM_RESET(fsm);}	\
  }
/**
 * Reinit the FSM when EOF is reached.
 * Set the 'valid' flag of FSM
 * and the error code.
 */

#define FSM_DECODE_BYTE(fsm, byte)			\
  (((--fsm->bs_count) == 0)?				\
   (fsm->bs_count = byte, (uint8_t) RP_EOF):		\
   (byte))
/**
 * Update the COBS counter and decode the current byte. This macro can
 * be used once and only once in an fsm state. If the macro is not
 * used and the FSM is not reset, bs_count MUST be updated manually.
 */

static void RP_FSM_INIT(RP_Interface *interface){
  FSM_GET_BYTE(interface);
  /* 
   * If current byte is EOF, the fsm is reset but no error is set :
   * it's just a blank frame that can be used for synchronisation
   * purpose.
   */
  FSM_CHECK_EOF(interface);

  /*
   * The first byte initializes the COBS algorithm.
   */
  interface->bs_count = FSM_BYTE;

  FSM_UPDATE(interface, RP_FSM_SIZE);
}

static void RP_FSM_SIZE(RP_Interface *interface){
  FSM_GET_BYTE(interface);
  /*
   * From this byte, reaching an EOF flag before the END state is
   * unexpected and will trigger an error.
   */
  FSM_CHECK_ERR(interface, RP_ERR_LINK | RP_ERR_UNEXPECTED_EOF);

  /*
   * FSM_DECODE_BYTE is not used here because the protocol requires
   * that the size is > 0. So bs_count is decremented manually.
   */
  --(interface->bs_count);

  /*
   * For the states RP_FSM_SIZE and RP_FSM_DATA, the CRC must be
   * updated for each byte.
   */
  UPDATE_CRC(interface->crc_accum, FSM_BYTE);
  /*
   * Get the packet length. It will be used to find the CRC position.
   */
  interface->size = interface->remaining = FSM_BYTE - 3;
  interface->r_packet.len = interface->size;
  
  /*
   * Checks wether or not the read size is consistent.
   */
  if(interface->size > RP_MAX_PACKET_SIZE){
    FSM_ERR(interface, RP_ERR_LINK | RP_ERR_SIZE);
  }
  
  FSM_UPDATE(interface, RP_FSM_DATA);
}

static void RP_FSM_DATA(RP_Interface *interface){
  FSM_GET_BYTE(interface);
  FSM_CHECK_ERR(interface, RP_ERR_LINK | RP_ERR_UNEXPECTED_EOF);

  /*
   * Note that the CRC is computed AFTER the byte is decoded. Indeed,
   * the CRC concerns the useful data.
   */
  FSM_BYTE = FSM_DECODE_BYTE(interface, FSM_BYTE);
  *(interface->p_out++) = FSM_BYTE;
  UPDATE_CRC(interface->crc_accum, FSM_BYTE);

  if(!(--interface->remaining)){
    /*
     * According to the size read, the next bytes should contains CRC
     * information.
     */
    FSM_UPDATE(interface, RP_FSM_CRC_LOW);
  }
}

static void RP_FSM_CRC_LOW(RP_Interface *interface){
  FSM_GET_BYTE(interface);
  FSM_CHECK_ERR(interface, RP_ERR_LINK | RP_ERR_UNEXPECTED_EOF);

  /*
   * Checks the low byte of CRC, and triggers an error if it doesn't match.
   */
  if((interface->crc_accum & 0xFF) != FSM_DECODE_BYTE(interface, FSM_BYTE)){
    FSM_ERR(interface, RP_ERR_LINK | RP_ERR_CRC);
  }else{
    FSM_UPDATE(interface, RP_FSM_CRC_HIGH);
  }
}

static void RP_FSM_CRC_HIGH(RP_Interface *interface){
  FSM_GET_BYTE(interface);
  FSM_CHECK_ERR(interface, RP_ERR_LINK | RP_ERR_UNEXPECTED_EOF);

  /*
   * Checks the high byte of CRC, and triggers an error if it doesn't match.
   */
  if((interface->crc_accum >> 8) != FSM_DECODE_BYTE(interface, FSM_BYTE)){
    FSM_ERR(interface, RP_ERR_LINK | RP_ERR_CRC);
  }else{
    FSM_UPDATE(interface, RP_FSM_END);
  }
}

static void RP_FSM_END(RP_Interface *interface){
  FSM_GET_BYTE(interface);

  /*
   * The last byte must be EOF. Otherwise, it is an error.
   */
  if(FSM_BYTE == 0x00){
    interface->received = true;
    RP_Packet_Received(interface, &interface->r_packet);
    FSM_RESET(interface);
  }else{
    FSM_ERR(interface, RP_ERR_LINK | RP_ERR_SIZE);
  }
}

uint16_t RP_Get_Error(){
  return err;
}
