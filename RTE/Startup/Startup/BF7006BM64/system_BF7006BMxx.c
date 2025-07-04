/**************************************************************************//**
 * @file     system_ARMCM0.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM0 Device Series
 * @version  V1.08
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2011 - 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

/*!
    \file  system_BF7006BMxx.c
    \brief system function
*/

/*
    Copyright (C) 2017 Byd

    2022-08-30, V1.0.0, system_BF7006BMxx.c initial version
*/

#include "BF7006BMxx.h"
#include "BF7006BMxx_sysctrl.h"

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYSCLK_32M      ((uint32_t)32000000UL)        /* System frequency 32M HZ   */
#define SYSCLK_16M      ((uint32_t)16000000UL)        /* System frequency 16M HZ   */
#define SYSCLK_12M      ((uint32_t)12000000UL)        /* System frequency 12M HZ   */
#define SYSCLK_8M       ((uint32_t) 8000000UL)        /* System frequency 8M HZ   */
#define XTAL_16M        ((uint32_t)16000000UL)        /* Oscillator frequency 16M HZ   */
#define XTAL_12M        ((uint32_t)12000000UL)        /* Oscillator frequency 12M HZ   */
#define XTAL_8M         ((uint32_t) 8000000UL)        /* Oscillator frequency 8M HZ    */

/* Define XTAL frequency here    */
#define XTAL                XTAL_16M

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSCLK_16M;  /*!< System Clock Frequency (Core Clock)*/

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)                   /* Get Core Clock Frequency */
{
    if(SYS_CLK_SEL == SYS_CLK_XTAL){
        #ifdef XTAL
            SystemCoreClock = XTAL;
        #endif
    }else{
        switch(SYS_CLK_SEL){
        case SYS_CLK_32M:
            SystemCoreClock = (uint32_t)32000000UL;
            break;
        case SYS_CLK_16M:
            SystemCoreClock = (uint32_t)16000000UL;
            break;
        case SYS_CLK_8M:
            SystemCoreClock = (uint32_t)8000000UL;
            break;
        default:
            #ifdef XTAL
                SystemCoreClock = XTAL;
            #endif
            break;
        }
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
           Empty here.
           Initialization should be done in main().
 */
void SystemInit (void)
{

}
