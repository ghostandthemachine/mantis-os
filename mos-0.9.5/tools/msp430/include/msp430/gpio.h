#include <msp430/iostructures.h>

#ifndef __msp430_headers_gpio_h
#define __msp430_headers_gpio_h

/* gpio.h
 *
 * mspgcc project: MSP430 device headers
 * GPIO module header
 *
 * (c) 2002 by M. P. Ashton <data@ieee.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: gpio.h,v 1.2 2002/12/10 10:46:33 diwil Exp $
 */

/* Switches:

__msp430_have_port0 - if device has port 0
__msp430_have_port1 - if device has port 1
__msp430_have_port2 - if device has port 2
__msp430_have_port3 - if device has port 3
__msp430_have_port4 - if device has port 4
__msp430_have_port5 - if device has port 5
__msp430_have_port6 - if device has port 6

*/

#ifdef __msp430_have_port0
#define P0IN_               0x0010  /* Port 0 Input */
sfrb(P0IN,P0IN_);
#define P0IN_0              0x01
#define P0IN_1              0x02
#define P0IN_2              0x04
#define P0IN_3              0x08
#define P0IN_4              0x10
#define P0IN_5              0x20
#define P0IN_6              0x40
#define P0IN_7              0x80

#define P0OUT_              0x0011  /* Port 0 Output */
sfrb(P0OUT,P0OUT_);
#define P0OUT_0             0x01
#define P0OUT_1             0x02
#define P0OUT_2             0x04
#define P0OUT_3             0x08
#define P0OUT_4             0x10
#define P0OUT_5             0x20
#define P0OUT_6             0x40
#define P0OUT_7             0x80

#define P0DIR_              0x0012  /* Port 0 Direction */
sfrb(P0DIR,P0DIR_);
#define P0DIR_0             0x01
#define P0DIR_1             0x02
#define P0DIR_2             0x04
#define P0DIR_3             0x08
#define P0DIR_4             0x10
#define P0DIR_5             0x20
#define P0DIR_6             0x40
#define P0DIR_7             0x80

#define P0IFG_              0x0013  /* Port 0 Interrupt Flag */
sfrb(P0IFG,P0IFG_);
/* These two bits are defined in Interrupt Flag 1 */
/* #define P0IFG_0             0x01 */
/* #define P0IFG_1             0x02 */
#define P0IFG_2             0x04
#define P0IFG_3             0x08
#define P0IFG_4             0x10
#define P0IFG_5             0x20
#define P0IFG_6             0x40
#define P0IFG_7             0x80

#define P0IES_              0x0014  /* Port 0 Interrupt Edge Select */
sfrb(P0IES,P0IES_);
#define P0IES_0             0x01
#define P0IES_1             0x02
#define P0IES_2             0x04
#define P0IES_3             0x08
#define P0IES_4             0x10
#define P0IES_5             0x20
#define P0IES_6             0x40
#define P0IES_7             0x80

#define P0IE_               0x0015  /* Port 0 Interrupt Enable */
sfrb(P0IE,P0IE_);
/* These two bits are defined in Interrupt Enable 1 */
/* #define P0IE_0              0x01 */
/* #define P0IE_1              0x02 */
#define P0IE_2              0x04
#define P0IE_3              0x08
#define P0IE_4              0x10
#define P0IE_5              0x20
#define P0IE_6              0x40
#define P0IE_7              0x80
#endif

#ifdef __msp430_have_port1
#define P1IN_               0x0020  /* Port 1 Input */
sfrb (P1IN,P1IN_);
#define P1OUT_              0x0021  /* Port 1 Output */
sfrb (P1OUT,P1OUT_);
#define P1DIR_              0x0022  /* Port 1 Direction */
sfrb (P1DIR,P1DIR_);
#define P1IFG_              0x0023  /* Port 1 Interrupt Flag */
sfrb (P1IFG,P1IFG_);
#define P1IES_              0x0024  /* Port 1 Interrupt Edge Select */
sfrb (P1IES,P1IES_);
#define P1IE_               0x0025  /* Port 1 Interrupt Enable */
sfrb (P1IE,P1IE_);
#define P1SEL_              0x0026  /* Port 1 Selection */
sfrb (P1SEL,P1SEL_);
#endif

#ifdef __msp430_have_port2
#define P2IN_               0x0028  /* Port 2 Input */
sfrb (P2IN,P2IN_);
#define P2OUT_              0x0029  /* Port 2 Output */
sfrb (P2OUT,P2OUT_);
#define P2DIR_              0x002A  /* Port 2 Direction */
sfrb (P2DIR,P2DIR_);
#define P2IFG_              0x002B  /* Port 2 Interrupt Flag */
sfrb (P2IFG,P2IFG_);
#define P2IES_              0x002C  /* Port 2 Interrupt Edge Select */
sfrb (P2IES,P2IES_);
#define P2IE_               0x002D  /* Port 2 Interrupt Enable */
sfrb (P2IE,P2IE_);
#define P2SEL_              0x002E  /* Port 2 Selection */
sfrb (P2SEL,P2SEL_);
#endif

#ifdef __msp430_have_port3
#define P3IN_               0x0018  /* Port 3 Input */
sfrb ( P3IN ,P3IN_);
#define P3OUT_              0x0019  /* Port 3 Output */
sfrb ( P3OUT   ,P3OUT_);
#define P3DIR_              0x001A  /* Port 3 Direction */
sfrb ( P3DIR   ,P3DIR_);
#define P3SEL_              0x001B  /* Port 3 Selection */
sfrb ( P3SEL   ,P3SEL_);
#endif

#ifdef __msp430_have_port4
#define P4IN_               0x001C  /* Port 4 Input */
sfrb(P4IN,P4IN_);
#define P4OUT_              0x001D  /* Port 4 Output */
sfrb(P4OUT,P4OUT_);
#define P4DIR_              0x001E  /* Port 4 Direction */
sfrb(P4DIR,P4DIR_);
#define P4SEL_              0x001F  /* Port 4 Selection */
sfrb(P4SEL,P4SEL_);
#endif

#ifdef __msp430_have_port5
#define P5IN_               0x0030  /* Port 5 Input */
sfrb(P5IN,P5IN_);
#define P5OUT_              0x0031  /* Port 5 Output */
sfrb(P5OUT,P5OUT_);
#define P5DIR_              0x0032  /* Port 5 Direction */
sfrb(P5DIR,P5DIR_);
#define P5SEL_              0x0033  /* Port 5 Selection */
sfrb(P5SEL,P5SEL_);
#endif

#ifdef __msp430_have_port6
#define P6IN_               0x0034  /* Port 6 Input */
sfrb(P6IN,P6IN_);
#define P6OUT_              0x0035  /* Port 6 Output */
sfrb(P6OUT,P6OUT_);
#define P6DIR_              0x0036  /* Port 6 Direction */
sfrb(P6DIR,P6DIR_);
#define P6SEL_              0x0037  /* Port 6 Selection */
sfrb(P6SEL,P6SEL_);
#endif

#endif
