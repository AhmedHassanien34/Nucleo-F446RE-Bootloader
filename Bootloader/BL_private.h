/*
 * BL_private.h
 *
 *  Created on: Oct 22, 2023
 *      Author: Torres
 */

#ifndef INC_BL_PRIVATE_H_
#define INC_BL_PRIVATE_H_

#define CRC_SUCCESS			0u
#define CRC_FAIL 			1u

#define BL_VERSION			1u

#define  READING_SUCCESS     0u
#define  READING_ERROR       1u

#define VALID_ADDRESS		0u
#define INVALID_ADDRESS		1u

#define MAX_NUMB_SECTOR 	8u
#define MASS_ERASE			0xff

#define WRITTING_SUCCESS	0u
#define WRITTING_ERROR		1u

#define CRC_LENGTH_CMD      4u

#define WRITE_PROTECTION		1u
#define READ_WRITE_PROTECTION	2u

#define FLASH_TYPEERASE_SECTORS         0x00000000U  /*!< Sectors erase only          */
#define FLASH_TYPEERASE_MASSERASE       0x00000001U  /*!< Flash Mass erase activation */

#define FLASH_VOLTAGE_RANGE_1        0x00000000U  /*!< Device operating range: 1.8V to 2.1V                */
#define FLASH_VOLTAGE_RANGE_2        0x00000001U  /*!< Device operating range: 2.1V to 2.7V                */
#define FLASH_VOLTAGE_RANGE_3        0x00000002U  /*!< Device operating range: 2.7V to 3.6V                */
#define FLASH_VOLTAGE_RANGE_4        0x00000003U  /*!< Device operating range: 2.7V to 3.6V + External Vpp */

#define FLASH_BANK_1     1U /*!< Bank 1   */

#define DBGMCU_IDCODE				*((volatile uint32_t*) 0xE0042000)
#define RDP_USER_OPTION_WORD		*((volatile uint32_t*) 0x1FFFC000)
#define WRP_OPTION_WORD             *((volatile uint32_t *)0x1FFFC008)

typedef enum
{
  OK       = 0x00U,
  ERROR    = 0x01U,
  BUSY     = 0x02U,
  TIMEOUT  = 0x03U
} Status_TypeDef;



static void voidSendNack ( void );

static void voidSendAck(uint8_t copy_u8ReplyLength);

static uint8_t u8ExecuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSectors);

static uint8_t u8VerifyCRC(uint8_t* copy_pu8DataArr, uint8_t copy_u8Length , uint32_t copy_u32HostCRC );

static uint8_t u8ValidateAddress(uint32_t Copy_u32Address);

static uint8_t u8ExecuteMemWrite(uint8_t* Copy_pu8Buffer , uint32_t Copy_u32Address , uint8_t Copy_u8Length);

static uint8_t u8ExcuteMemoryRead(uint32_t Copy_u32Address , uint8_t Copy_u8Length , uint32_t * Copy_pu32Destination);

static uint8_t u8ExcuteRWProtect(uint8_t Copy_u8SectorDetails , uint8_t Copy_u8ProtectionMode);

#endif /* INC_BL_PRIVATE_H_ */
