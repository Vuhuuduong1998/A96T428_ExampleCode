/**
 *******************************************************************************
 * @file        a96T428_flash.h
 * @author      ABOV R&D Division
 * @brief       Flash Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TRIM_H_
#define __TRIM_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "intrins.h"
#include "delay.h"
#include "typedef.h"


#define     TS_MODE     					(*(volatile unsigned char xdata *) 0x2EC1)        //
#define     TS_MODE2     					(*(volatile unsigned char xdata *) 0x2ED6)        //
#define     TS_TEST     					(*(volatile unsigned char xdata *) 0x2ED7)        //
#define     TS_CH_SEL_0     				(*(volatile unsigned char xdata *) 0x2EC6)        //    

#define     LDOCON     						(*(volatile unsigned char xdata *) 0x2F45)        //
#define     TEST_REGE  						(*(volatile unsigned char xdata *) 0x2F46)        //
#define     FUSE_CFG0_IRC32FCAL_LOW_TRIM   	(*(volatile unsigned char xdata *) 0x2F52)        //
#define     FUSE_CFG1_IRC32FCAL_HIGH_TRIM   (*(volatile unsigned char xdata *) 0x2F53)        //
#define     FUSE_CFG2_IRC32TCAL_TRIM   		(*(volatile unsigned char xdata *) 0x2F54)        //
#define     FUSE_CFG3_BGRREF_1V_TRIM    	(*(volatile unsigned char xdata *) 0x2F55)        //
#define     FUSE_CFG6_BMRBGR_VDC1P5V_TRIM	(*(volatile unsigned char xdata *) 0x2F58)        //

#define     FUSE_CFG4_TIRC16FCAL_LOW_TRIM   (*(volatile unsigned char xdata *) 0x2F56)        //
#define     FUSE_CFG5_TIRC16FCAL_HIGH_TRIM  (*(volatile unsigned char xdata *) 0x2F57)        //    
#define     FUSE_CFG8_TLDO_TRIM             (*(volatile unsigned char xdata *) 0x2F5B)        //

#define     TEST_REGB  					(*(volatile unsigned char xdata *) 0x2F5E)        //
#define     TEST_REGA  					(*(volatile unsigned char xdata *) 0x2F5F)        //


#define     TADDR_IRC32FCAL_LOW_TRIM    (0x0404)        //
#define     TADDR_IRC32FCAL_HIGH_TRIM   (0x040C)        //

#define     TADDR_TIRC16FCAL_LOW_TRIM    (0x0424)        //
#define     TADDR_TIRC16FCAL_HIGH_TRIM   (0x042C)        //

#define     TADDR_TLDO_TRIM             (0x0444)        //


//#define     TADDR_LDT0_BGRREF_1V_TRIM	(0x011C)        //
#define     TADDR_LDT1_BGRREF_1V_TRIM   (0x041C)        //

#define     TADDR_LDT1_BMRBGR_VDC1P5V_TRIM    (0x0434)        //

extern void Flash_Enter(void);
extern void DCT_Erase();
extern void IF0_AREA_Erase();
extern void LDT0_AREA_Erase(void);
extern void LDT1_AREA_Erase();
extern void P2_ID_WRITE();
extern u16 adc_data_table[16];
extern void BGREF1V_TRIM(u8 bMonitorOnly, u8 bVDCLOCKdisable);
extern void VDC1P5V_TRIM(u8 bMonitorOnly);
extern void IRC32M_TRIM(u8 bMonitorOnly);
//extern void BGREF1V_ADC_monitor(u8 bVDCLOCKdisable);
//extern void VDC1P5V_ADC_Monitor(void);
extern void TRIM_Register_monitor(void);
extern void TIRC16M_TRIM(u8 bMonitorOnly);
extern void TLDO_TRIM(u8 bMonitorOnly);
void Trim_TableBuffer_monitor(u16 TaddrBase);
void TRIM_WRITE_with_TRIM_TableBuffer(void);
u32 TRIM_READ(u16 Taddress);
void TRIM_WRITE(u16 Taddress, u32 Tdata);
void TRIM_TableBuffer_read(u16 TaddrBase);

extern u16 adc_data_tmp[16];
extern u8 ADCCLKdivide;// default /8 divide

//#define	MONITORONLY		1
//#define	VDCLOCKDISABLE	1
typedef enum { VDCLOCKDEFAULT = 0, VDCLOCKDISABLE= 1 };
typedef enum { TRIMnWRITE = 0, MONITORONLY= 1 };

typedef union 
{
	u32 ul;
	u8 uc[4];
} unionUL; 

#endif //__TRIM_H_


/* --------------------------------- End Of File ------------------------------ */