/**
 * Library Robotronik Protocol
 * robotronik_protocol.h
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
#ifndef __ROBOTRONIK_PROTOCOL_H
#define __ROBOTRONIK_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include "crc_16.h"

//==================================================
//              Global definitions
//==================================================

//RP_MAX_PACKET_SIZE must be <= 251 (see RP_Packet below).
#define RP_MAX_PACKET_SIZE 251
#define RP_BUFFER_SIZE RP_MAX_PACKET_SIZE+5

//Data packet
typedef struct RP_Packet_S{
  uint8_t len;//Number of data bytes
  uint8_t data[RP_MAX_PACKET_SIZE];
}RP_Packet;
/*
 * Here is the frame format, by byte :
 * [COBS init] [size] [data]* [CRC-16_LOW] [CRC-16_HIGH] [EOF]
 * There is at most 251 data bytes.
 * Size is (3 + packet->len)
 * The CRC is calculated before byte stuffing, from [size] to the last
 * [data] byte
 */

typedef struct RP_Interface_S{
  
  uint8_t (*send)(uint8_t *, uint16_t, uint32_t);//data, size, timeout_ms
  uint32_t (*get_tick)();
  
  //Reception buffer
  uint8_t buffer_in[RP_BUFFER_SIZE];

  //Packet used for reception
  RP_Packet r_packet;
  /*
   * The FSM writes directly in this packet while receiving.  There is
   * no queue for received packets, so this packet is overwritten when
   * new data is received. The sender should wait for the receiver to
   * process the packet before sending a new one.
   */

  //Packet used for sending (optional)
  RP_Packet s_packet;
  /*
   * This packet can be used to prepare a packet before
   * sending. However, you must ensure that you're not doing
   * concurrent access.
   */
  
  //Output buffer
  uint8_t buffer_out[RP_BUFFER_SIZE];
  
  //Finite state machine for reception
  void (*update_state)(struct RP_Interface_S*);
  uint8_t bs_count;//COBS counter
  uint8_t size;//packet size
  uint8_t remaining;
  uint8_t *p_in;
  uint8_t *p_out;
  uint16_t crc_accum;
  volatile bool received;

  //Position set externally
  uint16_t sync_pos;
}RP_Interface;

//==================================================
//           Initialization functions
//==================================================

void RP_Init_Interface(RP_Interface *interface,
		       uint8_t (*send)(uint8_t *, uint16_t, uint32_t),
		       uint32_t (*get_tick)());
/**
 * Init the interface and its associated FSM and set send and get_tick
 * functions.
 */

//==================================================
//           Sending functions
//==================================================

int RP_Build_Frame(RP_Packet *packet, uint8_t buffer[RP_BUFFER_SIZE]);
/**
 * Builds a frame from the packet and store it in the buffer. Returns
 * the effective size of the frame if it succeeds, 0 otherwise. The
 * frame is built according to the Consistent Overhead Byte Stuffing
 * algorithm.
 * Conditions :
 * (packet != NULL)
 * (packet->len > 0)
 * (packet->data != NULL)
 * (3 + packet->len <= 254)
 *
 * Return the size of the built frame in bytes on success, -1 on error.
 */

int RP_Sync(RP_Interface *interface, uint32_t timeout);
/**
 * Send a single RP_EOF byte to synchronize the remote pair. It could
 * be useful to ensure that the receiver is in INIT mode and ready to
 * process the next packet. The synchronization is done at each end of
 * sent packet, this function is just for particular cases where we
 * need to do it before sending a new packet.
 * The timeout is in ms.
 *
 * Returns 0 on success, -1 on error.
 */

int RP_Send(RP_Interface *interface, RP_Packet *packet, uint32_t timeout);
/**
 * Send the given packet on 'interface', with a timeout on ms.
 *
 * Return 0 on success, -1 on error.
 */

//==================================================
//           Receiving functions
//==================================================

void RP_Process_Data(RP_Interface *interface, uint8_t *data, uint16_t len);
/**
 * Run the receiving fsm on bytes from data to data+len-1.
 */

int RP_Wait_Packet(RP_Interface *interface, uint32_t timeout_ms);
/**
 * Waits for a new packet to be received. Any packet received before
 * calling this function is not taken into account.  Return 0 if a
 * packet was received in the given time, -1 on timeout.
 */

void RP_Packet_Received(RP_Interface* interface, RP_Packet* packet);
/**
 * This function is called when a valid packet is received. It do
 * nothing by default. It is declared as weak, so it can be redefined
 * to handle the packets. 'interface' is the interface on which the
 * packet was received.
 */

void RP_Error_Handler(RP_Interface* interface, uint16_t err);
/**
 * This function is called when there was an error while receiving on
 * the 'interface' interface. 'err' is the error code, see below for
 * description of possible values. This function does nothing by
 * default and is declared as weak, so it can be redefined to handle
 * errors.
 */

//==================================================
//              Error management
//==================================================
//Error types
typedef enum RP_Error_Type_E{
  RP_ERR_INTERNAL = 0x0100, //Internal error
  RP_ERR_LINK = 0x0200, //Communication error
}RP_Error_Type;

//Internal errors
typedef enum RP_Internal_Error_E{
  RP_ERR_ILLEGAL_ARGUMENTS, //A function were called with invalid arguments
  RP_ERR_BUFFER_OVERFLOW, //An operation could not be performed
			  //to avoid an overflow
}RP_Internal_Error;

//Communication errors
typedef enum RP_Link_Error_E{
  RP_ERR_TIMEOUT, //When a timeout timed out
  RP_ERR_UNEXPECTED_EOF, //The EOF flag was found on a frame but were
			 //not expected. This is sometimes intentional
			 //(see RP_Sync())
  RP_ERR_SIZE, //The frame size wasn't as expected
  RP_ERR_CRC, //The calculated CRC was incorrect, ie. the frame is
	      //corrupt.
}RP_Link_Error;

//Macros on errors
#define RP_ERROR_TYPE(err) (RP_Error_Type) (err & 0xFF00)
#define RP_ERROR_CODE(err) (err & 0xFF)
#define RP_INTERNAL_ERROR(err) (RP_Internal_Error) RP_ERROR_CODE(err)
#define RP_LINK_ERROR(err) (RP_Link_Error) RP_ERROR_CODE(err)

uint16_t RP_Get_Error();
/**
 * This function returns the last error code set.
 */

#endif
