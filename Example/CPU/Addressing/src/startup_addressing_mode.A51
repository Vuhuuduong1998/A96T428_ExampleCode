$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 8.01
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP.OBJ  controls
;
;------------------------------------------------------------------------------
;
;  User-defined <h> Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
; <o> IDATALEN: IDATA memory size <0x0-0x060> 96 byte
;     <i> Note: The absolute start-address of IDATA memory is always 0
;     <i>       The IDATA space overlaps physically the DATA and BIT areas.
IDATALEN        EQU     100H
;
; <o> XDATASTART: XDATA memory start address <0x0-0xFFFF> 
;     <i> The absolute start address of XDATA memory
XDATASTART      EQU     0     
;
; <o> XDATALEN: XDATA memory size <0x0-0xFFFF> 
;     <i> The length of XDATA memory in bytes.
XDATALEN        EQU     700H      
;
; <o> PDATASTART: PDATA memory start address <0x0-0xFFFF> 
;     <i> The absolute start address of PDATA memory
PDATASTART      EQU     0H
;
; <o> PDATALEN: PDATA memory size <0x0-0xFF> 
;     <i> The length of PDATA memory in bytes.
PDATALEN        EQU     0H
;
;</h>
;------------------------------------------------------------------------------
;
;<h> Reentrant Stack Initialization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
; <h> Stack Space for reentrant functions in the SMALL model.
;  <q> IBPSTACK: Enable SMALL model reentrant stack
;     <i> Stack space for reentrant functions in the SMALL model.
IBPSTACK        EQU     0       ; set to 1 if small reentrant is used.
;  <o> IBPSTACKTOP: End address of SMALL model stack <0x0-0xFF>
;     <i> Set the top of the stack to the highest location.
IBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </h>
;
; <h> Stack Space for reentrant functions in the LARGE model.      
;  <q> XBPSTACK: Enable LARGE model reentrant stack
;     <i> Stack space for reentrant functions in the LARGE model.
XBPSTACK        EQU     0       ; set to 1 if large reentrant is used.
;  <o> XBPSTACKTOP: End address of LARGE model stack <0x0-0xFFFF>
;     <i> Set the top of the stack to the highest location.
XBPSTACKTOP     EQU     0xFFFF +1   ; default 0FFFFH+1 
; </h>
;
; <h> Stack Space for reentrant functions in the COMPACT model.    
;  <q> PBPSTACK: Enable COMPACT model reentrant stack
;     <i> Stack space for reentrant functions in the COMPACT model.
PBPSTACK        EQU     0       ; set to 1 if compact reentrant is used.
;
;   <o> PBPSTACKTOP: End address of COMPACT model stack <0x0-0xFFFF>
;     <i> Set the top of the stack to the highest location.
PBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </h>
;</h>
;------------------------------------------------------------------------------
;
;  Memory Page for Using the Compact Model with 64 KByte xdata RAM
;  <e>Compact Model Page Definition
;
;  <i>Define the XDATA page used for PDATA variables. 
;  <i>PPAGE must conform with the PPAGE set in the linker invocation.
;
; Enable pdata memory page initalization
PPAGEENABLE     EQU     0       ; set to 1 if pdata object are used.
;
; <o> PPAGE number <0x0-0xFF> 
; <i> uppermost 256-byte address of the page used for PDATA variables.
PPAGE           EQU     0
;
; <o> SFR address which supplies uppermost address byte <0x0-0xFF> 
; <i> most 8051 variants use P2 as uppermost address byte
PPAGE_SFR       DATA    0A0H
;
; </e>
;------------------------------------------------------------------------------

; Standard SFR Symbols 
ACC     DATA    0E0H
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

                NAME    ?C_STARTUP


?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1

                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

                CSEG    AT      0
?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:

IF IDATALEN <> 0
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF

IF XDATALEN <> 0
                MOV     DPTR,#XDATASTART
                MOV     R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
                MOV     R6,#(HIGH (XDATALEN)) +1
  ELSE
                MOV     R6,#HIGH (XDATALEN)
  ENDIF
                CLR     A
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                DJNZ    R7,XDATALOOP
                DJNZ    R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0
                MOV     PPAGE_SFR,#PPAGE
ENDIF

IF PDATALEN <> 0
                MOV     R0,#LOW (PDATASTART)
                MOV     R7,#LOW (PDATALEN)
                CLR     A
PDATALOOP:      MOVX    @R0,A
                INC     R0
                DJNZ    R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

                MOV     ?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

                MOV     ?C_XBP,#HIGH XBPSTACKTOP
                MOV     ?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
                MOV     ?C_PBP,#LOW PBPSTACKTOP
ENDIF

				jmp	addressing_mode_test
addressing_mode_return:

                MOV     SP,#?STACK-1

; This code is required if you use L51_BANK.A51 with Banking Mode 4
;<h> Code Banking
; <q> Select Bank 0 for L51_BANK.A51 Mode 4
#if 0   
;     <i> Initialize bank mechanism to code bank 0 when using L51_BANK.A51 with Banking Mode 4.
EXTRN CODE (?B_SWITCH0)
                CALL    ?B_SWITCH0      ; init bank mechanism to code bank 0
#endif
;</h>
                LJMP    ?C_START

addressing_mode_test:
				nop
iram_direct_addressing:
                MOV     0ah,#0ah
                MOV     1ah,#1ah
                MOV     2ah,#2ah
                MOV     3ah,#3ah
                MOV     4ah,#4ah
                MOV     5ah,#5ah
                MOV     6ah,#6ah
                MOV     7ah,#7ah
				
iram_indirect_addressing:
                MOV     R0,#0ch
                MOV     @R0,#0ch
                MOV     R0,#1ch
                MOV     @R0,#1ch
                MOV     R0,#2ch
                MOV     @R0,#2ch
                MOV     R0,#3ch
                MOV     @R0,#3ch
                MOV     R0,#4ch
                MOV     @R0,#4ch
                MOV     R0,#5ch
                MOV     @R0,#5ch
                MOV     R0,#6ch
                MOV     @R0,#6ch
                MOV     R0,#7ch
                MOV     @R0,#7ch
                MOV     R0,#8ch
                MOV     @R0,#8ch
                MOV     R0,#9ch
                MOV     @R0,#9ch
                MOV     R0,#0ach
                MOV     @R0,#0ach
                MOV     R0,#0bch
                MOV     @R0,#0bch
                MOV     R0,#0cch
                MOV     @R0,#0cch
                MOV     R0,#0dch
                MOV     @R0,#0dch
                MOV     R0,#0ech
                MOV     @R0,#0ech
                MOV     R0,#0fch
                MOV     @R0,#0fch

xram_pdata_indirect_addressing:
                MOV     R0,#07h
				MOV     A,#07h
                MOVX    @R0,A 
                MOV     R0,#17h
				MOV     A,#17h
                MOVX    @R0,A 
				MOV     A,#27h
                MOV     R0,#27h
                MOVX    @R0,A 
                MOV     R0,#37h
				MOV     A,#37h
                MOVX    @R0,A 
                MOV     R0,#47h
				MOV     A,#47h
                MOVX    @R0,A 
                MOV     R0,#57h
				MOV     A,#57h
                MOVX    @R0,A 
                MOV     R0,#67h
				MOV     A,#67h
                MOVX    @R0,A 
                MOV     R0,#77h
				MOV     A,#77h
                MOVX    @R0,A 
                MOV     R0,#87h
				MOV     A,#87h
                MOVX    @R0,A 
                MOV     R0,#97h
				MOV     A,#97h
                MOVX    @R0,A 
                MOV     R0,#0a7h
				MOV     A,#0a7h
                MOVX    @R0,A 
                MOV     R0,#0b7h
				MOV     A,#0b7h
                MOVX    @R0,A 
                MOV     R0,#0c7h
				MOV     A,#0c7h
                MOVX    @R0,A 
                MOV     R0,#0d7h
				MOV     A,#0d7h
                MOVX    @R0,A 
                MOV     R0,#0e7h
				MOV     A,#0e7h
                MOVX    @R0,A 
                MOV     R0,#0f7h
				MOV     A,#0f7h
                MOVX    @R0,A 
xram_xdata_indirect_addressing:
                MOV     DPTR,#08h
				MOV     A,#08h
                MOVX    @DPTR,A 
                MOV     DPTR,#18h
				MOV     A,#18h
                MOVX    @DPTR,A 
				MOV     A,#28h
                MOV     DPTR,#28h
                MOVX    @DPTR,A 
                MOV     DPTR,#38h
				MOV     A,#38h
                MOVX    @DPTR,A 
                MOV     DPTR,#48h
				MOV     A,#48h
                MOVX    @DPTR,A 
                MOV     DPTR,#58h
				MOV     A,#58h
                MOVX    @DPTR,A 
                MOV     DPTR,#68h
				MOV     A,#68h
                MOVX    @DPTR,A 
                MOV     DPTR,#78h
				MOV     A,#78h
                MOVX    @DPTR,A 
                MOV     DPTR,#88h
				MOV     A,#88h
                MOVX    @DPTR,A 
                MOV     DPTR,#98h
				MOV     A,#98h
                MOVX    @DPTR,A 
                MOV     DPTR,#0a8h
				MOV     A,#0a8h
                MOVX    @DPTR,A 
                MOV     DPTR,#0b8h
				MOV     A,#0b8h
                MOVX    @DPTR,A 
                MOV     DPTR,#0c8h
				MOV     A,#0c8h
                MOVX    @DPTR,A 
                MOV     DPTR,#0d8h
				MOV     A,#0d8h
                MOVX    @DPTR,A 
                MOV     DPTR,#0e8h
				MOV     A,#0e8h
                MOVX    @DPTR,A 
                MOV     DPTR,#0f8h
				MOV     A,#0f8h
                MOVX    @DPTR,A 				
				jmp		addressing_mode_return
	
                END
