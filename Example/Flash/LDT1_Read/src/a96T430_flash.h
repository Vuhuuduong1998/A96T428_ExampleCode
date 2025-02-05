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
#ifndef __FLASH_H_
#define __FLASH_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "intrins.h"
#include "delay.h"
#include "typedef.h"
/*******************************************************************************
* Public Macro
*******************************************************************************/
//Device Description=====================================//
//	Device : A96T418
//	Flash : 32 Kbyte (7FFFh)
//	PageBuf : 64 byte (40h)
//=======================================================//

//Device Dependent=======================================

//Modify to use==========================================

#if A96T418_MODE==0
#define PAGE_BUFFER_SIZE 	0x200U //512B
#define SECTOR_BUFFER_SIZE (0x800U) //2KB
#define	FLASH_BLABK_TATA	((u8)0xFF)

#define	REMAP_ADDR_MAX		0xFFFF
#define	REMAP_ADDR_MIN		0xFA00

#define	REMAPSI_IF1			(0x1<<4)
#define	REMAPSI_IF2_3		(0x6<<4) 

#define	REMAP_IF1_ADDR_MAX		0xFBFF
#define	REMAP_IF1_ADDR_MIN		0xFA00
#define	REMAP_IF2_3_ADDR_MAX	0xFFFF
#define	REMAP_IF2_3_ADDR_MIN	0xFC00

#endif
#if A96T418_MODE==1
#define PAGE_BUFFER_SIZE 	(0x40U)
#define	FLASH_BLABK_TATA	0x00
#endif

//more than 2.0V @ IRC 16MHz
#define FLASH_LVI 0x00//default  //0x06	//LVI 2.28V(2.05V~2.35V)

//Flash Dummy Address value, not used area
#define FLASH_ADDR_DUMMY 0x03FF00
//=====================================================

//safety code for operation of flash memory
#define FLASH_KEY 0xAA55
#define FLASH_XOR 0x9C75

#define WAITTIME 163		// 2.5625ms @ LSIRC 128KHz
#define Flash_Exit()	{FEMR = 0x00; FECR = 0x30;}	                // Set flash to normal mode.

//Flash Mode Control value
#define FLASH_PAGEBUFFER_RESET 0x01

//Flash User ID value, used password
#define FLASH_USER_ID 0xCC33



/*******************************************************************************
* Public Typedef
*******************************************************************************/

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Init_Flash();
void Update_Flash_Buf(unsigned int addr_start, unsigned int addr_end, unsigned char *buf, unsigned int buf_size);
unsigned char Update_Flash(unsigned int key, uint8_t bErase, uint8_t bWrite);
unsigned char Page_Erase_Flash(unsigned int key, unsigned long sector_address, unsigned int buf_size);
unsigned char Page_Write_Flash(unsigned int key, unsigned long sector_address, unsigned int buf_size, unsigned char *buf);
void Read_Flash(unsigned int sector_address, unsigned int size, unsigned char *buf);
uint32_t Flash_CheckSum(uint16_t startaddr, uint16_t endaddr);


#endif //_FLASH_HEADER_

/* --------------------------------- End Of File ------------------------------ */