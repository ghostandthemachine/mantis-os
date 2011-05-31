//  This file is part of MOS, the MANTIS Operating System
//  See http://mantis.cs.colorado.edu/
//
//  Copyright (c) 2002 - 2007 University of Colorado, Boulder
//
//   All rights reserved.
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are
//   met:
//
//       * Redistributions of source code must retain the above copyright
//         notice, this list of conditions and the following disclaimer.
//       * Redistributions in binary form must reproduce the above
//         copyright notice, this list of conditions and the following
//         disclaimer in the documentation and/or other materials provided
//         with the distribution. 
//       * Neither the name of the MANTIS Project nor the names of its
//         contributors may be used to endorse or promote products derived
//         from this software without specific prior written permission.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//   POSSIBILITY OF SUCH DAMAGE.

/**
  Project Mantis
  File:   terminal.h
  Authors: Charles Gruenwald III : gruenwal@colorado.edu
  Date:   03-12-2004
  
**/

/** @file terminal.h
 * @brief Terminal driver for stdin and stdout - xmos processes
 * @author Charles Gruenwald III
 * @date 03/12/2004
 */

#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "com.h"

/** @brief Setup the serial port and register with the com layer. */
uint8_t terminal_init(void);
/** @brief Send the buffer to the terminal. 
 * @param buf Buffer to use 
 */
uint8_t terminal_send(comBuf *buf);
/** @brief Not implemented.
 *
 * In linux this function is very important because we don't
 * have any low power functionality, but you still must set
 * to listen mode if you want to get packets. 
 * @param mode 
 */
uint8_t terminal_mode(uint8_t mode);
/** @brief Not implemented.
 *
 * Generic control function for doing things like changing the
 *  properties of the serial connection etc... 
 */
uint8_t terminal_ioctl(uint8_t request, va_list ap);

#endif
