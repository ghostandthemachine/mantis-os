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


/** @file context_switch.h
 * @brief Assembly routines required to preform a context switch.
 */
#ifndef __context_switch_h__
#define __context_switch_h__

#include "plat_dep.h"


//gcc places the return address at offset 0 for the dispatcher function
//here we intercept that by putting the start wrapper at that address
//we decrement by 8 as this is the normal offset for a branch call
#define CONTEXT_SWITCH_PREAMBLE_PUSH_START_WRAPPER()  \
{                                                     \
    asm volatile(                                     \
            "addik %0, %0, -8\n\t"                    \
            "swi %0, r1, 0\n\t"                       \
            "addik r1,r1,-132\n\t"                    \
            "swi %0, r1, 72\n\t"                      \
            "/*swi %0, r1, 76*/\n\t"                  \
            :: "r" (start_wrapper)  );                \
}

#define CONTEXT_SWITCH_PREAMBLE_PUSH_CLEAR_STACK()    \
{                                                     \
    asm volatile("swi r0, r1, 4\n\t" ::);             \
    asm volatile("swi r0, r1, 12\n\t" ::);            \
    asm volatile("swi r0, r1, 16\n\t" ::);            \
    asm volatile("swi r0, r1, 20\n\t" ::);            \
    asm volatile("swi r0, r1, 24\n\t" ::);            \
    asm volatile("swi r0, r1, 28\n\t" ::);            \
    asm volatile("swi r0, r1, 32\n\t" ::);            \
    asm volatile("swi r0, r1, 36\n\t" ::);            \
    asm volatile("swi r0, r1, 40\n\t" ::);            \
    asm volatile("swi r0, r1, 44\n\t" ::);            \
    asm volatile("swi r0, r1, 48\n\t" ::);            \
    asm volatile("swi r0, r1, 52\n\t" ::);            \
    asm volatile("swi r0, r1, 56\n\t" ::);            \
    asm volatile("swi r0, r1, 60\n\t" ::);            \
    asm volatile("swi r0, r1, 64\n\t" ::);            \
    asm volatile("swi r0, r1, 68\n\t" ::);            \
    asm volatile("swi r0, r1, 76\n\t" ::);            \
    asm volatile("swi r0, r1, 80\n\t" ::);            \
    asm volatile("swi r0, r1, 84\n\t" ::);            \
    asm volatile("swi r0, r1, 88\n\t" ::);            \
    asm volatile("swi r0, r1, 92\n\t" ::);            \
    asm volatile("swi r0, r1, 96\n\t" ::);            \
    asm volatile("swi r0, r1, 100\n\t" ::);           \
    asm volatile("swi r0, r1, 104\n\t" ::);           \
    asm volatile("swi r0, r1, 108\n\t" ::);           \
    asm volatile("swi r0, r1, 112\n\t" ::);           \
    asm volatile("swi r0, r1, 116\n\t" ::);           \
    asm volatile("swi r0, r1, 120\n\t" ::);           \
    asm volatile("swi r0, r1, 124\n\t" ::);           \
    asm volatile("swi r0, r1, 128\n\t" ::);           \
    asm volatile("and r31, r31, r0\n\t" ::);          \
    asm volatile("ori r31, r31, 2\n\t                 \
                  swi r31, r1, 8" ::);                \
}


/** @file microblaze/include/context_switch.h
 *  @brief save the necessary registers for a context switch
 * on the microblaze architecture
 *
 * Save current stack pointer
 * Change stack pointer to process stack
 * Push address of start_thread function onto stack
 * Push zeroes for initial register vals and sreg
 * Save adjusted stack ptr to thread struct
 * Restore kernel stack ptr
 */
#define CONTEXT_SWITCH_PREAMBLE()                     \
{                                                     \
    GET_SP(_current_thread->sp);                      \
    stack_pointer_register = stack_addr;              \
    CONTEXT_SWITCH_PREAMBLE_PUSH_START_WRAPPER();     \
    CONTEXT_SWITCH_PREAMBLE_PUSH_CLEAR_STACK();       \
    threads[id].sp = (stackval_t *)stack_pointer_register; \
    stack_pointer_register = _current_thread->sp;     \
}

#define PUSH_THREAD_STACK_PUSH_GENERAL_REGS() \
{ \
    asm volatile("                                    \
            /* Stack general registers. */      \n\t  \
            swi r30, r1, 12                     \n\t  \
            swi r29, r1, 16                     \n\t  \
            swi r28, r1, 20                     \n\t  \
            swi r27, r1, 24                     \n\t  \
            swi r26, r1, 28                     \n\t  \
            swi r25, r1, 32                     \n\t  \
            swi r24, r1, 36                     \n\t  \
            swi r23, r1, 40                     \n\t  \
            swi r22, r1, 44                     \n\t  \
            swi r21, r1, 48                     \n\t  \
            swi r20, r1, 52                     \n\t  \
            swi r19, r1, 56                     \n\t  \
            swi r18, r1, 60                     \n\t  \
            swi r17, r1, 64                     \n\t  \
            swi r16, r1, 68                     \n\t  \
            swi r15, r1, 72                     \n\t  \
            swi r13, r1, 80                     \n\t  \
            swi r12, r1, 84                     \n\t  \
            swi r11, r1, 88                     \n\t  \
            swi r10, r1, 92                     \n\t  \
            swi r9, r1, 96                      \n\t  \
            swi r8, r1, 100                     \n\t  \
            swi r7, r1, 104                     \n\t  \
            swi r6, r1, 108                     \n\t  \
            swi r5, r1, 112                     \n\t  \
            swi r4, r1, 116                     \n\t  \
            swi r3, r1, 120                     \n\t  \
            swi r2, r1, 124                     \n\t  \
            /*swi r1, r1, 128 */                \n\t  \
    " ); \
}

#define PUSH_THREAD_STACK_PREAMBLE() \
{ \
    asm volatile("                                   \
        /* Make room for the context on the stack. */\n\t          \
        addik r1, r1, -132                           \n\t          \
        /* Save r31 so it can then be used. */       \n\t          \
        swi r31, r1, 4                               \n\t          \
        /* Copy the msr into r31 - this is stacked later. */\n\t   \
        mfs r31, rmsr                                       \n\t   \
        " ); \
}

#define PUSH_THREAD_STACK_PUSH_SR() \
{ \
     asm volatile("                    \
         swi r14, r1, 76         \n\t  \
         ori r31, r31, 2         \n\t  \
         swi r31, r1, 8                \
         ");\
}


/** @brief save the current thread's context to the stack
 * Save all the registers
 * Save SREG
 * Push the stack pointer
 * Taken directly from FreeRTOS
 */
#define PUSH_THREAD_STACK() \
{ \
    PUSH_THREAD_STACK_PREAMBLE();           \
    PUSH_THREAD_STACK_PUSH_GENERAL_REGS();  \
    PUSH_THREAD_STACK_PUSH_SR();            \
    GET_SP(_current_thread->sp);            \
}

/** @brief retrieve a thread and context from the stack
 * Restore the stack pointer
 * Restore SREG
 * Restore the other registers
 */


#define POP_THREAD_STACK_RESTORE_GENERAL_REGS() \
{                                                \
asm volatile("                       \
        lwi r31, r1, 4         \n\t  \
        lwi r30, r1, 12        \n\t  \
        lwi r29, r1, 16        \n\t  \
        lwi r28, r1, 20        \n\t  \
        lwi r27, r1, 24        \n\t  \
        lwi r26, r1, 28        \n\t  \
        lwi r25, r1, 32        \n\t  \
        lwi r24, r1, 36        \n\t  \
        lwi r23, r1, 40        \n\t  \
        lwi r22, r1, 44        \n\t  \
        lwi r21, r1, 48        \n\t  \
        lwi r20, r1, 52        \n\t  \
        lwi r19, r1, 56        \n\t  \
        lwi r18, r1, 60        \n\t  \
        lwi r17, r1, 64        \n\t  \
        lwi r16, r1, 68        \n\t  \
        lwi r15, r1, 72        \n\t  \
        lwi r14, r1, 76        \n\t  \
        lwi r13, r1, 80        \n\t  \
        lwi r12, r1, 84        \n\t  \
        lwi r11, r1, 88        \n\t  \
        lwi r10, r1, 92        \n\t  \
        lwi r9,  r1, 96         \n\t  \
        lwi r8,  r1, 100        \n\t  \
        lwi r7,  r1, 104        \n\t  \
        lwi r6,  r1, 108        \n\t  \
        lwi r5,  r1, 112        \n\t  \
        lwi r4,  r1, 116        \n\t  \
        lwi r2,  r1, 124        \n\t");  \
}

#define POP_THREAD_STACK_OBTAIN_MSR_FROM_STACK() \
{                                                \
    asm volatile("lwi r3, r1, 8\n\t");           \
}

#define POP_THREAD_STACK_RETURN_NORMALLY() \
{                                          \
    asm volatile("                         \
    mts rmsr, r3                     \n\t  \
    lwi r3, r1, 120                  \n\t  \
    addik r1, r1, 132                \n\t  \
    " );                                   \
}
//checks to see if interrupts were enabled in the thread
//we are popping's status register
//if the interrupts were enabled, we wait to enable them until
//after we have finished popping the stack
#define POP_THREAD_STACK_HANDLE_RETURN1()      \
{                                             \
    asm volatile("                       \
            andi r3, r3, 2                                       \n\t  \
            beqid r3, 36                                         \n\t  \
            or r0, r0, r0                                        \n\t  \
            " );                         \
}


//NOTE1:
//the stack is increased again by 132 since this was what was subtracted
//s.t. we had room to push the state on to the stack.
//An extra 32 is added since the dispatcher loads 32bytes of local
//somehow we must make this function not have any local variables.
//
//NOTE2:
//The register 14 is loaded with register 15 in the context switch

//skips over the next block if interrups were disabled
//if interrupts were enabled, it waits to enable interrupts
//until after we return from this function
#define POP_THREAD_STACK_HANDLE_RETURN2()      \
{                                             \
    asm volatile("                       \
            lwi r3, r1, 8                                        \n\t  \
            andi r3, r3, ~2                                      \n\t  \
            mts rmsr, r3                                         \n\t  \
            lwi r3, r1, 120                                      \n\t  \
            addik r1, r1, 132                                    \n\t  \
            rtid r14, 0                                          \n\t  \
            or r0, r0, r0                                        \n\t  \
            " );                                                       \
}

//interrupts were disabled, so return normally, i.e. without
//enabling interrupts on return
#define POP_THREAD_STACK_HANDLE_RETURN3()          \
{                                                  \
    asm volatile("                                 \
           lwi r3, r1, 8                     \n\t  \
           mts rmsr, r3                      \n\t  \
           lwi r3, r1, 120                   \n\t  \
           addik r1, r1, 132                 \n\t  \
      /*   rtsd r14, 0         */            \n\t  \
      /*   or r0, r0, r0       */            \n\t  \
           ");                                     \
}

#define POP_THREAD_STACK()                      \
{                                               \
    stack_pointer_register = (register_type_t)_current_thread->sp; \
    POP_THREAD_STACK_RESTORE_GENERAL_REGS();    \
    POP_THREAD_STACK_OBTAIN_MSR_FROM_STACK();   \
    POP_THREAD_STACK_RETURN_NORMALLY();         \
}
//POP_THREAD_STACK_HANDLE_RETURN1();
//POP_THREAD_STACK_HANDLE_RETURN2();
//POP_THREAD_STACK_HANDLE_RETURN3();

#endif


