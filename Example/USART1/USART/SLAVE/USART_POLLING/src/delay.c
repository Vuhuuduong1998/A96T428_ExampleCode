/**
 *******************************************************************************
 * @file        delay.c
 * @author      ABOV R&D Division
 * @brief       DELAY Source File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include    "typedef.h"
#include    "Intrins.h"
#include    "delay.h"       //
/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/
/**
* @brief    System NOP 1us Delay rountine. (MCLK = 16MHZ)
* @note     1 machine cycle comprises 2 system clock cycles. (@ABOV 96 Core Serise)
*           16 system clock delay
* @param    None
* @return   None
*/
volatile void NOP_1us_Delay(void)
{
    // ACALL, LCALL : 2 cycle => 4 system clock cycle
    NOP; NOP; NOP; NOP;     // NOP : 1 cycle => 2 sys. clock => 8 sys. clk
    // RET : 2 cycle => 4 system clock cycle
    // 16 sys. clk @16MHZ = 62.5ns x 16 = 1us
}
/**
* @brief    System NOP 10us Delay rountine. (MCLK = 16MHZ)
* @note     1 machine cycle comprises 2 system clock cycles. (@ABOV 96 Core Serise)
*           160 system clock delay
*           1 machine cycle can be added depending on code optimization.
*
*           ex1)    MOV R7,#(Low byte of delay)
*                   MOV R6,#(high byte of delay)
*                   LCALL   NOP_10us_Delay
*
*           ex2)    MOV A,#(Low byte of delay) // Lower byte and higher byte are the same.
*                   MOV R7,A
*                   MOV R6,A
*                   LCALL   NOP_10us_Delay
*
* @param    delay : unsigned int 1~65,355 (delay) * 10us (@System clock = 16Mhz)
* @return   None
*/
volatile void NOP_10us_Delay(unsigned int delay)
{
    // mov r7 <- low byte of delay      // 1cycle
    // mov r6 <- high byte of delay     // 1cycle
    // lcall NOP_10us_Delay             // 2cycle
    
    // dummy assignment to avoid warning
    // 'unreferenced local variable'
    // Reference Link : http://www.keil.com/support/docs/2622.htm
    // delay -> [r6:r7]
    
    delay = delay;  // dummy
                    
    #pragma asm
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        clr     c                           // 1cycle
        mov     a,r7                        // 1cycle
        subb    a,#2                        // 1cycle
        mov     r7,a                        // 1cycle
        mov     a,r6                        // 1cycle
        subb    a,#0                        // 1cycle
        mov     r6,a                        // 1cycle
        jc     _nop_10us_delay_loop_end     // 2cycle
        
    _nop_10us_delay_loop:
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        lcall   NOP_1us_Delay
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        
        clr     c                           // 1cycle
        mov     a,r7                        // 1cycle
        subb    a,#1                        // 1cycle
        mov     r7,a                        // 1cycle
        mov     a,r6                        // 1cycle
        subb    a,#0                        // 1cycle
        mov     r6,a                        // 1cycle
        jnc     _nop_10us_delay_loop        // 2cycle

    _nop_10us_delay_loop_end:
        nop                                 // 1cycle
        
    #pragma endasm
                                            // ret 2cycle
}

/* --------------------------------- End Of File ------------------------------ */
