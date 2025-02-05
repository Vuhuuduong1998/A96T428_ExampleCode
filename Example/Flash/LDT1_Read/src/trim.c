/**
 *******************************************************************************
 * @file        Main.c
 * @author      ABOV R&D Division
 * @brief       Main Example Code
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
#include "intrins.h"
#include "stdio.h"  
#include "delay.h"
#include "a96T428_flash.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart1_uart.h"
#include	"a96T428_flash.h"	
#include "trim.h"  

extern void Flash_Enter(void);

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/

#if A96T418_MODE==0
//Flash Address Min/Max value for permitted area
#define FLASH_ADDR_MIN 		(0xEE00)
#define FLASH_ADDR_MAX 		(0xF9FF) 
//#define FLASH_ADDR_MIN 		(0x800)
//#define FLASH_ADDR_MAX 		(0xFFF) 
#endif
#if A96T418_MODE==1
//Flash Address for used
#define FLASH_ADDR_MIN 		(0x7F00)
#define FLASH_ADDR_MAX 		(0x7FFF) 
#endif

#define	FLASH_USERMEMORY_SIZE ((uint16_t)(FLASH_ADDR_MAX-FLASH_ADDR_MIN+1))
code uint8_t codetmp[FLASH_USERMEMORY_SIZE] _at_ FLASH_ADDR_MIN;

#if A96T418_MODE==1
#define	FLASH_MYBUFFER_SIZE (PAGE_BUFFER_SIZE*2)
#endif
#if A96T418_MODE==0
#define	FLASH_MYBUFFER_SIZE (SECTOR_BUFFER_SIZE+PAGE_BUFFER_SIZE)
#endif

u16 adc_data_table_bgr1v[16] _at_ 0x00;
u16 adc_diffdata_table_bgr1v[16] _at_ 0x20;
u16 adc_data_tmp[16] _at_ 0x40;
u16 adc_data_table_vdc1p5[16] _at_ 0x60;
u16 adc_diffdata_table_vdc1p5[16] _at_ 0x80;

u16 adc_swingwidth_table_bgr1v[16] _at_ 0xA0;
u16 adc_swingwidth_table_vdc1p5[16] _at_ 0xC0;

u32 LDT1_Trim_Table[PAGE_BUFFER_SIZE/4];

uint8_t write_data[FLASH_MYBUFFER_SIZE] _at_ 0x100;
//uint8_t read_data[FLASH_MYBUFFER_SIZE];
//unsigned char code *read_data=0x0000;


/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
u16 BlankCheck(u16 addr, u16 Count)
{
	unsigned char code *rom_addr = (unsigned char code *)addr;
	u16 i, blankErrorCount=0;
	u8 ctmp;
	
	for(i=0; i<Count; i++) { 
		ctmp=*rom_addr++;
		if(ctmp!=FLASH_BLABK_TATA)
			blankErrorCount++;
	}
	return blankErrorCount;
}

void DCT_Erase()
{	
	Flash_Enter();


	// TrimACC mode entry
	FEMR2 = 0x5A;
	FEMR2 = 0xA5;
	FEMR = 0x91;
	while ( !( FESR & (0x1<<1))); //EMODE bit 
	
	FEARM = 0x06;
	FEARL = 0x00;
	FECR = 0x0A;
	
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	if(BlankCheck(0x0600, PAGE_BUFFER_SIZE))
		while(1);
	NOP;
	Flash_Exit();			            // Set flash to normal mode.
}

void IF0_AREA_Erase()
{
	Flash_Enter();

	// IfACC mode entry
	FEMR2 = 0x66;
	FEMR2 = 0x99;
	FEMR =0x91; // 0x95;

	FEARM = 0x00;
	FEARL = 0x00;
	FECR = 0x0A;
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	if(BlankCheck(0x0000, PAGE_BUFFER_SIZE))
		while(1);

	Flash_Exit();			            // Set flash to normal mode.
}

void LDT0_AREA_Erase(void)
{
	Flash_Enter();

	// IfACC mode entry
	FEMR2 = 0x5A;
	FEMR2 = 0xA5;
	FEMR = 0x91;
	while ( !( FESR & (0x1<<1))); //EMODE bit 

	FEARM = 0x02;
	FEARL = 0x00;
	FECR = 0x0A;

	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	if(BlankCheck(0x0200, PAGE_BUFFER_SIZE))
		while(1);

	Flash_Exit();			            // Set flash to normal mode.	
}

void LDT1_AREA_Erase()
{
	Flash_Enter();

	// TrimACC mode entry
	FEMR2 = 0x5A;
	FEMR2 = 0xA5;
	FEMR = 0x91;
	while ( !( FESR & (0x1<<1))); //EMODE bit 

	FEARM = 0x04;
	FEARL = 0x00;
	FECR = 0x0A;

	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	if(BlankCheck(0x0400, PAGE_BUFFER_SIZE))
		while(1);

	Flash_Exit();			            // Set flash to normal mode.	
}

void P2_ID_WRITE()
{
	u32 code *rom_addr=0;
	
	Flash_Enter();
	
	// TrimACC mode entry
	FEMR2 = 0x5A;
	FEMR2 = 0xA5;
	FEMR = 0xA1;
	while ( !( FESR & (0x1<<2))); //WMODE bit 
	
	FEARM = 0x03;
	FEARL = 0xF0;
	FEDR0 = 0xB1; // data
	FEDR1 = 0xFF;
	FEDR2 = 0xFF;
	FEDR3 = 0xFF;
	FECR = 0x0A;
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	rom_addr=(u32 code *)0x03F0;
	while(*rom_addr != 0xB1FFFFFF);

	FEARM = 0x03;
	FEARL = 0xF4; //0xF0;
	FEDR0 = 0xB2; // data
	FEDR1 = 0xFF;
	FEDR2 = 0xFF;
	FEDR3 = 0xFF;
	FECR = 0x0A;
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	rom_addr=(u32 code *)0x03F4;
	while(*rom_addr != 0xB2FFFFFF);

	FEARM = 0x03;
	FEARL = 0xF8; //0xF0;
	FEDR0 = 0xB3; // data
	FEDR1 = 0xFF;
	FEDR2 = 0xFF;
	FEDR3 = 0xFF;
	FECR = 0x0A;
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	rom_addr=(u32 code *)0x03F8;
	while(*rom_addr != 0xB3FFFFFF);

	FEARM = 0x03;
	FEARL = 0xFC; //0xF0;
	FEDR0 = 0xB4; // data
	FEDR1 = 0xFF;
	FEDR2 = 0xFF;
	FEDR3 = 0xFF;
	FECR = 0x0A;
	//Wait 2ms
	_nop_();
	while ( !( FESR & 0x80));
	_nop_();
	rom_addr=(u32 code *)0x03FC;
	while(*rom_addr != 0xB4FFFFFF);
	
	Flash_Exit();			            // Set flash to normal mode.	
	
}

void TRIM_TableBuffer_update(u16 Taddress, u32 Tdata)
{
	unionUL unionTmp;
	u16 i; 
	u16 addr; 
	u16 TaddressBase; 
	
	TaddressBase=(Taddress/0x200)*0x200;
	
	for(i=0; i<2; i++) 
	{
		if(i==0) { 
			unionTmp.ul=Tdata;
			addr=Taddress;
		}
		else {
			unionTmp.ul=0xFFFFFF00;
			addr=Taddress-4;
		}
		LDT1_Trim_Table[(addr-TaddressBase)/4]=unionTmp.ul;
	}
}
	

void TRIM_WRITE_with_TRIM_TableBuffer(void)
{
	u16 Taddr=0;
	u32 wtmp;
	
	printf("TRIM_WRITE_with_TRIM_TableBuffer : ");
	LDT1_AREA_Erase();
	Taddr=0x404;
	while(Taddr<0x450)
	{
		wtmp=LDT1_Trim_Table[(Taddr-0x400)/4];
		TRIM_WRITE(Taddr, wtmp);
		Taddr+=8;
	}
	
}


void TRIM_WRITE(u16 Taddress, u32 Tdata)
{
	unionUL unionTmp;
	u8 uctmp, i; 
	u16 addr; 
	static u32 wtmp, wtmp2;
	u32 code *rom_addr=(u32 code *)Taddress;
	
	for(i=0; i<2; i++) 
	{
		if(i==0) { 
			unionTmp.ul=Tdata;
			addr=Taddress;
		}
		else {
			unionTmp.ul=0xFFFFFF00;
			addr=Taddress-4;
			rom_addr-=1;
		}
		//data reverse 
		uctmp=unionTmp.uc[0];
		unionTmp.uc[0]=unionTmp.uc[3];
		unionTmp.uc[3]=uctmp;
		uctmp=unionTmp.uc[1];
		unionTmp.uc[1]=unionTmp.uc[2];
		unionTmp.uc[2]=uctmp;
		wtmp=unionTmp.ul;
		
		Flash_Enter();
		
		// TrimACC mode entry
		FEMR2 = 0x5A;
		FEMR2 = 0xA5;
		FEMR = 0xA1;
		while ( !( FESR & (0x1<<2))); //WMODE bit 

		if(1)
		{
			FEARM = addr>>8;
			FEARL = addr&0xff;
			FEDR0 = unionTmp.uc[0]; // data
			FEDR1 = unionTmp.uc[1];
			FEDR2 = unionTmp.uc[2];
			FEDR3 = unionTmp.uc[3];		
			FECR = 0x0A;
			//Wait 2ms
			_nop_();
			while ( !( FESR & 0x80));
			_nop_();
		}
		wtmp2=*rom_addr;
		Flash_Exit();			            // Set flash to normal mode.	
		if(wtmp!=wtmp2)
			while(1);
	}	
}

u32 TRIM_READ(u16 Taddress)
{
	unionUL unionTmp;
	u8 uctmp; 
	static u32 wtmp, wtmp2;
	u32 code *rom_addr=(u32 code *)Taddress;
	bit bOCDmode=(RSTFR&OCDRF)?1:0;
	
	Flash_Enter();
	// TrimACC mode entry
	if(bOCDmode)
	{
		FEMR2 = 0x5A;
		FEMR2 = 0xA5;
	}
	else 
	{
		rom_addr=(u32 code *)(Taddress|0xF000);
		FEMR2 = 0x7D;	//Testen mode
		FEMR2 = 0x39;
		FETR4 = 0xD0;	//Hidden_test mode
		FETR4 = 0xDC;
		FETR |= 0x20; //0x40; 	//TREMAP		
	}
	wtmp=*rom_addr;
	Flash_Exit();			            // Set flash to normal mode.	

	unionTmp.ul=wtmp;
		
	//data reverse 
	uctmp=unionTmp.uc[0];
	unionTmp.uc[0]=unionTmp.uc[3];
	unionTmp.uc[3]=uctmp;
	uctmp=unionTmp.uc[1];
	unionTmp.uc[1]=unionTmp.uc[2];
	unionTmp.uc[2]=uctmp;
	wtmp2=unionTmp.ul;

	return wtmp2;
}

u8 ADCCLKdivide=2;// default /2 => 8MHz divide

void BGREF1V_TRIM(u8 bMonitorOnly, u8 bVDCLOCKdisable)
{
	u16 adc_data;
	u16 adc_data_target=819;
	u16 i, j, min_diff=0xffff, diff, utmp;
	u32 wtmp;
	s16 strim_set, min_strim_set;
	u8 saveFUSE_CFG3_BGRREF_1V_TRIM;
	u8 saveTEST_REGE; 
	u16 minADC=0xffff, maxADC=0;

	saveFUSE_CFG3_BGRREF_1V_TRIM=FUSE_CFG3_BGRREF_1V_TRIM;
		
	TEST_AR=0x19; //Test register access enable 
	//REF TEST signal high
	LDOCON = 0x10;
	saveTEST_REGE=TEST_REGE;
	if(bVDCLOCKdisable)
		TEST_REGE = 0xA8; //VDCLOCK disable 

	//ADC setting
	//ADCCRH |= 0x05; // Select ADC clock to fx/2 = 8MHz.
	ADCCRH |= 0x04; // LSB align 
	ADCCRH |= (ADCCLKdivide&0x3); // Select ADC clock 
	ADCCRL |= 0x80; // Enable ADC.
	//ADC channel 17 setting
	ADCCRL  = (ADCCRL&0xF0) | 1;
	ADCCR4  |= 0x80;
	ADCCR3  = 0x1E; //sampling time 

	//Search
	//change FUSE_CAL3[3:0] -> 3ms wait
	//search ADC conversion value nearest to 1V 
	strim_set=7;	
	for(i=0;i<16;i++)
	{
		TEST_AR=0x28; //Trim register access enable 
		FUSE_CFG3_BGRREF_1V_TRIM=strim_set&0x0f; 
		NOP_10us_Delay(300); //3ms wait
		//dummy ADC 16 times 
		for(j=0; j<16; j++)
		{
			ADCCRL |= (1 << 6); //ADC start 
			while(!(ADCCRL & 0x10)); //ADC complete check 
			adc_data_tmp[j]=ADCDR;			
		}
		
		//ADC 16 times 
		minADC=0xffff; maxADC=0;
		adc_data=0;
		for(j=0; j<16; j++)
		{
			ADCCRL |= (1 << 6); //ADC start 
			while(!(ADCCRL & 0x10)); //ADC complete check 
			adc_data_tmp[j]=ADCDR;			
			adc_data += adc_data_tmp[j];	
			if(adc_data_tmp[j]<minADC)
				minADC=adc_data_tmp[j];
			if(adc_data_tmp[j]>maxADC)
				maxADC=adc_data_tmp[j];
		}
		utmp=strim_set&0x0f;
		adc_data/=16;
		if((adc_data%16)>=2)
			adc_data++;
		adc_data_table_bgr1v[utmp]=adc_data;
		if(adc_data>adc_data_target) { 
			diff=adc_data-adc_data_target;
		}
		else if(adc_data<adc_data_target){
			diff=adc_data_target-adc_data;
		}
		else 
			diff=0;
		adc_diffdata_table_bgr1v[utmp]=diff;
		if(diff<min_diff) { 
			min_diff=diff;
			min_strim_set=strim_set;
		}
		adc_swingwidth_table_bgr1v[utmp]=maxADC-minADC;
		strim_set--;
	}
	
	wtmp=min_strim_set&0x0F;
	wtmp|=0xFFFFFF00;
	if(!bMonitorOnly)
		TRIM_WRITE(TADDR_LDT1_BGRREF_1V_TRIM, wtmp);
	
	FUSE_CFG3_BGRREF_1V_TRIM=min_strim_set&0x0F; 
	NOP_10us_Delay(300); //3ms wait
	if(FUSE_CFG3_BGRREF_1V_TRIM!=(wtmp&0xFF))
		NOP;
	if(bMonitorOnly)
	{
		printf("\r\n");	
		printf("BGREF1V_TRIM :\r\n");	
		printf("initial FUSE_CFG3_BGRREF_1V_TRIM=%02x \r\n", saveFUSE_CFG3_BGRREF_1V_TRIM&0xFFU);	
		if(bVDCLOCKdisable) 
			printf("VDCLOCK : VDCLOCK disable \r\n");
		else 
			printf("VDCLOCK : VDCLOCK default \r\n");
		printf("BGR 1V ADC (sampling time(ADCCR3)=%4u) \r\n", ADCCR3&0xFFU);
		printf("BGR 1V ADC data target=%u) \r\n", adc_data_target);
		printf("adc_data_table_bgr1v : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_data_table_bgr1v[j]);
		printf("\r\n");
		printf("adc_diffdata_table_bgr1v : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_diffdata_table_bgr1v[j]);
		printf("\r\n");
		printf("adc_swingwidth_table_bgr1v : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_swingwidth_table_bgr1v[j]);
		printf("\r\n");
		printf("suitable FUSE_CFG3_BGRREF_1V_TRIM=%02x  \r\n", FUSE_CFG3_BGRREF_1V_TRIM&0xFFU);
		if(1)
		{
			//ADC 16 times 
			for(j=0; j<16; j++)
			{
				ADCCRL |= (1 << 6); //ADC start 
				while(!(ADCCRL & 0x10)); //ADC complete check 
				adc_data_tmp[j]=ADCDR;			
			}
		}		
		printf("current adc_data_tmp : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_data_tmp[j]);
		printf("\r\n");		
	}
	TEST_AR=0x19; //Test register access enable 
	if(bVDCLOCKdisable)
		TEST_REGE=saveTEST_REGE;	

	NOP;
}

//void BGREF1V_ADC_monitor(u8 bVDCLOCKdisable)
//{
//	bVDCLOCKdisable=bVDCLOCKdisable;
//	u16 adc_data;
//	u16 adc_data_target=819;
//	u16 i, j;//
//	u16 minADC=0xffff, maxADC=0;
//	u8 saveTEST_REGE; 
//	
//	TEST_AR=0x19; //Test register access enable 
//	//REF TEST signal high
//	LDOCON = 0x10;
//	saveTEST_REGE=TEST_REGE;
//	if(bVDCLOCKdisable)
//		TEST_REGE = 0xA8; //VDCLOCK disable 

//	//ADC setting
//	ADCCRH |= 0x05; // Select ADC clock to fx/2 = 8MHz.
//	ADCCRL |= 0x80; // Enable ADC.
//	//ADC channel 17 setting
//	ADCCRL  = (ADCCRL&0xF0) | 1;
//	ADCCR4  |= 0x80;
//	ADCCR3  = 0x1E; //sampling time 
//	
//	//Search
//	for(i=0;i<1;i++)
//	{
//		TEST_AR=0x28; //Trim register access enable 
//		NOP_10us_Delay(300); //3ms wait
//		//dummy ADC 16 times 
//		for(j=0; j<16; j++)
//		{
//			ADCCRL |= (1 << 6); //ADC start 
//			while(!(ADCCRL & 0x10)); //ADC complete check 
//			adc_data_tmp[j]=ADCDR;			
//		}
//		//ADC 16 times 
//		adc_data=0;
//		for(j=0; j<16; j++)
//		{
//			ADCCRL |= (1 << 6); //ADC start 
//			while(!(ADCCRL & 0x10)); //ADC complete check 
//			adc_data_tmp[j]=ADCDR;			
//			adc_data += adc_data_tmp[j];	
//			if(adc_data_tmp[j]<minADC)
//				minADC=adc_data_tmp[j];
//			if(adc_data_tmp[j]>maxADC)
//				maxADC=adc_data_tmp[j];
//		}
//	}

//	printf("\r\n");
//	printf("FUSE_CFG3_BGRREF_1V_TRIM=%02x \r\n", FUSE_CFG3_BGRREF_1V_TRIM&0xFFU);	
//	if(bVDCLOCKdisable) 
//		printf("VDCLOCK : VDCLOCK disable \r\n");
//	else 
//		printf("VDCLOCK : VDCLOCK default \r\n");		
//	printf("BGR 1V ADC (sampling time(ADCCR3)=%4u) \r\n", ADCCR3&0xFFU);
//	printf("BGR 1V ADC data target=%u) \r\n", adc_data_target);
////	printf("adc_data_table_bgr1v : \r\n");
////	for(j=0; j<16; j++)
////		printf("%4u ", adc_data_table_bgr1v[j]);
////	printf("\r\n");
////	printf("adc_diffdata_table_bgr1v : \r\n");
////	for(j=0; j<16; j++)
////		printf("%4u ", adc_diffdata_table_bgr1v[j]);
////	printf("\r\n");
//	printf("current adc_data_tmp : \r\n");
//	for(j=0; j<16; j++)
//		printf("%4u ", adc_data_tmp[j]);
//	printf("\r\n");
//	printf("minADC=%4u, maxADC=%4u, maxADC-minADC=%4u ", minADC, maxADC, maxADC-minADC);
//	printf("\r\n");

//		NOP_10us_Delay(50000);NOP_10us_Delay(50000);
//		//NOP_10us_Delay(50000);NOP_10us_Delay(50000);
//		//NOP_10us_Delay(50000);NOP_10us_Delay(50000);
//	
//	TEST_AR=0x19; //Test register access enable 
//	if(bVDCLOCKdisable)
//		TEST_REGE=saveTEST_REGE;	

//	NOP;
//}

void VDC1P5V_TRIM(u8 bMonitorOnly)
{
	u16 adc_data;
	u16 adc_data_target=1229;
	u16 i, j, min_diff=0xffff, diff, utmp;
	u32 wtmp;
	s16 strim_set, min_strim_set;
	u8 saveFUSE_CFG6_BMRBGR_VDC1P5V_TRIM;
	u16 minADC=0xffff, maxADC=0;

	saveFUSE_CFG6_BMRBGR_VDC1P5V_TRIM=FUSE_CFG6_BMRBGR_VDC1P5V_TRIM;
	
	TEST_AR=0x19; //Test register access enable 
	//ADC setting
	ADCCRH |= 0x05; // Select ADC clock to fx/2 = 8MHz.
	ADCCRL |= 0x80; // Enable ADC.
	//ADC channel 18 setting
	ADCCRL  = (ADCCRL&0xF0) | 2;
	ADCCR4  |= 0x80;
	ADCCR3  = 0x1E; //sampling time 

	//Search
	//change FUSE_CAL6[3:0] -> 3ms wait
	//search ADC conversion value nearest to 1V 
	strim_set=7;	
	for(i=0;i<16;i++)
	{
		TEST_AR=0x28; //Trim register access enable 
		FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=strim_set&0x0f; 
		NOP_10us_Delay(300); //3ms wait
		//dummy ADC 16 times 
		for(j=0; j<16; j++)
		{
			ADCCRL |= (1 << 6); //ADC start 
			while(!(ADCCRL & 0x10)); //ADC complete check 
			adc_data_tmp[j]=ADCDR;			
		}
		
		//ADC 16 times 
		minADC=0xffff; maxADC=0;
		adc_data=0;
		for(j=0; j<16; j++)
		{
			ADCCRL |= (1 << 6); //ADC start 
			while(!(ADCCRL & 0x10)); //ADC complete check 
			adc_data_tmp[j]=ADCDR;			
			adc_data += adc_data_tmp[j];	
			if(adc_data_tmp[j]<minADC)
				minADC=adc_data_tmp[j];
			if(adc_data_tmp[j]>maxADC)
				maxADC=adc_data_tmp[j];			
		}
		utmp=strim_set&0x0f;
		adc_data/=16;
		if((adc_data%16)>=2)
			adc_data++;
		adc_data_table_vdc1p5[utmp]=adc_data;
		if(adc_data>adc_data_target) { 
			diff=adc_data-adc_data_target;
		}
		else if(adc_data<adc_data_target){
			diff=adc_data_target-adc_data;
		}
		else 
			diff=0;
		adc_diffdata_table_vdc1p5[utmp]=diff;
		if(diff<min_diff) { 
			min_diff=diff;
			min_strim_set=strim_set;
		}
		adc_swingwidth_table_vdc1p5[utmp]=maxADC-minADC;
		strim_set--;
	}

	wtmp=min_strim_set&0x0F;
	wtmp|=0xFFFFFF00;
	if(!bMonitorOnly)
		TRIM_WRITE(TADDR_LDT1_BMRBGR_VDC1P5V_TRIM, wtmp);
	FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=min_strim_set&0x0f; 
	NOP_10us_Delay(300); //3ms wait
	if(FUSE_CFG3_BGRREF_1V_TRIM!=(wtmp&0xFF))
		NOP;
	
	if(bMonitorOnly)
	{
		printf("\r\n");
		printf("VDC1P5V_TRIM: \r\n");	
		printf("initial FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=%02x \r\n", saveFUSE_CFG6_BMRBGR_VDC1P5V_TRIM&0xFFU);	
		printf("VDC1P15 ADC (sampling time(ADCCR3)=%4u) \r\n", ADCCR3&0xFFU);	
		printf("VDC1P15 ADC data target=%u) \r\n", adc_data_target);
		printf("adc_data_table_vdc1p5 : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_data_table_vdc1p5[j]);
		printf("\r\n");
		printf("adc_diffdata_table_vdc1p5 : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_diffdata_table_vdc1p5[j]);
		printf("\r\n");
		printf("adc_swingwidth_table_vdc1p5 : \r\n");
		for(j=0; j<16; j++)
			printf("%4u ", adc_swingwidth_table_vdc1p5[j]);
		printf("\r\n");
		printf("suitable FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=%02x  \r\n", FUSE_CFG6_BMRBGR_VDC1P5V_TRIM&0xFFU);
		if(1)
		{
			//ADC 16 times 
			for(j=0; j<16; j++)
			{
				ADCCRL |= (1 << 6); //ADC start 
				while(!(ADCCRL & 0x10)); //ADC complete check 
				adc_data_tmp[j]=ADCDR;			
			}
		}		
		printf("current adc_data_tmp : \r\n");
		for(j=0; j<16; j++)
		{
			printf("%4u ", adc_data_tmp[j]);
		}
		printf("\r\n");
	}
	NOP;
	
	NOP;
}

//void VDC1P5V_ADC_Monitor(void)
//{
//	u16 adc_data;
//	u16 adc_data_target=1229;
//	u16 i, j;//, min_diff=0xffff, diff, utmp;
//	//u32 wtmp;
//	//s16 strim_set, min_strim_set;
//	
//	TEST_AR=0x19; //Test register access enable 
//	//ADC setting
//	ADCCRH |= 0x05; // Select ADC clock to fx/2 = 8MHz.
//	ADCCRL |= 0x80; // Enable ADC.
//	//ADC channel 18 setting
//	ADCCRL  = (ADCCRL&0xF0) | 2;
//	ADCCR4  |= 0x80;
//	ADCCR3  = 0x1E; //sampling time 

//	//Search
//	for(i=0;i<1;i++)
//	{
//		TEST_AR=0x28; //Trim register access enable 
//		//dummy ADC 16 times 
//		for(j=0; j<16; j++)
//		{
//			ADCCRL |= (1 << 6); //ADC start 
//			while(!(ADCCRL & 0x10)); //ADC complete check 
//			adc_data_tmp[j]=ADCDR;			
//		}
//		//ADC 16 times 
//		adc_data=0;
//		for(j=0; j<16; j++)
//		{
//			ADCCRL |= (1 << 6); //ADC start 
//			while(!(ADCCRL & 0x10)); //ADC complete check 
//			adc_data_tmp[j]=ADCDR;			
//			adc_data += adc_data_tmp[j];	
//		}
//	}
//	
//	printf("\r\n");
//	printf("FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=%02x \r\n", FUSE_CFG6_BMRBGR_VDC1P5V_TRIM&0xFFU);	
//	printf("VDC1P15 ADC (sampling time(ADCCR3)=%4u) \r\n", ADCCR3&0xFFU);	
//	printf("VDC1P15 ADC data target=%u) \r\n", adc_data_target);
//	printf("adc_data_table_vdc1p5 : \r\n");
//	for(j=0; j<16; j++)
//		printf("%4u ", adc_data_table_vdc1p5[j]);
//	printf("\r\n");
//	printf("adc_diffdata_table_vdc1p5 : \r\n");
//	for(j=0; j<16; j++)
//		printf("%4u ", adc_diffdata_table_vdc1p5[j]);
//	printf("\r\n");
//	printf("current adc_data_tmp : \r\n");
//	for(j=0; j<16; j++)
//	{
//		printf("%4u ", adc_data_tmp[j]);
//	}
//	printf("\r\n");
//	NOP;
//}

void Trim_TableBuffer_monitor(u16 TaddrBase)
{
	u32 wtmp;
	u16 Taddr=0;
	u8	uc;
	bit bOCDmode=(RSTFR&OCDRF)?1:0;
	
	if(bOCDmode)
	{
		printf("\n\r");
		printf("Trim_TableBuffer_monitor @%04x: \n\r", TaddrBase);
		Taddr=TaddrBase;
		while(Taddr<(TaddrBase+0x200))
		{
			printf("Taddr=%04x: ", Taddr);
			for(uc=0; uc<16; uc++) {
				wtmp=LDT1_Trim_Table[(Taddr-0x400)/4];
				printf("%08lx ", wtmp);	
				Taddr+=4;
			}
			printf("\r\n");
		}
	}
	else
	{
		TaddrBase = (TaddrBase|0xF000);
		printf("\n\r");
		printf("Trim_TableBuffer_monitor @%04x: \n\r", TaddrBase);
		Taddr=TaddrBase;
		while(Taddr<(TaddrBase+0x200))
		{
			printf("Taddr=%04x: ", Taddr);
			for(uc=0; uc<16; uc++) {
				wtmp=LDT1_Trim_Table[(Taddr-0xF400)/4];
				printf("%08lx ", wtmp);	
				Taddr+=4;
			}
			printf("\r\n");
		}
	}

}


void TRIM_TableBuffer_read(u16 TaddrBase)
{
	u32 wtmp;
	u16 Taddr;
	bit bOCDmode=(RSTFR&OCDRF)?1:0;
	
	if(bOCDmode)
	{
		Taddr = TaddrBase/0x200*0x200;
		
		while(Taddr<(TaddrBase+0x200))
		{
			wtmp=TRIM_READ(Taddr);
			LDT1_Trim_Table[(Taddr-0x400)/4]=wtmp;
			Taddr+=4;
		}
	}
	else
	{
		TaddrBase = (TaddrBase|0xF000);
		Taddr=TaddrBase/0x200*0x200;
		
		while(Taddr<(TaddrBase+0x200))
		{
			wtmp=TRIM_READ(Taddr-0xF000);
			LDT1_Trim_Table[(Taddr-0xF400)/4]=wtmp;
			Taddr+=4;
		}
	}
}
	
void TRIM_Register_monitor(void)
{
	u32 wtmp;
	u16 Taddr=0;

	printf("\n\r\n");
	printf("TRIM_Register_monitor :\r\n");
	
	wtmp=TRIM_READ(TADDR_LDT1_BGRREF_1V_TRIM);
	printf("TADDR_LDT1_BGRREF_1V_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG3_BGRREF_1V_TRIM=%02x \r\n", FUSE_CFG3_BGRREF_1V_TRIM&0xFFU);	
	printf("\n\r");
	
	wtmp=TRIM_READ(TADDR_LDT1_BMRBGR_VDC1P5V_TRIM);
	printf("TADDR_LDT1_BMRBGR_VDC1P5V_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG6_BMRBGR_VDC1P5V_TRIM=%02x \r\n", FUSE_CFG6_BMRBGR_VDC1P5V_TRIM&0xFFU);	
	printf("\n\r");
	
	wtmp=TRIM_READ(TADDR_IRC32FCAL_HIGH_TRIM);
	printf("TADDR_IRC32FCAL_HIGH_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG1_IRC32FCAL_HIGH_TRIM=%02x \r\n", FUSE_CFG1_IRC32FCAL_HIGH_TRIM&0xFFU);	
	printf("\n\r");
	
	wtmp=TRIM_READ(TADDR_IRC32FCAL_LOW_TRIM);
	printf("TADDR_IRC32FCAL_LOW_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG0_IRC32FCAL_LOW_TRIM=%02x \r\n", FUSE_CFG0_IRC32FCAL_LOW_TRIM&0xFFU);	
	printf("\n\r");

	wtmp=TRIM_READ(TADDR_TIRC16FCAL_HIGH_TRIM);
	printf("TADDR_TIRC16FCAL_HIGH_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG5_TIRC16FCAL_HIGH_TRIM=%02x \r\n", FUSE_CFG5_TIRC16FCAL_HIGH_TRIM&0xFFU);	
	printf("\n\r");

	wtmp=TRIM_READ(TADDR_TIRC16FCAL_LOW_TRIM);
	printf("TADDR_TIRC16FCAL_LOW_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG4_TIRC16FCAL_LOW_TRIM=%02x \r\n", FUSE_CFG4_TIRC16FCAL_LOW_TRIM&0xFFU);	
	printf("\r\n");

	wtmp=TRIM_READ(TADDR_TLDO_TRIM);
	printf("TADDR_TLDO_TRIM=%08lx \r\n", wtmp);	
	printf("FUSE_CFG8_TLDO_TRIM=%02x \r\n", FUSE_CFG8_TLDO_TRIM&0xFFU);	
	printf("\n\r");
	
}

void IRC32M_TRIM(u8 bMonitorOnly)
{
	//At first, check PWM freq at sCoarsetrim_set=0, sFinetrim_set=0
	//PWM freq is 160kHz @ P12(PWM2O)
	//if not accurate, adjust sCoarsetrim_set, sFinetrim_set 

	//s16 sCoarsetrim_set(-64 ~ 63), sFinetrim_set(-8 ~ 7) ; range 
	//static s16  sCoarsetrim_set=0, sFinetrim_set=0;
	//static s16  sCoarsetrim_set=1, sFinetrim_set=0;
	//static s16  sCoarsetrim_set=-1, sFinetrim_set=0; //
	//static s16  sCoarsetrim_set=1, sFinetrim_set=33;
	//static s16  sCoarsetrim_set=0, sFinetrim_set=50;
	static s16  sCoarsetrim_set=0, sFinetrim_set=25;

	u32 wtmp;
	s16 high_tmp, low_tmp;
	
	TEST_AR=0x19; //Test register access enable 

	//Search
	//change FUSE_CAL1[2:0], FUSE_CAL0[7:0] -> 3ms wait
	//search trim value nearest to 32MHz 
	if(1)
	{
		TEST_AR=0x28; //Trim register access enable 
		
		high_tmp=sCoarsetrim_set>>1; //[10:8]
		low_tmp=sCoarsetrim_set<<7; //[7]
		low_tmp|=sFinetrim_set&0x7F; //[6:0]

		high_tmp&=0x07; //[10:8]
		low_tmp&=0xFF; //[7:0]
		
		FUSE_CFG1_IRC32FCAL_HIGH_TRIM=high_tmp; //[10:8]
		NOP_10us_Delay(300); //3ms wait
		FUSE_CFG0_IRC32FCAL_LOW_TRIM=low_tmp; //[7:0]
		NOP_10us_Delay(300); //3ms wait

		wtmp=high_tmp&0xFF;
		wtmp|=0xFFFFFF00;
		if(!bMonitorOnly)
			TRIM_WRITE(TADDR_IRC32FCAL_HIGH_TRIM, wtmp);		

		wtmp=low_tmp&0xFF;
		wtmp|=0xFFFFFF00;
		if(!bMonitorOnly) {
			TRIM_WRITE(TADDR_IRC32FCAL_LOW_TRIM, wtmp);	
	}
	
	if(bMonitorOnly){
		printf("\n\n\r");
		printf("IRC32M_TRIM : \n\r");
		printf("sCoarsetrim_set=%d, sFinetrim_set=%d \n\r", sCoarsetrim_set, sFinetrim_set);
		printf("FUSE_CFG1_IRC32FCAL_HIGH_TRIM=%02x \n\r", FUSE_CFG1_IRC32FCAL_HIGH_TRIM&0xFFU);
		printf("FUSE_CFG0_IRC32FCAL_LOW_TRIM=%02x \n\r", FUSE_CFG0_IRC32FCAL_LOW_TRIM&0xFFU);		
		}
	}
	NOP;
		
}

void TIRC16M_TRIM(u8 bMonitorOnly)
{
	static s16 sCoarsetrim_set=2;//sCoarsetrim_set(-4 ~ 3); range 
	static s16 sMiddletrim_set=0;//sMiddletrim_set(-8 ~ 7); range 
	static s16 sFinetrim_set=0;//sFinetrim_set(-4 ~ 3) ; range 

	s16  tCoarsetrim_set, tFinetrim_set;

	u32 wtmp;
	s16 high_temp, low_temp;

	sCoarsetrim_set&=0x7;
	tCoarsetrim_set=sCoarsetrim_set;
	
	sMiddletrim_set&=0x0F;
	sFinetrim_set&=0x07;
	tFinetrim_set=(sMiddletrim_set<<3)|sFinetrim_set;
	tFinetrim_set&=0x7F;
	
	TEST_AR=0x19; //Test register access enable 
    NOP_10us_Delay(300); //3ms wait
    TEST_AR=0x28; //Trim register access enable 
    
    high_temp=tCoarsetrim_set>>1; //[9:8]
    low_temp=tCoarsetrim_set<<7; //[7]
    low_temp|=tFinetrim_set&0x7F; //[6:0]

    high_temp&=0x03; //[9:8]
    low_temp&=0xFF; //[7:0]    
    
    FUSE_CFG5_TIRC16FCAL_HIGH_TRIM=high_temp; //[9:8]
    NOP_10us_Delay(300); //3ms wait
    FUSE_CFG4_TIRC16FCAL_LOW_TRIM=low_temp; //[7:0]
    NOP_10us_Delay(300); //3ms wait

	wtmp=high_temp&0xFF;
	wtmp|=0xFFFFFF00;
	if(!bMonitorOnly)
		TRIM_WRITE(TADDR_TIRC16FCAL_HIGH_TRIM, wtmp);

	wtmp=low_temp&0xFF;
	wtmp|=0xFFFFFF00;
	if(!bMonitorOnly)
		TRIM_WRITE(TADDR_TIRC16FCAL_LOW_TRIM, wtmp);

	if(bMonitorOnly){
		printf("\n\n\r");
		printf("TIRC16M_TRIM : \n\r");
		printf("tCoarsetrim_set=%d, tFinetrim_set=%d \n\r", tCoarsetrim_set, tFinetrim_set);
		printf("FUSE_CFG5_TIRC16FCAL_HIGH_TRIM=%02x \n\r", FUSE_CFG5_TIRC16FCAL_HIGH_TRIM&0xFFU);
		printf("FUSE_CFG4_TIRC16FCAL_LOW_TRIM=%02x \n\r", FUSE_CFG4_TIRC16FCAL_LOW_TRIM&0xFFU);
	}
	NOP;
}

void TLDO_TRIM(u8 bMonitorOnly)
{
	//static s16  s2p4vtrim_set(-8 ~ 7) , s4p0vtrim_set(-8 ~ 7) ; range 
	//static s16  s2p4vtrim_set=0x30, s4p0vtrim_set=0x07;
	static s8  s2p4vtrim_set=7, s4p0vtrim_set=7;
	
	u32 wtmp;
	s16 high_temp, low_temp, temp;
	
	//s2p4vtrim_set+=0x10;
	//s2p4vtrim_set&=0xF0;
	//s4p0vtrim_set+=0x1;
	//s4p0vtrim_set&=0xF;
	
	
	TEST_AR=0x19; //Test register access enable 
//    NOP_10us_Delay(300); //3ms wait
    TEST_AR=0x28; //Trim register access enable 
    
    
    high_temp=(s2p4vtrim_set<<4)&0xF0; //[7:4]
    low_temp=s4p0vtrim_set&0x0F; //[3:0]
    
    temp = (high_temp | low_temp);
    temp &= 0xff;
    
    FUSE_CFG8_TLDO_TRIM = temp; //[7:0]
    NOP_10us_Delay(300); //3ms wait

	wtmp=temp&0xFF;
	wtmp|=0xFFFFFF00;
	if(!bMonitorOnly)
		TRIM_WRITE(TADDR_TLDO_TRIM, wtmp);

	if(bMonitorOnly){
		printf("\n\n\r");
		printf("TLDO_TRIM : \n\r");
		printf("s2p4vtrim_set=%d(%x), s4p0vtrim_set=%d(%x) \n\r", (s16)(s2p4vtrim_set/16), (s16)(s2p4vtrim_set/16), (s16)s4p0vtrim_set, (s16)s4p0vtrim_set);
		printf("FUSE_CFG8_TLDO_TRIM=%02x \n\r", FUSE_CFG8_TLDO_TRIM&0xFFU);
		NOP;
	}

	NOP;
}

/* --------------------------------- End Of File ------------------------------ */
