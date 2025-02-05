/**
 *******************************************************************************
 * @file        a96T428_flash.c
 * @author      ABOV R&D Division
 * @brief       Flash Source File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/*******************************************************************************
* Included File
*******************************************************************************/
#include	"a96T428_flash.h"	

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
// User ID global value
unsigned int User_ID;

unsigned char *target_buf;
unsigned int target_bufsize;
unsigned int target_addr_start, target_addr_end;
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/
// from flash_enter.a51
extern void Flash_LoadData(unsigned char dt, unsigned int add);
extern void Flash_Enter(void);

/**
* @brief	Safety code operation of flash memory initialization.
* @param    None
* @return	None
*/
void Init_Flash()
{
	//Init User_ID
	User_ID = 0;

	// Set Flash Sector Address as Dummy address
	FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
	FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;	//Flash Sector Address Middle Register
	FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;	//Flash Sector Address Low Register
}

/**
* @brief	Update Flash buffer for writing flash memory.
* @param    buf 	This parameter contains the buffer of writing Flash memory.
* @param    buf_size 	This parameter contains the size of data.
* @return	None
*/
void Update_Flash_Buf(unsigned int addr_start, unsigned int addr_end, unsigned char *buf, unsigned int buf_size)
{
	//Flash Buffer Update
	User_ID = FLASH_USER_ID;
	target_addr_start=addr_start;
	target_addr_end=addr_end;
	target_buf = buf;
	target_bufsize = buf_size;
}

/**
* @brief	Update flash memory for writing flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @return	None
*/
	static unsigned long paddr;
	static unsigned long paddrSize;
unsigned char Update_Flash(unsigned int key, uint8_t bErase, uint8_t bWrite)
{
	unsigned char ret = 0;
	unsigned int bufSize = 0;
	unsigned char *buf;

	if(target_addr_start>target_addr_end)
		while(1); //malfunction
	if((target_addr_end-target_addr_start+1)>target_bufsize)
		while(1); //malfunction
	
	if(key == FLASH_KEY)
	{
		if(User_ID == FLASH_USER_ID)
		{		
			buf=target_buf;
			paddr = (unsigned long)target_addr_start;
			paddrSize = (unsigned long)(target_addr_end-target_addr_start+1);
			
			while(paddrSize > 0)
			{								
				if((paddr<target_addr_start)||(paddr>target_addr_end))
					break;
				if(buf>=(target_buf+target_bufsize))
					break;
				
				if(paddr%PAGE_BUFFER_SIZE) //if not start of page addr
				{
					bufSize=PAGE_BUFFER_SIZE-(paddr%PAGE_BUFFER_SIZE);
					paddrSize -= bufSize;
				}
				else
				{									
					if(paddrSize < PAGE_BUFFER_SIZE)
					{
						bufSize = paddrSize;
						paddrSize = 0;
					}
#if A96T418_MODE==0
					else if((paddrSize >= SECTOR_BUFFER_SIZE) && (((paddr%SECTOR_BUFFER_SIZE)==0))) 
					{
						bufSize = SECTOR_BUFFER_SIZE;
						paddrSize -= bufSize;//SECTOR_BUFFER_SIZE;
					}
#endif				
					else
					{
						bufSize = PAGE_BUFFER_SIZE;
						paddrSize -= bufSize;//PAGE_BUFFER_SIZE;
					}
				}
				
				if(bErase)
				{
					ret = Page_Erase_Flash(FLASH_KEY, paddr, bufSize);
					if(ret)
					{
						_nop_();
						break;
					}
				}
				if(bWrite)
				{
					if(bWrite==1)
						ret = Page_Write_Flash(FLASH_KEY, paddr, bufSize, buf);
					else if(bWrite==(u8)0xff)  //prewrite 0x00
						ret = Page_Write_Flash(FLASH_KEY, paddr, bufSize, 0); //prewrite 0x00
						
					if(ret)
					{
						_nop_();
						break;
					}
				}
				paddr = paddr + bufSize;
				buf=buf + bufSize;
				
			}
		}
		else 
		{
			while(1); //malfunction
		}
		User_ID = 0;
	}
	else 
	{
		while(1); //malfunction
	}
	return ret;
}



/**
* @brief	Erase operation of flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 64kbytes(0x0 ~ 0xFFFF)
* @return	status(0 : OK, 1/2 : Failed)
*/
unsigned long sector_addresstmp;
unsigned char Page_Erase_Flash(unsigned int key, unsigned long sector_address, unsigned int buf_size)
{
	unsigned char code *rom_addr = 0x0000;
	unsigned int i = 0;
	unsigned char tmp = 0;
	unsigned char tmp2 = 0;
	unsigned char ret = 0;

	//Disable EA
	tmp = IE;
	//IE &= (~0x80);

	
	//LVI enalbe, safety code
	//tmp2 = LVICR;
	//LVICR = 0x10 | FLASH_LVI;

	if((sector_address+buf_size) > (unsigned long)target_addr_end) 
		buf_size=(target_addr_end-sector_address+1)&0xffff;
	if((sector_address)<(unsigned long)target_addr_start)
		while(1); //malfunction
		
	if(key == FLASH_KEY)
	{
		key ^= FLASH_XOR;

		if(buf_size && (sector_address>=(unsigned long)target_addr_start) && (sector_address <= (unsigned long)target_addr_end) )
		{
			// Enable program mode
			Flash_Enter();

#if A96T418_MODE==0
			// erase
			FEMR = 0x81;	// Select flash and enable control. //FSEL, FEEN
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.	
			FEMR = 0x91;	    // Set Erase mode.   //FSEL, PGM, FEEN
#endif			
#if A96T418_MODE==1
			// erase
			FEMR = 0x81;	// Select flash and enable control.
			FECR = 0x02;	// Reset page buffer.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			FEMR = 0x89;	// Select page buffer.

			//write data to pagebuffer
			for(i=0;i<buf_size;i++){
				Flash_LoadData(0, sector_address+i);
			}

			FEMR = 0x91;	    // Set Erase mode.
			FETCR = WAITTIME;	// Set Erase time. 
#endif
			
			// Set Flash Sector Address as used area
			FEARH = (sector_address >> 16) & 0xFF;
			FEARM = (sector_address >> 8) & 0xFF;
			FEARL = (sector_address) & 0xFF;
			sector_addresstmp=sector_address;

			//Check Power stable by LVI 
			LVICR &= ~0x20;
			NOP;
			if((LVICR & 0x20) == 0x00)
			{
				// Check User_ID
				if(User_ID == FLASH_USER_ID)
				{
					// Check valid of Flash Sector Address range
					if(buf_size && (sector_address>=(unsigned long)target_addr_start) && (sector_address <= (unsigned long)target_addr_end) )
					{
						if((key ^ FLASH_XOR) == FLASH_KEY)
						{
#if A96T418_MODE==0
							//write data to load			
							if(1)
							{
								if(buf_size==SECTOR_BUFFER_SIZE)
								{									
									//P20=1; P2IO|=0x1;
									FECR=0x4A; // Start Erase.  //SECT, nFERST, WRITE
									_nop_(); //one nop recommended
									while ( !( FESR & 0x80));  // Read status register.     //PEVBSY
									//P20=0;
									_nop_();
								}
								else //if(buf_size==PAGE_BUFFER_SIZE)
								{									
									//P20=1; P2IO|=0x1;
									FECR=0x0A; // Start Erase.  //nFERST, WRITE
									_nop_(); //one nop recommended
									while ( !( FESR & 0x80));  // Read status register.     //PEVBSY
									//P20=0;
									_nop_();
								}								
							}					
#endif							
#if A96T418_MODE==1
							// Flase Erase
							FECR = 0x0B;	// Start Erase.
							_nop_();//Dummy instruction, This instruction must be needed.
							while( !( FESR & 0x80));		// Read status register.
							_nop_();
#endif							
						}
						
						FEMR=0x00;	//					
						Flash_Exit();    // Set flash to normal mode.
						//verify data
//						for(i = 0; i < buf_size; i++)
//						{
//							if(rom_addr[sector_address + i] != FLASH_BLABK_TATA)
//							{
//								ret = 2;
//								break;
//							}
//						}
					}
					else {
						Flash_Exit();    // Set flash to normal mode.
						while(1); //malfunction
					}
				}
				else {
					Flash_Exit();    // Set flash to normal mode.
					while(1); //malfunction
				}
			}
			else
			{
				Flash_Exit();    // Set flash to normal mode.
				while(1); //malfunction
				//ret = 1;//LVI error
			}
			Flash_Exit();			            // Set flash to normal mode.
			// Set Flash Sector Address as Dummy address
			FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
			FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;		//Flash Sector Address Middle Register
			FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;		//Flash Sector Address Low Register
		}				
		else
			while(1); //malfunction
	}
	else 
		while(1); //malfunction
	//LVICR = tmp2;
	//IE = tmp;
	
	return ret;
}


/**
* @brief	Wrtie operation of flash memory.
* @param    key 	This parameter contains the address of Flash memory.
*
*					- safety code for operation of flash memory
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 64kbytes(0x0 ~ 0xFFFF)
* @param    buf_size 	This parameter contains the size of writing Flash data.
* @param    buf 	This parameter contains the buffer of writing Flash data
* @return	status(0 : OK, 1/4 : Failed)
*/
unsigned char Page_Write_Flash(unsigned int key, unsigned long sector_address, unsigned int buf_size, unsigned char *buf)
{
	unsigned long pdtBuf=0x00; //for prewrite 0x00
	static unsigned char *pdt;
	unsigned char code *rom_addr=0x0000;
	unsigned int i = 0;
	unsigned char tmp = 0;
	unsigned char tmp2 = 0;
	unsigned int tmp3 = 0;
	unsigned char ret = 0;
			
	//Disable EA
	tmp = IE;
	//IE &= (~0x80);
	
	//LVI enalbe, 2.32V
	//tmp2 = LVICR;
	//LVICR = 0x10 | FLASH_LVI;

	if((sector_address+buf_size) > (unsigned long)target_addr_end) 
		buf_size=(target_addr_end-sector_address+1)&0xffff;
	if((sector_address)<(unsigned long)target_addr_start)
		while(1); //malfunction
	
	if(key == FLASH_KEY)
	{
		key ^= FLASH_XOR;

		if(buf_size && (sector_address>=(unsigned long)target_addr_start) && (sector_address <= (unsigned long)target_addr_end) )
		{
			// Enable program mode
			Flash_Enter();

#if A96T418_MODE==0
			// write
			FEMR = 0x81;	// Select flash and enable control. //FSEL, FEEN
			//FECR = 0x02;	// Reset page buffer.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			FEMR = 0xA1;            // Set write mode.  //FSEL, PGM, FEEN
#endif			
#if A96T418_MODE==1
			// write
			FEMR = 0x81;	// Select flash and enable control.
			FECR = 0x02;	// Reset page buffer.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			_nop_( );	//Dummy instruction, This instruction must be needed.
			FEMR = 0x89;	// Select page buffer.

			//write data to pagebuffer			
			pdt = buf;
			for(i=0;i<buf_size;i++){
				Flash_LoadData(*pdt, (unsigned long)(sector_address+i)); 
				pdt++;
			}
			
			FEMR = 0xA1;            // Set write mode.
			FETCR = WAITTIME;       // Set Erase time. 
#endif			
			
			// Set Flash Sector Address as used area
			FEARH = (sector_address >> 16) & 0xFF;
			FEARM = (sector_address >> 8) & 0xFF;
			FEARL = (sector_address) & 0xFF;
			sector_addresstmp=sector_address;
			
			//Check Power stable by LVI 
			LVICR &= ~0x20;
			NOP;
			if((LVICR & 0x20) == 0x00)
			{
				// Check User_ID1/2
				if(User_ID == FLASH_USER_ID)
				{
					// Check valid of Flash Sector Address range
					if(buf_size && (sector_address>=(unsigned long)target_addr_start) && (sector_address <= (unsigned long)target_addr_end) )
					{
						if((key ^ FLASH_XOR) == FLASH_KEY)
						{
#if A96T418_MODE==0
							//write data load		
							pdt = buf;
								
							for(i=0;i<buf_size;i+=4){
								if(!buf){
									pdt=(unsigned char *)&pdtBuf; //for prewrite 0x00
								}
								sector_addresstmp=sector_address+i;
								FEDR0=*pdt++;
								FEDR1=*pdt++;
								FEDR2=*pdt++;
								FEDR3=*pdt++;							
								//P20=1; P2IO|=0x1;
								FECR=0x0A; // Start write.   //nFERST, WRITE
								_nop_(); //one nop recommended
								while ( !( FESR & 0x80));       //PEVBSY
								//P20=0;
								_nop_();
							}	
#endif							
#if A96T418_MODE==1
							// Flase Write
							FECR = 0x0B;		        // Start program.
							_nop_();//Dummy instruction, This instruction must be needed.						
							while ( !( FESR & 0x80));       //
							_nop_();
#endif	
						}

						FEMR = 0x00;            //
						Flash_Exit();    // Set flash to normal mode.
						//verify data
						pdt = buf;
//						for(i = 0; i < buf_size; i++)
//						{							
//							if(rom_addr[sector_address + i] != *pdt)
//							{
//								ret = 4;
//								break;
//							}
//							pdt++;
//						}
					}
					else {
						Flash_Exit();    // Set flash to normal mode.
						while(1); //malfunction
					}
				}
				else {
					Flash_Exit();    // Set flash to normal mode.
					while(1); //malfunction
				}

			}
			else
			{
				Flash_Exit();    // Set flash to normal mode.
				while(1); //malfunction
				//ret = 1;//LVI error
			}
			Flash_Exit();			            // Set flash to normal mode.
			// Set Flash Sector Address as Dummy address
			FEARH = (FLASH_ADDR_DUMMY >> 16) & 0x0f;	//Flash Sector Address High Register
			FEARM = (FLASH_ADDR_DUMMY >> 8) & 0xff;		//Flash Sector Address Middle Register
			FEARL = (FLASH_ADDR_DUMMY >> 0) & 0xff;		//Flash Sector Address Low Register
		}
		else 
			while(1); //malfunction
			
	}
	else 
		while(1); //malfunction
	//LVICR = tmp2;
	//IE = tmp;	
	return ret;
}


/**
* @brief	Read operation of flash memory.
* @param    sector_address 	This parameter contains the address of Flash memory.
*
*					- address range : 64kbytes(0x0 ~ 0xfFFF)
* @param    size 	This parameter contains the size of reading Flash data.
* @param    buf 	This parameter contains the data to read flash memory.
* @return	NONE
*/
void Read_Flash(unsigned int sector_address, unsigned int buf_size, unsigned char *buf)
{
	unsigned char code *rom_addr=0x0000;
	unsigned int i = 0;

	for(i = 0; i < buf_size; i++)
	{
		buf[i] = rom_addr[sector_address + i];
	}
}

volatile unsigned long checksum=0;
uint16_t FEARML_addr_before, FEARML1_addr_before;
uint16_t FEARML_addr_after, FEARML1_addr_after;
uint32_t Flash_CheckSum(uint16_t startaddr, uint16_t endaddr)
{
	
	checksum=0;
	Flash_Enter();
	
	// checksum
	if(startaddr>endaddr) //Full code checksum 
	{

		FEMR = 0x81;	// Select flash and enable control. //FSEL, FEEN
		FETR = 0x08;	// Reset page buffer.(from T336)
		FECR = 0x06;	// Start auto-verify of Flash, Reset checksum
		_nop_();
		while ( !( FESR & 0x80));
		_nop_();
	}
	else // code range checksum 
	{
		// Checksum start address
		FEARM = startaddr>>8; 
		FEARL 	= startaddr&0xFF; 
		FEARM1 = endaddr>>8; 
		FEARL1 	= endaddr&0xFF; 
		FEARML_addr_before=(FEARM<<8)|FEARL;
		FEARML1_addr_before=(FEARM1<<8)|FEARL1;
		FEMR = 0x81;	// Select flash and enable control.
		FETR = 0x00;	// test register (from T356)
		FECR = 0x06;	// Start auto-verify of Flash, Reset checksum
		_nop_();
		while ( !( FESR & 0x80));
		_nop_();
	}

#if A96T418_MODE==1
	checksum=FEARH;
	checksum<<=8;
	checksum|=FEARM;
	checksum<<=8;
	checksum|=FEARL;
#endif
#if A96T418_MODE==0
	checksum=CHECKSUMH;
	checksum<<=8;
	checksum|=CHECKSUMM;
	checksum<<=8;
	checksum|=CHECKSUML;

#endif	
	
	Flash_Exit();
	FEARML_addr_after=(FEARM<<8)|FEARL;
	FEARML1_addr_after=(FEARM1<<8)|FEARL1;
	return checksum;
}


/* --------------------------------- End Of File ------------------------------ */