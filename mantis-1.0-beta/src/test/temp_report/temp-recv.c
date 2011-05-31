#include "mos.h"
#include "dev.h"
#include "com.h"
#include "crc.h"
#include "hex_output.h"
#include "sem.h"
#include "user_button.h"
#include "packet_ids.h"

mos_sem_t button;

uint16_t counter[4] ={0,0,0};

void pkt_hello(comBuf* p)
{
   if (p->size != 5)
      return;

   uint16_t id = buf_extract_WORD(p->data, 1);
   uint16_t crc = buf_extract_WORD(p->data, 3);

   if (crc != crc_compute(p->data, 3))
      return;

   printf("Node %x has come online\n\n", id);
   
}

void pkt_sense(comBuf* p)
{
   uint16_t id, temp, hum, crc, light1, light2;
   uint8_t pid;
   double actual_temp;
   double actual_hum;
   const char* timed = "timed";
   const char* req = "requested";
   const char* unk = "unknown";
   const char* msg = unk;
   
   if (p->size != 13)
      return;

   pid    = p->data[0];
   id     = buf_extract_WORD(p->data, 1);
   temp   = buf_extract_WORD(p->data, 3);
   hum    = buf_extract_WORD(p->data, 5);
   light1 = buf_extract_WORD(p->data, 7);
   light2 = buf_extract_WORD(p->data, 9);
   crc    = buf_extract_WORD(p->data, 11);

   
   // make sure the CRC matches what it should
   if (crc == crc_compute(p->data, 11))
   {

      if (pid == PKT_TIMED_SENSE)
	 msg = timed;
      else if (pid = PKT_REQUESTED_SENSE)
	 msg = req;

	 
      // calculate actual temperature
      actual_temp = -39.96f + 0.018f * temp;
      // calculate relative humidity
      actual_hum  = -4.0f + (0.0405f * hum) + (-0.0000028 * hum * hum);
	 
      
      printf("Node %x (%s):\n", id, msg);
      counter[id]++;
      
      //print_hexdump(p->data, p->size);

/*       printf("  temperature:  %d.%d\n", (int)actual_temp, (int)((actual_temp - (int)actual_temp) * 100)); */
/*       printf("  humidity   :  %d.%d%%\n", (int)actual_hum, (int)((actual_hum - (int)actual_hum) * 100)); */
/*       printf("  light1     :  %d\n", light1); */
/*       printf("  light2     :  %d\n", light2); */
/*       printf("  crc        :  %x\n\n", crc); */

   }
}



void recv_thread(void)
{
   com_mode(IFACE_RADIO, IF_LISTEN);

   while(1)
   {
      comBuf* p = com_recv(IFACE_RADIO);
      if (p)
      {
	 switch(p->data[0])
	 {
	 case PKT_HELLO:
	    pkt_hello(p);
	    break;
	 case PKT_TIMED_SENSE:
	 case PKT_REQUESTED_SENSE:
	    pkt_sense(p);
	    break;
	 default:
	    //printf("Unknown packet id: %x\n\n", (uint16_t)p->data[0]);
	 }

	 com_free_buf(p);
	 

      }
      else
	 printf("com_recv(IFACE_RADIO) returned NULL\n\n");
      
      
   }
   
}

comBuf buf_out;

void button_handler(void)
{
   mos_sem_post(&button);
}

void button_thread(void)
{
   uint8_t i = 0;
   
   while(1)
   {
      mos_led_toggle(0);
      mos_sem_wait(&button);   
      
      for(i = 1; i < 4; ++i)
	 printf("** Node %x %d\n", (int)i, counter[i]);
      
/// send a DO_SENSE packet /////////////////////////////////
      buf_out.data[0] = PKT_DO_SENSE;
      buf_insert_WORD(buf_out.data, 1, mos_node_id_get());
      buf_insert_WORD(buf_out.data, 3, crc_compute(buf_out.data, 3));
      buf_out.size = 5;
      ////////////////////////////////////////////////////////////
      com_send(IFACE_RADIO, &buf_out);
   }
   
}



void start(void)
{
   mos_sem_init(&button, 0);
   
   mos_enable_user_button(button_handler);
   
   mos_thread_new(recv_thread, 256, PRIORITY_NORMAL);
   mos_thread_new(button_thread, 128, PRIORITY_NORMAL);
   
}


