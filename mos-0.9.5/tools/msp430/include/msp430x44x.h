#ifndef __msp430x44x
#define __msp430x44x

/* msp430x44x.h
 *
 * mspgcc project: MSP430 device headers
 * MSP430x44x family header
 *
 * (c) 2002 by M. P. Ashton <data@ieee.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: msp430x44x.h,v 1.7 2004/10/05 15:44:05 coppice Exp $
 */

#include <iomacros.h>

#define __msp430_have_port1
#define __msp430_have_port2
#define __msp430_have_port3
#define __msp430_have_port4
#define __msp430_have_port5
#define __msp430_have_port6
#define __msp430_have_fll_and_xt2
#define __msp430_have_usart1
#define __msp430_have_timerb7
#define __msp430_have_lcd_16_20
#define LCD_BASE 0x90

#include <msp430/basic_timer.h>
#include <msp430/system_clock.h>
#include <msp430/svs.h>
#include <msp430/lcd.h>
#include <msp430/flash.h>
#include <msp430/timera.h>
#include <msp430/timerb.h>
#include <msp430/usart.h>
#include <msp430/adc12.h>
#include <msp430/mpy.h>
#include <msp430/gpio.h>
#include <msp430/compa.h>

#include <msp430/common.h>

#define IE1_                0x0000  /* Interrupt Enable 1 */
sfrb(IE1,IE1_);
#define WDTIE               (1<<0)
#define OFIE                (1<<1)
#define NMIIE               (1<<4)
#define ACCVIE              (1<<5)
#define URXIE0              (1<<6)
#define UTXIE0              (1<<7)

#define IFG1_               0x0002  /* Interrupt Flag 1 */
sfrb(IFG1,IFG1_);
#define WDTIFG              (1<<0)
#define OFIFG               (1<<1)
#define NMIIFG              (1<<4)
#define URXIFG0             (1<<6)
#define UTXIFG0             (1<<7)

#define IE2_                0x0001  /* Interrupt Enable 2 */
sfrb(IE2,IE2_);
#define URXIE1              (1<<4)
#define UTXIE1              (1<<5)
#define BTIE                (1<<7)

#define IFG2_               0x0003  /* Interrupt Flag 2 */
sfrb(IFG2,IFG2_);
#define URXIFG1             (1<<4)
#define UTXIFG1             (1<<5)
#define BTIFG               (1<<7)

#define ME1_                0x0004  /* Module Enable 1 */
sfrb(ME1,ME1_);
#define URXE0               (1<<6)
#define USPIE0              (1<<6)
#define UTXE0               (1<<7)

#define ME2_                0x0005  /* Module Enable 2 */
sfrb(ME2,ME2_);
#define URXE1               (1<<4)
#define USPIE1              (1<<4)
#define UTXE1               (1<<5)

#define BASICTIMER_VECTOR   0       /* 0xFFE0 Basic Timer */
#define PORT2_VECTOR        2       /* 0xFFE2 Port 2 */
#define USART1TX_VECTOR     4       /* 0xFFE4 USART 1 Transmit */
#define USART1RX_VECTOR     6       /* 0xFFE6 USART 1 Receive */
#define PORT1_VECTOR        8       /* 0xFFE8 Port 1 */
#define TIMERA1_VECTOR      10      /* 0xFFEA Timer A CC1-2, TA */
#define TIMERA0_VECTOR      12      /* 0xFFEC Timer A CC0 */
#define ADC_VECTOR          14      /* 0xFFEE ADC */
#define USART0TX_VECTOR     16      /* 0xFFF0 USART 0 Transmit */
#define USART0RX_VECTOR     18      /* 0xFFF2 USART 0 Receive */
#define WDT_VECTOR          20      /* 0xFFF4 Watchdog Timer */
#define COMPARATORA_VECTOR  22      /* 0xFFF6 Comparator A */
#define TIMERB1_VECTOR      24      /* 0xFFF8 Timer B CC1-2, TB */
#define TIMERB0_VECTOR      26      /* 0xFFFA Timer B CC0 */
#define NMI_VECTOR          28      /* 0xFFFC Non-maskable */ 

#define UART0TX_VECTOR      USART0TX_VECTOR
#define UART0RX_VECTOR      USART0RX_VECTOR
#define UART1TX_VECTOR      USART1TX_VECTOR
#define UART1RX_VECTOR      USART1RX_VECTOR

#endif /* #ifndef __msp430x44x */
