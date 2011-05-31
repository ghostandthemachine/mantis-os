/*
 * Copyright (c) 2001 Dmitry Dicky diwil@eis.ru
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS `AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: io.h,v 1.13 2005/03/11 15:49:49 coppice Exp $
 */

#ifndef _IO_H_
#define _IO_H_

#if defined(__MSP430_1101__) || defined(__MSP430_1111__) || defined(__MSP430_1121__)
#include <msp430x11x1.h>

#elif defined(__MSP430_110__) || defined(__MSP430_112__)
#include <msp430x11x.h>

#elif defined(__MSP430_122__) || defined(__MSP430_123__)
#include <msp430x12x.h>

#elif defined(__MSP430_1122__) || defined(__MSP430_1132__)
#include <msp430x11x2.h>

#elif defined(__MSP430_1222__) || defined(__MSP430_1232__)
#include <msp430x12x2.h>

#elif defined(__MSP430_133__) || defined(__MSP430_135__)
#include <msp430x13x.h>

#elif defined(__MSP430_147__) || defined(__MSP430_148__) || defined(__MSP430_149__)
#include <msp430x14x.h>

#elif defined(__MSP430_1331__) || defined(__MSP430_1351__)
#include <msp430x13x1.h>

#elif defined(__MSP430_1471__) || defined(__MSP430_1481__) || defined(__MSP430_1491__)
#include <msp430x14x1.h>

#elif defined(__MSP430_155__) || defined(__MSP430_156__) || defined(__MSP430_157__)
#include <msp430x15x.h>

#elif defined(__MSP430_167__) || defined(__MSP430_168__) || defined(__MSP430_169__) || defined(__MSP430_1610__) || defined(__MSP430_1611__) || defined(__MSP430_1612__)
#include <msp430x16x.h>

#elif defined(__MSP430_2101__) || defined(__MSP430_2111__) || defined(__MSP430_2121__) || defined(__MSP430_2131__)
#include <msp430x21x1.h>

#elif defined(__MSP430_311__) || defined(__MSP430_312__) || defined(__MSP430_313__) || defined(__MSP430_314__) || defined(__MSP430_315__)
#include <msp430x31x.h>

#elif defined(__MSP430_323__) || defined(__MSP430_325__)
#include <msp430x32x.h>

#elif defined(__MSP430_336__) || defined(__MSP430_337__)
#include <msp430x33x.h>

#elif defined(__MSP430_412__) || defined(__MSP430_413__) || defined(__MSP430_415__) || defined(__MSP430_417__)
#include <msp430x41x.h>

#elif defined(__MSP430_423__) || defined(__MSP430_425__) || defined(__MSP430_427__)
#include <msp430x42x.h>

#elif defined(__MSP430_4250__) || defined(__MSP430_4260__) || defined(__MSP430_4270__)
#include <msp430x42x0.h>

#elif defined(__MSP430_E423__) || defined(__MSP430_E425__) || defined(__MSP430_E427__)
#include <msp430xE42x.h>

#elif defined(__MSP430_W423__) || defined(__MSP430_W425__) || defined(__MSP430_W427__)
#include <msp430xW42x.h>

#elif defined(__MSP430_G437__) || defined(__MSP430_G438__) || defined(__MSP430_G439__)
#include <msp430xG43x.h>

#elif defined(__MSP430_435__) || defined(__MSP430_436__) || defined(__MSP430_437__)
#include <msp430x43x.h>

#elif defined(__MSP430_447__) || defined(__MSP430_448__) || defined(__MSP430_449__)
#include <msp430x44x.h>

#else
#warning "Unknown arch! Please check"
#include <iomacros.h>
#endif

#endif
