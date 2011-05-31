#ifndef __msp430x11x1
#define __msp430x11x1

/* msp430x11x1.h
 *
 * mspgcc project: MSP430 device headers
 * MSP430x11x1 family header
 *
 * (c) 2002 by M. P. Ashton <data@ieee.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: msp430x11x1.h,v 1.5 2002/12/28 06:49:28 coppice Exp $
 */

#include <iomacros.h>

#define __msp430_have_port1
#define __msp430_have_port2

#include <msp430/basic_clock.h>
#include <msp430/flash.h>
#include <msp430/eprom.h>
#include <msp430/timera.h>
#include <msp430/gpio.h>
#include <msp430/compa.h>

#include <msp430/common.h>

#define IE1_                0x0000  /* Interrupt Enable 1 */
sfrb(IE1,IE1_);
#define WDTIE               (1<<0)
#define OFIE                (1<<1)
#define NMIIE               (1<<4)
#define ACCVIE              (1<<5)

#define IFG1_               0x0002  /* Interrupt Flag 1 */
sfrb(IFG1,IFG1_);
#define WDTIFG              (1<<0)
#define OFIFG               (1<<1)
#define NMIIFG              (1<<4)

#define PORT1_VECTOR        4       /* 0xFFE4 Port 1 */
#define PORT2_VECTOR        6	    /* 0xFFE6 Port 2 */
#define TIMERA1_VECTOR      16	    /* 0xFFF0 Timer A CC1-2, TA */
#define TIMERA0_VECTOR      18	    /* 0xFFF2 Timer A CC0 */
#define WDT_VECTOR          20	    /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  22	    /* 0xFFF6 Comparator A */
#define NMI_VECTOR          28	    /* 0xFFFC Non-maskable */

#endif /* #ifndef __msp430x11x1 */

