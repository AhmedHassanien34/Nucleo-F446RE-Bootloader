#include <stdint.h>
#include <stdio.h>

#include "../LIB/Stm32F466xx.h"

#include "../MCAL/UART/USART_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/FLASH/FLASH_interface.h"

#include "../SERVICE/CRC/CRC_interface.h"

#include "BL_config.h"
#include "BL_interface.h"
#include "BL_private.h"


extern USARTconfig_t UART_BL;



void BL_voidHandleGetVerCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t Local_u8BLVersion , Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */

		Local_u8BLVersion = BL_VERSION;

		MUSART_u8TransmitSynch( USART_2 , &Local_u8BLVersion , 1);
	}
	else
	{
		voidSendNack();
	}

}
void BL_voidHandleGetHelpCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_pu8BLCommands[]=
		{
				BL_GET_VER   			,
				BL_GET_HELP   			,
				BL_GET_CID   			,
				BL_GET_RDP_STATUS   	,
				BL_GO_TO_ADDR  			,
				BL_FLASH_ERASE  		,
				BL_MEM_WRITE 			,
				BL_EN_RW_PROTECT  		,
				BL_MEM_READ 			,
				BL_READ_SECTOR_STATUS   ,
				BL_OTP_READ	   			,
				BL_DIS_WR_PROTECT
		};
		voidSendAck(sizeof(Local_pu8BLCommands)); /*Bootloader version has size of 1 Byte */

		MUSART_u8TransmitSynch( USART_2 ,(uint8_t*) &Local_pu8BLCommands , sizeof(Local_pu8BLCommands) );
	}
	else
	{
		voidSendNack();
	}
}

void BL_voidHandleGetCIDCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint16_t Loacl_u16DeviceID = (DBGMCU_IDCODE & 0x0fff);

		voidSendAck(2u); /*Bootloader version has size of 1 Byte */

		MUSART_u8TransmitSynch( USART_2 , (uint8_t*)&Loacl_u16DeviceID , 2);

	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHandleGetVerRDPStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8RDPStatus = (uint8_t)((RDP_USER_OPTION_WORD >> 8) & 0xFF);
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */
		MUSART_u8TransmitSynch( USART_2 , (uint8_t*)&Local_u8RDPStatus , 1 );

	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHandleGoToAddressCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint32_t Local_u32Address;
		uint8_t Local_u8AddressValidStatus;

		voidSendAck(1u); /*Bootloader version has size of 1 Byte */

		/* Extract the Address */
		Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);

		Local_u8AddressValidStatus = u8ValidateAddress(Local_u32Address);

		MUSART_u8TransmitSynch( USART_2 , &Local_u8AddressValidStatus , 1);

		if(Local_u8AddressValidStatus == VALID_ADDRESS)
		{


			/*Define a Pointer to function*/
			void(*Local_pvFuncPtr)(void) = NULL;

			Local_u32Address |=1; //increment address by 1 to make t-bit = 1

			Local_pvFuncPtr = (void*)Local_u32Address;

			Local_pvFuncPtr();
		}

	}
	else
	{
		voidSendNack();
	}
}


void BL_voidHandleFlashEraseCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8EraseStatus;

		voidSendAck(1u); /*Bootloader version has size of 1 Byte */

		GPIO_u8SetPinValue(PORTA,PIN5,PIN_HIGH);

		Local_u8EraseStatus = u8ExecuteFlashErase(copy_pu8CmdPacket[2], copy_pu8CmdPacket[3]);

		GPIO_u8SetPinValue(PORTA,PIN5,PIN_LOW);

		MUSART_u8TransmitSynch( USART_2 , (uint8_t*) &Local_u8EraseStatus , 1 );

	}
	else
	{
		voidSendNack();
	}
}

void BL_voidHandleMemWriteCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8writingStatus;

		uint32_t Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]);  /* Extract the base memory addres */

		uint8_t Local_u8AddressStatus = u8ValidateAddress(Local_u32Address);

		voidSendAck(1u); /*Send the Ack */

		if (Local_u8AddressStatus == VALID_ADDRESS)
		{
			uint8_t Local_u8PayloadLength = copy_pu8CmdPacket[6];

			Local_u8writingStatus = u8ExecuteMemWrite(&copy_pu8CmdPacket[7],Local_u32Address,Local_u8PayloadLength);

		}
		else
		{
			Local_u8AddressStatus = WRITTING_ERROR;
		}

		MUSART_u8TransmitSynch( USART_2 , &Local_u8writingStatus , 1);

	}
	else
	{
		voidSendNack();
	}
}

void BL_voidHandleEnRWProtectCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8SectorDetails;  /*to hold Sectors*/
		uint8_t Local_u8ProtectionMode; /*to hold Protection mode*/
		uint8_t Local_u8Status;
		/*Extract Sector Details*/
		Local_u8SectorDetails =  copy_pu8CmdPacket[2];
		/*Extract Protection Details*/
		Local_u8ProtectionMode = copy_pu8CmdPacket[3];
		voidSendAck(1u);  /*Send the acknowledge*/
		Local_u8Status = u8ExcuteRWProtect(Local_u8SectorDetails ,Local_u8ProtectionMode);
		MUSART_u8TransmitSynch( USART_2 , &Local_u8Status , 1);

	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHandleMemReadCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8ReadStatus,Local_u8AddressValidate;
		uint32_t Local_u8Destination[255];
		uint32_t Local_u32Address = *((uint32_t*)&copy_pu8CmdPacket[2]); /*Extract memory address*/
		uint8_t Local_u8Length = copy_pu8CmdPacket[6];
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */
		Local_u8AddressValidate = u8ValidateAddress(Local_u32Address);

		if(Local_u8AddressValidate == VALID_ADDRESS)
		{
			Local_u8ReadStatus = u8ExcuteMemoryRead(Local_u32Address , Local_u8Length,Local_u8Destination);
		}
		else
		{
			Local_u8ReadStatus = READING_ERROR;
		}

		MUSART_u8TransmitSynch( USART_2 , &Local_u8ReadStatus , 1);

	}
	else
	{
		voidSendNack();
	}
}
void BL_voidHandleReadSectorStatusCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint16_t Local_u16SectorStatus = (WRP_OPTION_WORD & 0xffff);
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */
		MUSART_u8TransmitSynch( USART_2 , &Local_u16SectorStatus , 1);
	}
	else
	{
		voidSendNack();
	}
}


void BL_voidHandleOTPReadCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */
	}
	else
	{
		voidSendNack();
	}
}

void BL_voidHandleDisRWProtectCmd(uint8_t* copy_pu8CmdPacket)
{
	uint8_t  Local_u8CRCStatus , Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = copy_pu8CmdPacket[0] + 1; /* the first byte alreaady includes the length to follow */

	Local_u32HostCRC = *((uint32_t*)(copy_pu8CmdPacket + Local_u8CmdLen - 4));

	Local_u8CRCStatus = u8VerifyCRC(copy_pu8CmdPacket, (Local_u8CmdLen-4), Local_u32HostCRC);

	if (Local_u8CRCStatus == CRC_SUCCESS)
	{
		uint8_t Local_u8ErrorStatus = 0 ;
		voidSendAck(1u); /*Bootloader version has size of 1 Byte */
		Flash_OPTUnlock();
		Local_u8ErrorStatus = Flash_DisRWProtection();
		Flash_OPTLock();
		MUSART_u8TransmitSynch( USART_2 , &Local_u8ErrorStatus , 1);
	}
	else
	{
		voidSendNack();
	}
}


/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/


static void voidSendAck(uint8_t copy_u8ReplyLength)
{
	uint8_t Local_u8AckBuffer[2] = {BL_ACK , copy_u8ReplyLength};

	MUSART_u8TransmitSynch( USART_2 , (uint8_t*) &Local_u8AckBuffer , 2 );
}

static void voidSendNack(void)
{
	uint8_t Local_u8NackBuffer = BL_NACK;

	MUSART_u8TransmitSynch( USART_2 , &Local_u8NackBuffer , 1);
}

static uint8_t u8VerifyCRC(uint8_t* copy_pu8DataArr, uint8_t copy_u8Length , uint32_t copy_u32HostCRC )
{
	uint8_t Local_u8Iterator , Local_u8CRCStatus;
	uint32_t Local_u32AccCRC, Local_u32Temp;

	for(Local_u8Iterator = 0; Local_u8Iterator < copy_u8Length; Local_u8Iterator++)
	{
		Local_u32Temp = copy_pu8DataArr[Local_u8Iterator];
		Local_u32AccCRC = MCRC_u32Accumulate( &Local_u32Temp , 1);
	}

	/* Reset CRC Calculation unit*/
	MCRC_voidDRreset();

	if ( Local_u32AccCRC == copy_u32HostCRC )
	{
		Local_u8CRCStatus = CRC_SUCCESS;
	}
	else
	{
		Local_u8CRCStatus = CRC_FAIL;
	}

	return Local_u8CRCStatus;
}

static uint8_t u8ValidateAddress(uint32_t Copy_u32Address)
{
	/*Address is valid if it is within : SRAM or Flash*/

	uint8_t Local_u8AddressStatus;

	if ((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else if ((Copy_u32Address >= SRAM1_BASE) && (Copy_u32Address <= (SRAM1_BASE + (128*1024))))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else
	{
		Local_u8AddressStatus = INVALID_ADDRESS;
	}

	return Local_u8AddressStatus;
}

static uint8_t u8ExecuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSectors)
{
	Status_TypeDef Local_ErrorStatus = OK;
	uint8_t Local_u8RemainingSectores;

	if ((Copy_u8NumberOfSectors > MAX_NUMB_SECTOR) && (Copy_u8SectorNumber != MASS_ERASE))
	{
		Local_ErrorStatus = ERROR;
	}
	else if ((Copy_u8SectorNumber > 7) && (Copy_u8SectorNumber != MASS_ERASE))

	{
		Local_ErrorStatus = ERROR;
	}
	else
	{
		FLASH_EraseInitTypeDef Local_MyErase;
		uint32_t Local_u32SectorError ;

		if (Copy_u8SectorNumber == 0xff)
		{
			/* Mass Erase operation is required */
			Local_MyErase.TypeErase = FLASH_TYPEERASE_MASSERASE;
		}
		else
		{
			/* Sector Erase operation is required */
			Local_u8RemainingSectores = 8 - Copy_u8SectorNumber;

			if (Copy_u8NumberOfSectors > Local_u8RemainingSectores)
			{
				/* If number of sectors is bigger than max, make it equal to the maximum*/
				Copy_u8NumberOfSectors = Local_u8RemainingSectores;
			}
			else
			{
				/*Do nothing*/
			}
			Local_MyErase.TypeErase = FLASH_TYPEERASE_SECTORS;
			Local_MyErase.Sector = Copy_u8SectorNumber;
			Local_MyErase.NbSectors = Copy_u8NumberOfSectors;
		}
		Local_MyErase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		Local_MyErase.Banks = FLASH_BANK_1;

		/* Unlock the flash before erasing*/
		Flash_Unlock();

		Local_ErrorStatus = FLASH_u8Erase(&Local_MyErase,&Local_u32SectorError);

		/*Lock the flash again*/
		Flash_Lock();
	}
	return Local_ErrorStatus;
}

static uint8_t u8ExecuteMemWrite(uint8_t* Copy_pu8Buffer , uint32_t Copy_u32Address , uint8_t Copy_u8Length)
{
	uint8_t Local_u8ErrorStatus = OK;

	if ((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		uint8_t Local_u8Iterator;

		/* Unlock the flash before writing*/
		Flash_Unlock();

		for(Local_u8Iterator=0;Local_u8Iterator<Copy_u8Length;Local_u8Iterator++)
		{
			Local_u8ErrorStatus =  Flash_WriteMemoryByte(Copy_u32Address+Local_u8Iterator,Copy_pu8Buffer[Local_u8Iterator]);
		}

		Flash_Lock();
	}
	else
	{
		/*Writing in SRAM case*/
		uint8_t Local_u8Iterator;
		uint8_t* Local_pu8Dest = (uint8_t*)Copy_u32Address;

		for(Local_u8Iterator=0;Local_u8Iterator<Copy_u8Length;Local_u8Iterator++)
		{
			Local_pu8Dest[Local_u8Iterator]= Copy_pu8Buffer[Local_u8Iterator];
		}

	}

	return Local_u8ErrorStatus;
}

static uint8_t u8ExcuteMemoryRead(uint32_t Copy_u32Address , uint8_t Copy_u8Length , uint32_t * Copy_pu32Destination)
{
	uint8_t Local_u8ErrorStatus = OK;

	return Local_u8ErrorStatus;
}

static uint8_t u8ExcuteRWProtect(uint8_t Copy_u8SectorDetails , uint8_t Copy_u8ProtectionMode)
{
	uint8_t Local_u8ErrorStatus = OK;
	uint8_t Local_u8Iterator;
	for(Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		if(((Copy_u8SectorDetails >> Local_u8Iterator ) & 1 )== 1)
		{
			if(((Copy_u8ProtectionMode >> Local_u8Iterator ) & 1 )== 0)
			{
				/*Write protection Nedded*/
				Flash_OPTUnlock();
				Local_u8ErrorStatus = Flash_EnRWProtection(Local_u8Iterator , WRITE_PROTECTION);
				Flash_OPTLock();
			}
			else
			{
				/*Read Write Protection Nedded*/
				Flash_OPTUnlock();
				Local_u8ErrorStatus = Flash_EnRWProtection(Local_u8Iterator , READ_WRITE_PROTECTION);
				Flash_OPTLock();
			}
		}
	}
	return Local_u8ErrorStatus;
}



