/* Copyright (c) 2004 Eric B. Weddington
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/* $Id: iom165.h,v 1.2.2.2 2005/07/19 15:02:13 aesok Exp $ */

/* avr/iom165.h - definitions for ATmega165 */

#ifndef _AVR_IOM165_H_
#define _AVR_IOM165_H_ 1

/* This file should only be included from <avr/io.h>, never directly. */

#ifndef _AVR_IO_H_
#  error "Include <avr/io.h> instead of this file."
#endif

#ifndef _AVR_IOXXX_H_
#  define _AVR_IOXXX_H_ "iom165.h"
#else
#  error "Attempt to include more than one <avr/ioXXX.h> file."
#endif 

/* Registers and associated bit numbers */

/* The bit numbers for the Port A-G registers are defined in <avr/portpins.h> */
#define PINA    _SFR_IO8(0X00)
#define DDRA    _SFR_IO8(0X01)
#define PORTA   _SFR_IO8(0X02)

#define PINB    _SFR_IO8(0X03)
#define DDRB    _SFR_IO8(0x04)
#define PORTB   _SFR_IO8(0x05)

#define PINC    _SFR_IO8(0x06)
#define DDRC    _SFR_IO8(0x07)
#define PORTC   _SFR_IO8(0x08)

#define PIND    _SFR_IO8(0x09)
#define DDRD    _SFR_IO8(0x0A)
#define PORTD   _SFR_IO8(0x0B)

#define PINE    _SFR_IO8(0x0C)
#define DDRE    _SFR_IO8(0x0D)
#define PORTE   _SFR_IO8(0x0E)

#define PINF    _SFR_IO8(0x0F)
#define DDRF    _SFR_IO8(0x10)
#define PORTF   _SFR_IO8(0x11)

#define PING    _SFR_IO8(0x12)
#define DDRG    _SFR_IO8(0x13)
#define PORTG   _SFR_IO8(0x14)


#define TIFR0   _SFR_IO8(0x15)
#define TOV0    0
#define OCF0A   1

#define TIFR1   _SFR_IO8(0x16)
#define TOV1    0
#define OCF1A   1
#define OCF1B   2
#define ICF1    5

#define TIFR2   _SFR_IO8(0x17)
#define TOV2    0
#define OCF2A   1

/* Reserved [0x18..0x1B] */

#define EIFR   _SFR_IO8(0x1C)
#define INTF0   0
#define PCIF0   6
#define PCIF1   7

#define EIMSK   _SFR_IO8(0x1D)
#define INT0    0
#define PCIE0   6
#define PCIE1   7

#define GPIOR0  _SFR_IO8(0x1E)

#define EECR    _SFR_IO8(0x1F)
#define EERE    0
#define EEWE    1
#define EEMWE   2
#define EERIE   3

#define EEDR    _SFR_IO8(0X20)

/* Combine EEARL and EEARH */
#define EEAR    _SFR_IO16(0x21)
#define EEARL   _SFR_IO8(0x21)
#define EEARH   _SFR_IO8(0X22)

#define GTCCR   _SFR_IO8(0x23)
#define PSR10   0
#define PSR2    1
#define TSM     7

#define TCCR0A  _SFR_IO8(0x24)
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM0A0  4
#define COM0A1  5
#define WGM00   6
#define FOC0A   7

/* Reserved [0x25] */

#define TCNT0   _SFR_IO8(0X26)

#define OCR0A   _SFR_IO8(0X27)

/* Reserved [0x28..0x29] */

#define GPIOR1  SFR_IO8(0x2A)

#define GPIOR2  SFR_IO8(0x2B)

#define SPCR    SFR_IO8(0x2C)
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

#define SPSR    SFR_IO8(0x2D)
#define SPI2X   0
#define WCOL    6
#define SPIF    7

#define SPDR    SFR_IO8(0X2E)

/* Reserved [0x2F] */

#define ACSR    SFR_IO8(0x30)
#define ACIS0   0
#define ACIS1   1
#define ACIC    2
#define ACIE    3
#define ACI     4
#define ACO     5
#define ACBG    6
#define ACD     7

#define OCDR    SFR_IO8(0x31)
#define OCDR0   0
#define OCDR1   1
#define OCDR2   2
#define OCDR3   3
#define OCDR4   4
#define OCDR5   5
#define OCDR6   6
#define OCD     7   // The datasheet defines this but IMO it should be OCDR7.
#define OCDR7   7
#define IDRD    7

/* Reserved [0x32] */

#define SMCR    _SFR_IO8(0x33)
#define SE      0
#define SM0     1
#define SM1     2
#define SM2     3

#define MCUSR   _SFR_IO8(0x34)
#define PORF    0
#define EXTRF   1
#define BORF    2
#define WDRF    3
#define JTRF    4

#define MCUCR   _SFR_IO8(0X35)
#define IVCE    0
#define IVSEL   1
#define PUD     4
#define JTD     7

/* Reserved [0x36] */

#define SPMCSR  _SFR_IO8(0x37)
#define SPMEN   0
#define PGERS   1
#define PGWRT   2
#define BLBSET  3
#define RWWSRE  4
#define RWWSB   6
#define SPMIE   7

/* Reserved [0x38..0x3C] */

/* SP [0x3D..0x3E] */
/* SREG [0x3F] */

#define WDTCR   _SFR_MEM8(0x60)
#define WDP0    0
#define WDP1    1
#define WDP2    2
#define WDE     3
#define WDCE    4

#define CLKPR   _SFR_MEM8(0x61)
#define CLKPS0  0
#define CLKPS1  1
#define CLKPS2  2
#define CLKPS3  3
#define CLKPCE  7

/* Reserved [0x62..0x63] */

#define PRR     _SFR_MEM8(0x64)
#define PRADC       0
#define PRUSART0    1
#define PRSPI       2
#define PRTIM1      3

/* Reserved [0x65] */

#define OSCCAL  _SFR_MEM8(0x66)

/* Reserved [0x67..0x68] */

#define EICRA   _SFR_MEM8(0x69)
#define ISC00   0
#define ISC01   1

/* Reserved [0x6A] */

/* Combine PCMSK0 and PCMSK1 */
#define PCMSK   _SFR_MEM16(0x6B)

#define PCMSK0  _SFR_MEM8(0x6B)
#define PCINT0  0
#define PCINT1  1
#define PCINT2  2
#define PCINT3  3
#define PCINT4  4
#define PCINT5  5
#define PCINT6  6
#define PCINT7  7

#define PCMSK1  _SFR_MEM8(0x6C)
#define PCINT8  0
#define PCINT9  1
#define PCINT10 2
#define PCINT11 3
#define PCINT12 4
#define PCINT13 5
#define PCINT14 6
#define PCINT15 7

/* Reserved [0x6D] */

#define TIMSK0  _SFR_MEM8(0x6E)
#define TOIE0   0
#define OCIE0A  1

#define TIMSK1  _SFR_MEM8(0x6F)
#define TOIE1   0
#define OCIE1A  1
#define OCIE1B  2
#define ICIE1   5

#define TIMSK2  _SFR_MEM8(0x70)
#define TOIE2   0
#define OCIE2A  1

/* Reserved [0x71..0x77] */

/* Combine ADCL and ADCH */
#ifndef __ASSEMBLER__
#define ADC     _SFR_MEM16(0x78)
#endif
#define ADCW    _SFR_MEM16(0x78)
#define ADCL    _SFR_MEM8(0x78)
#define ADCH    _SFR_MEM8(0x79)

#define ADCSRA  _SFR_MEM8(0x7A)
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADATE   5
#define ADSC    6
#define ADEN    7

#define ADCSRB  _SFR_MEM8(0x7B)
#define ADTS0   0
#define ADTS1   1
#define ADTS2   2
#define ACME    6

#define ADMUX   _SFR_MEM8(0x7C)
#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5
#define REFS0   6
#define REFS1   7

/* Reserved [0x7D] */

#define DIDR0   _SFR_MEM8(0x7E)
#define ADC0D   0
#define ADC1D   1
#define ADC2D   2
#define ADC3D   3
#define ADC4D   4
#define ADC5D   5
#define ADC6D   6
#define ADC7D   7

#define DIDR1   _SFR_MEM8(0x7F)
#define AIN0D   0
#define AIN1D   1

#define TCCR1A  _SFR_MEM8(0X80)
#define WGM10   0
#define WGM11   1
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define TCCR1B  _SFR_MEM8(0X81)
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define TCCR1C  _SFR_MEM8(0x82)
#define FOC1B   6
#define FOC1A   7

/* Reserved [0x83] */

/* Combine TCNT1L and TCNT1H */
#define TCNT1   _SFR_MEM16(0x84)

#define TCNT1L  _SFR_MEM8(0x84)
#define TCNT1H  _SFR_MEM8(0x85)

/* Combine ICR1L and ICR1H */
#define ICR1    _SFR_MEM16(0x86)

#define ICR1L   _SFR_MEM8(0x86)
#define ICR1H   _SFR_MEM8(0x87)

/* Combine OCR1AL and OCR1AH */
#define OCR1A   _SFR_MEM16(0x88)

#define OCR1AL  _SFR_MEM8(0x88)
#define OCR1AH  _SFR_MEM8(0x89)

/* Combine OCR1BL and OCR1BH */
#define OCR1B   _SFR_MEM16(0x8A)

#define OCR1BL  _SFR_MEM8(0x8A)
#define OCR1BH  _SFR_MEM8(0x8B)

/* Reserved [0x8C..0xAF] */

#define TCCR2A  _SFR_MEM8(0xB0)
#define CS20    0
#define CS21    1
#define CS22    2
#define WGM21   3
#define COM2A0  4
#define COM2A1  5
#define WGM20   6
#define FOC2A   7

/* Reserved [0xB1] */

#define TCNT2   _SFR_MEM8(0xB2)

#define OCR2A   _SFR_MEM8(0xB3)

/* Reserved [0xB4..0xB5] */

#define ASSR    _SFR_MEM8(0xB6)
#define TCR2UB  0
#define OCR2UB  1
#define TCN2UB  2
#define AS2     3
#define EXCLK   4

/* Reserved [0xB7] */

#define USICR   _SFR_MEM8(0xB8)
#define USITC   0
#define USICLK  1
#define USICS0  2
#define USICS1  3
#define USIWM0  4
#define USIWM1  5
#define USIOIE  6
#define USISIE  7

#define USISR   _SFR_MEM8(0xB9)
#define USICNT0 0
#define USICNT1 1
#define USICNT2 2
#define USICNT3 3
#define USIDC   4
#define USIPF   5
#define USIOIF  6
#define USISIF  7

#define USIDR   _SFR_MEM8(0xBA)

/* Reserved [0xBB..0xBF] */

#define UCSRA   _SFR_MEM8(0xC0)
#define MPCM    0
#define U2X     1
#define UPE     2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UCSRB   _SFR_MEM8(0XC1)
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSRC   _SFR_MEM8(0xC2)
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6

/* Reserved [0xC3] */

/* Combine UBRRL and UBRRH */
#define UBRR    _SFR_MEM16(0xC4)

#define UBRRL   _SFR_MEM8(0xC4)
#define UBRRH   _SFR_MEM8(0xC5)

#define UDR     _SFR_MEM8(0XC6)

/* Reserved [0xC7..0xFF] */


/* Interrupt vectors */
/* Vector 0 is the reset vector */
#define SIG_INTERRUPT0          _VECTOR(1)
#define SIG_PIN_CHANGE0         _VECTOR(2)
#define SIG_PIN_CHANGE1         _VECTOR(3)
#define SIG_OUTPUT_COMPARE2     _VECTOR(4)
#define SIG_OVERFLOW2           _VECTOR(5)
#define SIG_INPUT_CAPTURE1      _VECTOR(6)
#define SIG_OUTPUT_COMPARE1A    _VECTOR(7)
#define SIG_OUTPUT_COMPARE1B    _VECTOR(8)
#define SIG_OVERFLOW1           _VECTOR(9)
#define SIG_OUTPUT_COMPARE0     _VECTOR(10)
#define SIG_OVERFLOW0           _VECTOR(11)
#define SIG_SPI                 _VECTOR(12)
#define SIG_UART_RECV           _VECTOR(13)
#define SIG_UART_DATA           _VECTOR(14)
#define SIG_UART_TRANS          _VECTOR(15)
#define SIG_USI_START           _VECTOR(16)
#define SIG_USI_OVERFLOW        _VECTOR(17)
#define SIG_COMPARATOR          _VECTOR(18)
#define SIG_ADC                 _VECTOR(19)
#define SIG_EEPROM_READY        _VECTOR(20)
#define SIG_SPM_READY           _VECTOR(21)

#define _VECTORS_SIZE 88


/* Constants */
#define SPM_PAGESIZE    128
#define RAMEND          0x4FF
#define XRAMEND         0x4FF
#define E2END           0x1FF
#define FLASHEND        0x3FFF

#endif /* _AVR_IOM165_H_ */
