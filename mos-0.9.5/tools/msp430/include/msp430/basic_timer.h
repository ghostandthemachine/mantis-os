
#ifndef __msp430_headers_basic_timer_h
#define __msp430_headers_basic_timer_h

/* basic_timer.h
 *
 * mspgcc project: MSP430 device headers
 * BASIC_TIMER module header
 *
 * (c) 2002 by M. P. Ashton <data@ieee.org>
 * Originally based in part on work by Texas Instruments Inc.
 *
 * $Id: basic_timer.h,v 1.2 2002/12/28 06:56:48 coppice Exp $
 */

/* Switches: none */

#define BTCTL_              0x0040  /* Basic Timer Control */
sfrb(BTCTL,BTCTL_);

/* The bit names have been prefixed with "BT" */
#define BTIP0               0x01
#define BTIP1               0x02
#define BTIP2               0x04
#define BTFRFQ0             0x08
#define BTFRFQ1             0x10
#define BTDIV               0x20                        /* fCLK2 = ACLK:256 */
#define BTRESET             0x40                        /* BT is reset and BTIFG is reset if this bit is set */
#define BTHOLD              0x40                        /* BT1 is held if this bit is set */
#define BTSSEL              0x80                        /* fBT = fMCLK (main clock) */

#define BTCNT1_             0x0046  /* Basic Timer Count 1 */
sfrb(BTCNT1,BTCNT1_);
#define BTCNT2_             0x0047  /* Basic Timer Count 2 */
sfrb(BTCNT2,BTCNT2_);

/* Frequency of the BTCNT2 coded with Bit 5 and 7 in BTCTL */
#define BT_fCLK2_ACLK               0x00
#define BT_fCLK2_ACLK_DIV256        BTDIV
#define BT_fCLK2_MCLK               BTSSEL

/* Interrupt interval time fINT coded with Bits 0-2 in BTCTL */
#define BT_fCLK2_DIV2       0                           /* fINT = fCLK2:2 (default) */
#define BT_fCLK2_DIV4       (BTIP0)                     /* fINT = fCLK2:4 */
#define BT_fCLK2_DIV8       (BTIP1)                     /* fINT = fCLK2:8 */
#define BT_fCLK2_DIV16      (BTIP1|BTIP0)               /* fINT = fCLK2:16 */
#define BT_fCLK2_DIV32      (BTIP2)                     /* fINT = fCLK2:32 */
#define BT_fCLK2_DIV64      (BTIP2|BTIP0)               /* fINT = fCLK2:64 */
#define BT_fCLK2_DIV128     (BTIP2|BTIP1)               /* fINT = fCLK2:128 */
#define BT_fCLK2_DIV256     (BTIP2|BTIP1|BTIP0)         /* fINT = fCLK2:256 */
/* Frequency of LCD coded with Bits 3-4 */
#define BT_fLCD_DIV32       0                           /* fLCD = fACLK:32 (default) */
#define BT_fLCD_DIV64       (BTFRFQ0)                   /* fLCD = fACLK:64 */
#define BT_fLCD_DIV128      (BTFRFQ1)                   /* fLCD = fACLK:128 */
#define BT_fLCD_DIV256      (BTFRFQ1|BTFRFQ0)           /* fLCD = fACLK:256 */
/* LCD frequency values with fBT=fACLK */
#define BT_fLCD_1K          0                           /* fACLK:32 (default) */
#define BT_fLCD_512         (BTFRFQ0)                   /* fACLK:64 */
#define BT_fLCD_256         (BTFRFQ1)                   /* fACLK:128 */
#define BT_fLCD_128         (BTFRFQ1|BTFRFQ0)           /* fACLK:256 */
/* LCD frequency values with fBT=fMCLK */
#define BT_fLCD_31K         (BTSSEL)                    /* fMCLK:32 */
#define BT_fLCD_15_5K       (BTSSEL|BTFRFQ0)            /* fMCLK:64 */
#define BT_fLCD_7_8K        (BTSSEL|BTFRFQ1|BTFRFQ0)    /* fMCLK:256 */
/* With assumed values of fACLK=32KHz, fMCLK=1MHz */
/* fBT=fACLK is thought for longer interval times */
#define BT_ADLY_0_064       0                           /* 0.064ms interval (default) */
#define BT_ADLY_0_125       (BTIP0)                     /* 0.125ms    " */
#define BT_ADLY_0_25        (BTIP1)                     /* 0.25ms     " */
#define BT_ADLY_0_5         (BTIP1|BTIP0)               /* 0.5ms      " */
#define BT_ADLY_1           (BTIP2)                     /* 1ms        " */
#define BT_ADLY_2           (BTIP2|BTIP0)               /* 2ms        " */
#define BT_ADLY_4           (BTIP2|BTIP1)               /* 4ms        " */
#define BT_ADLY_8           (BTIP2|BTIP1|BTIP0)         /* 8ms        " */
#define BT_ADLY_16          (BTDIV)                     /* 16ms       " */
#define BT_ADLY_32          (BTDIV|BTIP0)               /* 32ms       " */
#define BT_ADLY_64          (BTDIV|BTIP1)               /* 64ms       " */
#define BT_ADLY_125         (BTDIV|BTIP1|BTIP0)         /* 125ms      " */
#define BT_ADLY_250         (BTDIV|BTIP2)               /* 250ms      " */
#define BT_ADLY_500         (BTDIV|BTIP2|BTIP0)         /* 500ms      " */
#define BT_ADLY_1000        (BTDIV|BTIP2|BTIP1)         /* 1000ms     " */
#define BT_ADLY_2000        (BTDIV|BTIP2|BTIP1|BTIP0)   /* 2000ms     " */
/* fCLK2=fMCLK (1MHz) is thought for short interval times */
/* the timing for short intervals is more precise than ACLK */
/* NOTE */
/* Be sure that the SCFQCTL-Register is set to 01Fh so that fMCLK=1MHz */
/* Too low interval times result in too interrupts more frequent than the
   processor can handle! */
#define BT_MDLY_0_002       (BTSSEL)                    /* 0.002ms interval       *** interval times */
#define BT_MDLY_0_004       (BTSSEL|BTIP0)              /* 0.004ms    "           *** too short for */
#define BT_MDLY_0_008       (BTSSEL|BTIP1)              /* 0.008ms    "           *** interrupt */
#define BT_MDLY_0_016       (BTSSEL|BTIP1|BTIP0)        /* 0.016ms    "           *** handling */
#define BT_MDLY_0_032       (BTSSEL|BTIP2)              /* 0.032ms    " */
#define BT_MDLY_0_064       (BTSSEL|BTIP2|BTIP0)        /* 0.064ms    " */
#define BT_MDLY_0_125       (BTSSEL|BTIP2|BTIP1)        /* 0.125ms    " */
#define BT_MDLY_0_25        (BTSSEL|BTIP2|BTIP1|BTIP0)  /* 0.25ms     " */

/* Reset/Hold coded with Bits 6-7 in BT(1)CTL */
/* this is for BT */
#define BTRESET_CNT1        (BTRESET)                   /* BTCNT1 is reset while BTRESET is set */
#define BTRESET_CNT1_2      (BTRESET|BTDIV)             /* BTCNT1 .AND. BTCNT2 are reset while ~ is set */
/* this is for BT1 */
#define BTHOLD_CNT1         (BTHOLD)                    /* BTCNT1 is held while BTHOLD is set */
#define BTHOLD_CNT1_2       (BTHOLD|BTDIV)              /* BT1CNT1 .AND. BT1CNT2 are held while ~ is set */

/* INTERRUPT CONTROL BITS */
/* #define BTIE                0x80 */
/* #define BTIFG               0x80 */
/* #define BTME                0x80 */

#endif
