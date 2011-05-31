#ifndef __PACKET_IDS_H__
#define __PACKET_IDS_H__

/**** Packet format ****
 * sent when a node boots up
 * (uint8_t)   PKT_HELLO
 * (uint16_t)  node id
 * (uint16_t)  crc
 ***********************/
#define PKT_HELLO       0x44


/**** Packet format ****
 * sent when requested or every X interval
 * (uint8_t)    PKT_*_SENSE
 * (uint16_t)   Node ID
 * (uint16_t)   Raw Temperature Data
 * (uint16_t)   Raw Humidity Data
 * (uint16_t)   Light Data 1
 * (uint16_t)   Light Data 2
 * (uint16_t)   crc
 ***********************/
#define PKT_TIMED_SENSE 0x45
#define PKT_REQUESTED_SENSE 0x47


/**** Packet format ****
 * sent to request a sensor reading
 * (uint8_t)   PKT_DO_SENSE
 * (uint16_t)  sending node id
 * (uint16_t)  crc
 ***********************/
#define PKT_DO_SENSE    0x46

#endif
