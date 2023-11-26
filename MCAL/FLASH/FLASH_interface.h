/**
 ******************************************************************************
 * @file           : FLASH_interface.h
 * @author         : Diea Abdeltwab
 * @layer          : MCAL
 * @brief          : Version 1 For STM32F411RE Drivers
 * @date           : 27/10/2023
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
#ifndef  FLASH_INTERFACE_H
#define  FLASH_INTERFACE_H

typedef enum{
    FLASH_PSIZE_BYTE        = 0x00, /**< Supply voltage from 1.7V to 3.6V */
    FLASH_PSIZE_HALFWORD    = 0x01, /**< Supply voltage from 2.1V to 3.6V */
    FLASH_PSIZE_WORD        = 0x02, /**< Supply voltage from 2.7V to 3.6V */
    FLASH_PSIZE_DOUBLEWORD  = 0x03  /**< Supply voltage from 2.7V to 3.6V with external Vpp 8V to 9V */
}flash_psize_t;

typedef struct{
    uint16_t nWRP;   /**< Not Write Protect */
    uint8_t  RDP;    /**< Read Protect */
    uint8_t  user;   /**< User configuration */
    uint8_t  BOR;    /**< BOR reset level */
}OPT_Cfg_t;

typedef struct
{
  uint32_t TypeErase;   /*!< Mass erase or sector Erase.
                             This parameter can be a value of @ref FLASHEx_Type_Erase */

  uint32_t Banks;       /*!< Select banks to erase when Mass erase is enabled.
                             This parameter must be a value of @ref FLASHEx_Banks */

  uint32_t Sector;      /*!< Initial FLASH sector to erase when Mass erase is disabled
                             This parameter must be a value of @ref FLASHEx_Sectors */

  uint32_t NbSectors;   /*!< Number of sectors to be erased.
                             This parameter must be a value between 1 and (max number of sectors - value of Initial sector)*/

  uint32_t VoltageRange;/*!< The device voltage range which defines the erase parallelism
                             This parameter must be a value of @ref FLASHEx_Voltage_Range */

} FLASH_EraseInitTypeDef;

uint8_t Flash_EraseSector(uint8_t sector);

uint8_t FLASH_u8Erase(FLASH_EraseInitTypeDef *Copy_pEraseInit, uint32_t *Local_pu32SectorError);

uint8_t Flash_WriteMemoryByte(uint32_t address, uint8_t data);

uint8_t Flash_WriteMemoryHalfWord(uint32_t address, uint16_t data);

uint8_t Flash_WriteMemoryWord(uint32_t address, uint32_t data);

uint8_t Flash_WriteMemoryDoubleWord(uint32_t address, uint64_t data);

uint8_t Flash_EnRWProtection(uint8_t sectors, uint8_t protection_mode);

uint8_t Flash_DisRWProtection(void);

void Flash_Unlock(void);

void Flash_Lock(void);

void Flash_OPTUnlock(void);

void Flash_OPTLock(void);

void Flash_SetPSIZE(flash_psize_t psize);

uint8_t Flash_Busy(void);

void Flash_GetOBCfg(OPT_Cfg_t* OPTCfg);


#endif

