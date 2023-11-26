
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "LIB/ErrorType.h"
#include "LIB/Utils.h"

#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/UART/USART_interface.h"


#include "APP/BL_interface.h"


#define USER_APP1_BASE_ADDRESS      0x08020000UL
#define USER_APP2_BASE_ADDRESS      0x08040000UL



static void voidGOToBootloader  ( void );
static void voidJumpToUserApp_1 ( void );
static void voidJumpToUserApp_2 ( void );

GPIO_PinConfig_t UART_PIN_TX=
{
		.Port = PORTA,
		.PinNum = PIN2,
		.Mode = ALTERNATE_FUNCTION,
		.AltFunc= AF7,
};
GPIO_PinConfig_t UART_PIN_RX=
{
		.Port = PORTA,
		.PinNum = PIN3,
		.Mode = ALTERNATE_FUNCTION,
		.AltFunc = AF7,
};

USARTconfig_t 	UART_BL = {
		.USARTindex = USART_2,
		.Receiver= RECEIVER_ENABLE,
		.Transmitter = TRANSMITTER_ENABLE,
		.WordLength = DATA_8_BITS,
		.StopBit_t = ONE_BIT,

};

extern GPIO_PinConfig_t User_Led;

extern GPIO_PinConfig_t User_Button;


static uint8_t Local_u8AppIndexFlag = 1 ;

int main(void)
{
	uint8_t Local_u8Btn;

	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOAEN);
	RCC_AHB1EnableCLK(RCC_AHB1ENR_GPIOCEN);
	RCC_APB1EnableCLK(RCC_APB1ENR_USART2EN);
	RCC_APB1EnableCLK(RCC_AHB1ENR_CRCEN);

	GPIO_u8PinInit(&User_Led);
	GPIO_u8PinInit(&User_Button);
	GPIO_u8PinInit(&UART_PIN_TX);
	GPIO_u8PinInit(&UART_PIN_RX);

	MUSART_u8SetConfiguration(&UART_BL );



	/* Loop forever */
	for(;;)
	{
		GPIO_u8GetPinValue(PORTC,PIN13,&Local_u8Btn);

		if (Local_u8Btn == 0 )
		{
			voidGOToBootloader();
		}

		else if ( Local_u8AppIndexFlag == 1 )
		{
			voidJumpToUserApp_1();
		}
		else
		{
			voidJumpToUserApp_2();
		}
	}
}

static void  voidGOToBootloader( void )
{
	uint8_t Local_u8CmdPacket[255]={0};
	while(1)
	{
		memset(Local_u8CmdPacket,0,255);
		/* 1- Length to Follow */
		MUSART_u8ReceiveArraySynch(USART_2 , &Local_u8CmdPacket[0] , 1 );
		/* 2- Command */
		MUSART_u8ReceiveArraySynch(USART_2 , &Local_u8CmdPacket[1] , Local_u8CmdPacket[0]);
		/* 2- Decode Command */
		switch (Local_u8CmdPacket[1])
		{
		case BL_GET_VER   			: BL_voidHandleGetVerCmd(Local_u8CmdPacket);			break;
		case BL_GET_HELP   			: BL_voidHandleGetHelpCmd(Local_u8CmdPacket);           break;
		case BL_GET_CID   			: BL_voidHandleGetCIDCmd(Local_u8CmdPacket);            break;
		case BL_GET_RDP_STATUS   	: BL_voidHandleGetVerRDPStatusCmd(Local_u8CmdPacket);   break;
		case BL_GO_TO_ADDR  		: BL_voidHandleGoToAddressCmd(Local_u8CmdPacket); 	    break;
		case BL_FLASH_ERASE  		: BL_voidHandleFlashEraseCmd(Local_u8CmdPacket);        break;
		case BL_MEM_WRITE 			: BL_voidHandleMemWriteCmd(Local_u8CmdPacket);          break;
		case BL_EN_RW_PROTECT  		: BL_voidHandleEnRWProtectCmd(Local_u8CmdPacket);       break;
		case BL_MEM_READ 			: BL_voidHandleMemReadCmd(Local_u8CmdPacket);           break;
		case BL_READ_SECTOR_STATUS  : BL_voidHandleReadSectorStatusCmd(Local_u8CmdPacket);  break;
		case BL_OTP_READ	   		: BL_voidHandleOTPReadCmd(Local_u8CmdPacket); 	        break;
		case BL_DIS_WR_PROTECT		: BL_voidHandleDisRWProtectCmd(Local_u8CmdPacket);      break;
		default: /* Invalid command from host */											break;
		}
	}
}

static void  voidJumpToUserApp_1 ( void )
{
	void (* Local_pFunResetHandler)(void);

	uint32_t Local_u8ResetHandlerAddress , Local_u32MSPVal ;

	/* value of the main Stack pointer of our main application */
	Local_u32MSPVal = *((volatile uint32_t *)USER_APP1_BASE_ADDRESS );

	/* Set Main Stack Pointer */
	__asm volatile("MSR MSP , %0"::"r"(Local_u32MSPVal));

	/* Reset handler definition function of our main application */
	Local_u8ResetHandlerAddress  =  *((volatile uint32_t *)(USER_APP1_BASE_ADDRESS + 4) );

	/* Fetch the reset Handler address of the user application */
	Local_pFunResetHandler = (void *)Local_u8ResetHandlerAddress;

	/* Jump to Application Reset Handler */
	Local_pFunResetHandler();
}

static void  voidJumpToUserApp_2 ( void )
{
	void (* Local_pFunResetHandler)(void);

	uint32_t Local_u8ResetHandlerAddress , Local_u32MSPVal ;

	/* value of the main Stack pointer of our main application */
	Local_u32MSPVal = *((volatile uint32_t *)USER_APP2_BASE_ADDRESS );

	/* Set Main Stack Pointer */
	__asm volatile("MSR MSP , %0"::"r"(Local_u32MSPVal));

	/* Reset handler definition function of our main application */
	Local_u8ResetHandlerAddress  =  *((volatile uint32_t *)(USER_APP2_BASE_ADDRESS + 4) );

	/* Fetch the reset Handler address of the user application */
	Local_pFunResetHandler = (void *)Local_u8ResetHandlerAddress;

	/* Jump to Application Reset Handler */
	Local_pFunResetHandler();
}

