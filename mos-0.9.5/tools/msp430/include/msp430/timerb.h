#ifndef __msp430_headers_timerb_h
#define __msp430_headers_timerb_h

/* timerb.h
 *
 * mspgcc project: MSP430 device headers
 * TIMERB module header
 *
 * (c) 2002 by M. P. Ashton <data@ieee.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: timerb.h,v 1.8 2004/01/28 22:25:30 cliechti Exp $
 */

/* Switches:

__msp430_have_timerb7 - if timer B has 7 capture/compare registers (default is 3)

*/

#define TBIV_               0x011E  /* Timer B Interrupt Vector Word */
sfrw(TBIV,TBIV_);
#define TBCTL_              0x0180  /* Timer B Control */
sfrw(TBCTL,TBCTL_);
#define TBCCTL0_            0x0182  /* Timer B Capture/Compare Control 0 */
sfrw(TBCCTL0,TBCCTL0_);
#define TBCCTL1_            0x0184  /* Timer B Capture/Compare Control 1 */
sfrw(TBCCTL1,TBCCTL1_);
#define TBCCTL2_            0x0186  /* Timer B Capture/Compare Control 2 */
sfrw(TBCCTL2,TBCCTL2_);
#define TBR_                0x0190  /* Timer B */
sfrw(TBR,TBR_);
#define TBCCR0_             0x0192  /* Timer B Capture/Compare 0 */
sfrw(TBCCR0,TBCCR0_);
#define TBCCR1_             0x0194  /* Timer B Capture/Compare 1 */
sfrw(TBCCR1,TBCCR1_);
#define TBCCR2_             0x0196  /* Timer B Capture/Compare 2 */
sfrw(TBCCR2,TBCCR2_);

#if defined(__msp430_have_timerb7)

#define TBCCTL3_            0x0188  /* Timer B Capture/Compare Control 3 */
sfrw(TBCCTL3,TBCCTL3_);
#define TBCCTL4_            0x018A  /* Timer B Capture/Compare Control 4 */
sfrw(TBCCTL4,TBCCTL4_);
#define TBCCTL5_            0x018C  /* Timer B Capture/Compare Control 5 */
sfrw(TBCCTL5,TBCCTL5_);
#define TBCCTL6_            0x018E  /* Timer B Capture/Compare Control 6 */
sfrw(TBCCTL6,TBCCTL6_);
#define TBCCR3_             0x0198  /* Timer B Capture/Compare 3 */
sfrw(TBCCR3,TBCCR3_);
#define TBCCR4_             0x019A  /* Timer B Capture/Compare 4 */
sfrw(TBCCR4,TBCCR4_);
#define TBCCR5_             0x019C  /* Timer B Capture/Compare 5 */
sfrw(TBCCR5,TBCCR5_);
#define TBCCR6_             0x019E  /* Timer B Capture/Compare 6 */
sfrw(TBCCR6,TBCCR6_);

#endif

#ifndef _GNU_ASSEMBLER_
/* Structured declaration */
typedef struct {
  volatile unsigned
    tbifg:1,
    tbie:1,
    tbclr:1,
    dummy1:1,
    tbmc:2,
    tbid:2,
    tbssel:2,
    dummy2:1,
    tbcntl:2,
    tbclgrp:2;
} __attribute__ ((packed)) tbctl_t;

typedef struct {
  volatile unsigned
    ccifg:1,
    cov:1,
    out:1,
    cci:1,
    ccie:1,
    outmod:3,
    cap:1,
    clld:2,
    scs:1,
    ccis:2,
    cm:2;
} __attribute__ ((packed)) tbcctl_t;

/* The timer B declaration itself */
struct timerb_t {
  tbctl_t ctl;
  tbcctl_t cctl0;
  tbcctl_t cctl1;
  tbcctl_t cctl2;
#if defined(__msp430_have_timerb7)
  tbcctl_t cctl3;
  tbcctl_t cctl4;
  tbcctl_t cctl5;
  tbcctl_t cctl6;
#else
  volatile unsigned dummy[4];   /* Pad to the next group of registers */
#endif
  volatile unsigned tbr;
  volatile unsigned tbccr0;
  volatile unsigned tbccr1;
  volatile unsigned tbccr2;
#if defined(__msp430_have_timerb7)
  volatile unsigned tbccr3;
  volatile unsigned tbccr4;
  volatile unsigned tbccr5;
  volatile unsigned tbccr6;
#endif
};

#ifdef __cplusplus
extern "C" struct timerb_t timerb asm("0x0180");
#else //__cplusplus
struct timerb_t timerb asm("0x0180");
#endif //__cplusplus

#endif

#define SHR1                0x4000  /* Timer B compare latch load group 1 */
#define SHR0                0x2000  /* Timer B compare latch load group 0 */
#define TBCLGRP1            0x4000  /* Timer B compare latch load group 1 */
#define TBCLGRP0            0x2000  /* Timer B compare latch load group 0 */
#define CNTL1               0x1000  /* Counter length 1 */
#define CNTL0               0x0800  /* Counter length 0 */
#define TBSSEL2             0x0400  /* unused */
#define TBSSEL1             0x0200  /* Clock source 1 */
#define TBSSEL0             0x0100  /* Clock source 0 */
#define TBCLR               0x0004  /* Timer B counter clear */
#define TBIE                0x0002  /* Timer B interrupt enable */
#define TBIFG               0x0001  /* Timer B interrupt flag */

#define TBSSEL_0            (0<<8)  /* Clock source: TBCLK */
#define TBSSEL_1            (1<<8)  /* Clock source: ACLK  */
#define TBSSEL_2            (2<<8)  /* Clock source: SMCLK */
#define TBSSEL_3            (3<<8)  /* Clock source: INCLK */
#define CNTL_0              (0<<11) /* Counter length: 16 bit */
#define CNTL_1              (1<<11) /* Counter length: 12 bit */
#define CNTL_2              (2<<11) /* Counter length: 10 bit */
#define CNTL_3              (3<<11) /* Counter length:  8 bit */
#define SHR_0               (0<<13) /* Timer B Group: 0 - individually */
#define SHR_1               (1<<13) /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define SHR_2               (2<<13) /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define SHR_3               (3<<13) /* Timer B Group: 3 - 1 group (all) */
#define TBCLGRP_0           (0<<13) /* Timer B Group: 0 - individually */
#define TBCLGRP_1           (1<<13) /* Timer B Group: 1 - 3 groups (1-2, 3-4, 5-6) */
#define TBCLGRP_2           (2<<13) /* Timer B Group: 2 - 2 groups (1-3, 4-6)*/
#define TBCLGRP_3           (3<<13) /* Timer B Group: 3 - 1 group (all) */

/* Additional Timer B Control Register bits are defined in Timer A */

#define SLSHR1              0x0400  /* Compare latch load source 1 */
#define SLSHR0              0x0200  /* Compare latch load source 0 */
#define CLLD1               0x0400  /* Compare latch load source 1 */
#define CLLD0               0x0200  /* Compare latch load source 0 */

#define SLSHR_0             (0<<9)  /* Compare latch load source 0 - immediate */
#define SLSHR_1             (1<<9)  /* Compare latch load source 1 - TBR counts to 0 */
#define SLSHR_2             (2<<9)  /* Compare latch load source 2 - up/down */
#define SLSHR_3             (3<<9)  /* Compare latch load source 3 - TBR counts to TBCTL0 */

#define CLLD_0              (0<<9)  /* Compare latch load source 0 - immediate */
#define CLLD_1              (1<<9)  /* Compare latch load source 1 - TBR counts to 0 */
#define CLLD_2              (2<<9)  /* Compare latch load source 2 - up/down */
#define CLLD_3              (3<<9)  /* Compare latch load source 3 - TBR counts to TBCTL0 */

/* Aliases by mspgcc */
#define TBSSEL_TBCLK        TBSSEL_0
#define TBSSEL_ACLK         TBSSEL_1
#define TBSSEL_SMCLK        TBSSEL_2
#define TBSSEL_INCLK        TBSSEL_3

#endif
