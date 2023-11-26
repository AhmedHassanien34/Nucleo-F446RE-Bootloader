#include <stdint.h>

#include "../../LIB/Stm32F466xx.h"
#include "../../LIB/ErrorType.h"


#include "FLASH_config.h"
#include "FLASH_private.h"
#include "FLASH_interface.h"
/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

uint8_t Flash_EraseSector(uint8_t sector){

	/* Check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Unlock Flash to perform erase operation */
	Flash_Unlock();

	if(sector != 0xFF){
		/* Set Sector Erase bit in Flash Control Register */
		FLASH->CR |= (1 << FLASH_CR_SER);
		/* Select the sector to be erased in the SNB bit in Flash Control Register */
		FLASH->CR &= ~(0x0F << FLASH_CR_SNB); /* Clear the SNB bits */
		FLASH->CR |= ((0x07 & sector) << FLASH_CR_SNB);
	}
	else{
		/* Set Mass Erase bit in Flash Control Register */
		FLASH->CR |= (1 << FLASH_CR_MER);
	}
	/* Set the STRT bit in Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_STRT);

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/* Lock Flash Control Register */
	Flash_Lock();

	return 0;
}

uint8_t FLASH_u8Erase(FLASH_EraseInitTypeDef *Copy_pEraseInit, uint32_t *Local_pu32SectorError)
{
	uint8_t Local_u8ErrorStatus = OK;
	if (Local_u8ErrorStatus == OK)
	{
		/*Initialization of SectorError variable*/
		*Local_pu32SectorError = 0xFFFFFFFFU;
		if (Copy_pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
		{
			/*Mass erase to be done*/
			voidMassErase((uint8_t) Copy_pEraseInit->VoltageRange, Copy_pEraseInit->Banks);
			/* if the erase operation is completed, disable the MER Bit */
			FLASH->CR &= (~(FLASH_CR_MER_Msk << FLASH_CR_MER));
		}
		else
		{
			/* Erase by sector by sector to be done*/
			for ( uint32_t Local_u8Index = Copy_pEraseInit->Sector; Local_u8Index < (Copy_pEraseInit->NbSectors + Copy_pEraseInit->Sector); Local_u8Index++)
			{
				voidEraseSector(Local_u8Index, (uint8_t) Copy_pEraseInit->VoltageRange);
				/* If the erase operation is completed, disable the SER and SNB Bits */
				CLEAR_BIT(FLASH->CR, ((FLASH_CR_SER_Msk << FLASH_CR_SER) | (FLASH_CR_SNB_Msk << FLASH_CR_SNB)));
			}
		}
	}
	return Local_u8ErrorStatus;
}

uint8_t Flash_WriteMemoryByte(uint32_t address, uint8_t data){

	/* check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Set PSIZE bits in the Flash Control Register */
	Flash_SetPSIZE(FLASH_PSIZE_BYTE);

	/* Set Programming bit in the Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_PG);

	/* Write data in flash memory */
	*(uint8_t*)address = data;

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/*Check for any error */
	if(FLASH->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) |
			(1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
		return 1;
	}

	return 0;
}

uint8_t Flash_WriteMemoryHalfWord(uint32_t address, uint16_t data){

	/* check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Set PSIZE bits in the Flash Control Register */
	Flash_SetPSIZE(FLASH_PSIZE_HALFWORD);

	/* Set Programming bit in the Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_PG);

	/* Write data in flash memory */
	*(uint16_t*)address = data;

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/*Check for any error */
	if(FLASH->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) |
			(1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
		return 1;
	}

	return 0;
}

uint8_t Flash_WriteMemoryWord(uint32_t address, uint32_t data){

	/* check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Set PSIZE bits in the Flash Control Register */
	Flash_SetPSIZE(FLASH_PSIZE_WORD);

	/* Set Programming bit in the Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_PG);

	/* Write data in flash memory */
	*(uint32_t*)address = data;

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/*Check for any error */
	if(FLASH->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) |
			(1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
		return 1;
	}

	return 0;
}

uint8_t Flash_WriteMemoryDoubleWord(uint32_t address, uint64_t data){

	/* check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Set PSIZE bits in the Flash Control Register */
	Flash_SetPSIZE(FLASH_PSIZE_DOUBLEWORD);

	/* Set Programming bit in the Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_PG);

	/* Write data in flash memory */
	*(uint32_t*)address = (uint32_t)data;
	*(uint32_t*)(address + 4) = (uint32_t)(data >> 32);

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/*Check for any error */
	if(FLASH->SR & ((1 << FLASH_SR_PGSERR) | (1 << FLASH_SR_PGPERR) |
			(1 << FLASH_SR_PGAERR) | (1 << FLASH_SR_WRPERR))){
		return 1;
	}

	return 0;
}

uint8_t Flash_EnRWProtection(uint8_t sectors, uint8_t protection_mode){

	if(protection_mode == 1){
		/* Check no flash memory operation is ongoing */
		if(FLASH->SR & (1 << FLASH_SR_BSY)){
			return 1;
		}

		/* Unlock Flash to perform erase operation */
		Flash_OPTUnlock();

		/* Set write protection on sectors */
		/* Reset SPRMOD bit in OPTCR register */
		FLASH->OPTCR &= ~(1 << FLASH_OPTCR_SPRMOD);
		/* Set nWRP byte in OPTCR register (0 is protection active) */
		FLASH->OPTCR &= ~(sectors << FLASH_OPTCR_NWRP);

		/* Set the STRT bit in Flash Control Register */
		FLASH->CR |= (1 << FLASH_CR_STRT);

		/* Wait for flash memory operation is finished */
		while(FLASH->SR & (1 << FLASH_SR_BSY));

		/* Lock Flash Control Register */
		Flash_OPTLock();
	}
	else if(protection_mode == 2){
		/* Check no flash memory operation is ongoing */
		if(FLASH->SR & (1 << FLASH_SR_BSY)){
			return 1;
		}

		/* Unlock Flash to perform erase operation */
		Flash_OPTUnlock();

		/* Set read/write protection on sectors */
		/* Set SPRMOD bit in OPTCR register */
		FLASH->OPTCR |= (1 << FLASH_OPTCR_SPRMOD);
		/* Clear nWRP byte in OPTCR register */
		FLASH->OPTCR &= ~(0xFF << FLASH_OPTCR_NWRP);
		/* Set nWRP byte in OPTCR register (1 is protection active) */
		FLASH->OPTCR |= (sectors << FLASH_OPTCR_NWRP);

		/* Set the STRT bit in Flash Control Register */
		FLASH->CR |= (1 << FLASH_CR_STRT);

		/* Wait for flash memory operation is finished */
		while(FLASH->SR & (1 << FLASH_SR_BSY));

		/* Lock Flash Control Register */
		Flash_OPTLock();
	}
	else{
		return 1;
	}

	return 0;
}

uint8_t Flash_DisRWProtection(void){

	/* Check no flash memory operation is ongoing */
	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	/* Unlock Flash to perform erase operation */
	Flash_OPTUnlock();

	/* Set read/write protection on sectors */
	/* Reset SPRMOD bit in OPTCR register */
	FLASH->OPTCR &= ~(1 << FLASH_OPTCR_SPRMOD);
	/* Set nWRP byte in OPTCR register (1 is disabled) */
	FLASH->OPTCR |= (0xFF << FLASH_OPTCR_NWRP);

	/* Set the STRT bit in Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_STRT);

	/* Wait for flash memory operation is finished */
	while(FLASH->SR & (1 << FLASH_SR_BSY));

	/* Lock Flash Control Register */
	Flash_OPTLock();

	return 0;
}

void Flash_Unlock(void){

	/* Write KEY1 and KEY2 in Flash Key Register */
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;
}

void Flash_Lock(void){

	/* Set Lock bit in Flash Control Register */
	FLASH->CR |= (1 << FLASH_CR_LOCK);
}

static void voidMassErase(uint8_t Copy_u8VoltageRange, uint32_t Copy_u32Banks)
{
  /* If the previous operation is completed, proceed to erase all sectors */
  CLEAR_BIT(FLASH->CR, (FLASH_CR_PSIZE_Msk << FLASH_CR_PSIZE_Msk));
  FLASH->CR |= (FLASH_CR_MER_Msk << FLASH_CR_MER_Msk);
  FLASH->CR |= (FLASH_CR_STRT_Msk << FLASH_CR_STRT_Msk) | ((uint32_t)Copy_u8VoltageRange << 8U);
}

void Flash_OPTUnlock(void){

	/* Write KEY1 and KEY2 in Flash Option Key Register */
	FLASH->OPTKEYR = 0x08192A3B;
	FLASH->OPTKEYR = 0x4C5D6E7F;
}

void Flash_OPTLock(void){

	/* Set Lock bit in Flash Option Control Register */
	FLASH->OPTCR |= (1 << FLASH_OPTCR_OPTLOCK);
}

void Flash_SetPSIZE(flash_psize_t psize){

	/* Set PSIZE bits in the Flash Control Register */
	FLASH->CR &= (0x07 << FLASH_CR_PSIZE);
	FLASH->CR |= (psize << FLASH_CR_PSIZE);
}

uint8_t Flash_Busy(void){

	if(FLASH->SR & (1 << FLASH_SR_BSY)){
		return 1;
	}

	return 0;
}

void Flash_GetOBCfg(OPT_Cfg_t* OPTCfg){

	/* Unlock Option Byte Flash area */
	Flash_OPTUnlock();

	/* Get Option Byte configuration */
	/* Get Not Write Protect byte */
	OPTCfg->nWRP = (uint16_t)((FLASH->OPTCR & (0xFFFF << FLASH_OPTCR_NWRP)) >> 16);
	/*Get Read Protect byte */
	OPTCfg->RDP = (uint8_t)((FLASH->OPTCR & (0xFF << FLASH_OPTCR_RDP)) >> 8);
	/* Get User Option bits */
	OPTCfg->user = (uint8_t)(FLASH->OPTCR & 0xE0);
	/* Get BOR bits */
	OPTCfg->BOR = (uint8_t)(FLASH->OPTCR & 0x0C);

	/* Lock Option Byte Flash area */
	Flash_OPTLock();
}
