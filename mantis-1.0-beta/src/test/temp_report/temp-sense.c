#include "mos.h"
#include "dev.h"
#include "com.h"
#include "node_id.h"
#include "crc.h"
#include "adc.h"
#include "mutex.h"
#include "packet_ids.h"

comBuf buf;

mos_mutex_t send_mutex;

uint8_t no_sensor = 0;

void send_packet(uint8_t packet_id)
{
   static uint8_t inited = 0;
   uint16_t temp;
   uint16_t hum;
   
   if (!inited)
   {
      inited = 1;
      dev_open(DEV_MSP_HUMIDITY);
      if (dev_mode(DEV_MSP_HUMIDITY, DEV_MODE_ON) == DEV_FAILURE)
      {
	 no_sensor = 1;
      }
      
   }
   
   mos_mutex_lock(&send_mutex);

   if (no_sensor)
   {
      temp = rand();
      hum = rand();
   }
   else
   {
      
      dev_read(DEV_MSP_TEMPERATURE, &temp, sizeof(temp));
      dev_read(DEV_MSP_HUMIDITY, &hum, sizeof(hum));
   }
   

   buf.size = 13;
   buf.data[0] = packet_id;
   
   buf_insert_WORD(buf.data, 1, mos_node_id_get());
   buf_insert_WORD(buf.data, 3, temp);
   buf_insert_WORD(buf.data, 5, hum);
   if (no_sensor)
   {
      buf_insert_WORD(buf.data, 7, rand());
      buf_insert_WORD(buf.data, 9, rand());
   }
   else
   {
      buf_insert_WORD(buf.data, 7, adc_get_conversion16(4));
      buf_insert_WORD(buf.data, 9, adc_get_conversion16(5));
   }
   
   buf_insert_WORD(buf.data, 11, crc_compute(buf.data, 11));

   com_send(IFACE_RADIO, &buf);

   mos_mutex_unlock(&send_mutex);
}


void sense_thread(void)
{

   while(1)
   {  
      mos_led_toggle(1);
      send_packet(PKT_TIMED_SENSE);
      mos_thread_sleep(1000);
   }
   
}


void recv_thread(void)
{
   while(1)
   {
      
      IF_SET set;
      IF_ZERO(&set);
      IF_SET(IFACE_RADIO, &set);

      if(com_select(&set, 1000))
      {
	 
	 comBuf* p = com_recv(IFACE_RADIO);
	 if (p && p->data[0] == PKT_DO_SENSE)
	 {
	    if (p->size != 5)
	       continue;

	    if (crc_compute(p->data, 3) != buf_extract_WORD(p->data, 3))
	       continue;

	    send_packet(PKT_REQUESTED_SENSE);
	 }
	 

	 com_free_buf(p);
      }
   }
   
   
   
}



void start(void)
{
   com_mode(IFACE_RADIO, IF_LISTEN);
   /// Send a HELLO packet //////////////////////////////
   buf.size = 5;
   buf.data[0] = PKT_HELLO;
   buf_insert_WORD(buf.data, 1, mos_node_id_get());
   buf_insert_WORD(buf.data, 3, crc_compute(buf.data, 3));
   //////////////////////////////////////////////////////
   com_send(IFACE_RADIO, &buf);
   
   mos_thread_new(sense_thread, 256, PRIORITY_NORMAL);
   mos_thread_new(recv_thread, 256, PRIORITY_NORMAL);
}
