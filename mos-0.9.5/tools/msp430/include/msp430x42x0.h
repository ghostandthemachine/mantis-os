#ifndef __msp430x42x0
#define __msp430x42x0

/* msp430x42x0.h
 *
 * mspgcc project: MSP430 device headers
 * MSP430x42x0 family header
 *
 * (c) 2005 by Steve Underwood <steveu@coppice.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: msp430x42x0.h,v 1.1 2005/03/11 15:49:49 coppice Exp $
 */

#include <iomacros.h>

#define __msp430_have_port1
#define __msp430_have_port2
#define __msp430_have_port5
#define __msp430_have_port6
#define __msp430_have_fll
#define __msp430_have_lcd_a
#define __msp430_have_lcd_16_20
#define LCD_BASE 0x90
#define __msp430_have_sd16a
#define __msp430_have_dac12_op_amp

#include <msp430/basic_timer.h>
#include <msp430/system_clock.h>
#include <msp430/svs.h>
#include <msp430/lcd.h>
#include <msp430/flash.h>
#include <msp430/timera.h>
#include <msp430/gpio.h>
#include <msp430/sd16.h>
#include <msp430/dac12.h>

#include <msp430/common.h>

#define IE1_                0x0000  /* Interrupt Enable 1 */
sfrb(IE1,IE1_);
#define WDTIE               (1<<0)
#define OFIE                (1<<1)
#define NMIIE               (1<<4)
#define ACCVIE              (1<<5)

#define IFG1_               0x0002  /* Interrupt Flag 1 */
sfrb(IFG1,IFG1_);

#define WDTIFG              (1<<0)    /* Watchdog Interrupt Flag */
#define OFIFG               (1<<1)    /* Osc. Fault Interrupt Flag */
#define PORIFG              (1<<2)    /* Power On Interrupt Flag */
#define RSTIFG              (1<<3)    /* Reset Interrupt Flag */
#define NMIIFG              (1<<4)    /* NMI Interrupt Flag */

#define IE2_                0x0001  /* Interrupt Enable 2 */
sfrb(IE2,IE2_);
#define BTIE                (1<<7)

#define IFG2_               0x0003  /* Interrupt Flag 2 */
sfrb(IFG2,IFG2_);
#define BTIFG               (1<<7)

#define BASICTIMER_VECTOR   (0 * 2u)  /* 0xFFE0 Basic Timer */
#define PORT2_VECTOR        (1 * 2u)  /* 0xFFE2 Port 2 */

#define DAC12_VECTOR        (3 * 2u)  /* 0xFFE6 DAC 12 */
#define PORT1_VECTOR        (4 * 2u)  /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      (5 * 2u)  /* 0xFFEA Timer A CC1-2, TA */
#define TIMERA0_VECTOR      (6 * 2u)  /* 0xFFEC Timer A CC0 */

#define WDT_VECTOR          (10 * 2u) /* 0xFFF4 Watchdog Timer */

#define SD16_VECTOR         (12 * 2u) /* 0xFFF8 Sigma Delta ADC */

#define NMI_VECTOR          (14 * 2u) /* 0xFFFC Non-maskable */

#endif /* #ifndef __msp430x42x0 */
