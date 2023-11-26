/********************************************************************************************/
/********************************************************************************************/
/**************************		Author:  Ahmed Mohamed Mohamed Hassanien        *************/
/**************************		Layer:   LIB								   	*************/
/**************************		SWC:	 STM32F446xx Registers					*************/
/**************************		Version: 1.00 	             					*************/
/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/* Guard of file will call one time in .c  			                                        */
/********************************************************************************************/
#ifndef STM33F446xx_H_
#define STM33F446xx_H_

/**************************************** Various Memories Base Addresses **********************/

#define FLASH_BASE            0x08000000UL /*!< FLASH(up to 1 MB) base address in the alias region                         */
#define SRAM1_BASE            0x20000000UL /*!< SRAM1(112 KB) base address in the alias region                              */
#define SRAM2_BASE            0x2001C000UL /*!< SRAM2(16 KB) base address in the alias region                              */
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region                                */
#define BKPSRAM_BASE          0x40024000UL /*!< Backup SRAM(4 KB) base address in the alias region                         */
#define FMC_R_BASE            0xA0000000UL /*!< FMC registers base address                                                 */
#define QSPI_R_BASE           0xA0001000UL /*!< QuadSPI registers base address                                             */
#define SRAM1_BB_BASE         0x22000000UL /*!< SRAM1(112 KB) base address in the bit-band region                          */
#define SRAM2_BB_BASE         0x22380000UL /*!< SRAM2(16 KB) base address in the bit-band region                           */
#define PERIPH_BB_BASE        0x42000000UL /*!< Peripheral base address in the bit-band region                             */
#define BKPSRAM_BB_BASE       0x42480000UL /*!< Backup SRAM(4 KB) base address in the bit-band region                      */
#define FLASH_END             0x0807FFFFUL /*!< FLASH end address                                                          */
#define FLASH_OTP_BASE        0x1FFF7800UL /*!< Base address of : (up to 528 Bytes) embedded FLASH OTP Area                */
#define FLASH_OTP_END         0x1FFF7A0FUL /*!< End address of : (up to 528 Bytes) embedded FLASH OTP Area                 */

/**************************************** GPIO Register Definition Structure **********************/
#define GPIOA_BASE_ADDRESS 				0x40020000UL
#define GPIOB_BASE_ADDRESS 				0x40020400UL
#define GPIOC_BASE_ADDRESS 				0x40020800UL
#define GPIOD_BASE_ADDRESS 				0x40020C00UL
#define GPIOE_BASE_ADDRESS 				0x40021000UL
#define GPIOF_BASE_ADDRESS 				0x40021400UL
#define GPIOG_BASE_ADDRESS 				0x40021800UL
#define GPIOH_BASE_ADDRESS 				0x40021C00UL

typedef struct
{
	volatile uint32_t MODER;				/* GPIO PORT Mode Register */
	volatile uint32_t OTYPER;               /* GPIO PORT Output type Register */
	volatile uint32_t OSPEEDR;              /* GPIO PORT Output speed Register */
	volatile uint32_t PUPDR;                /* GPIO PORT Pull up/down Register */
	volatile uint32_t IDR;                  /* GPIO PORT Input Data Register */
	volatile uint32_t ODR;                  /* GPIO PORT Output Data Register */
	volatile uint32_t BSRR;                 /* GPIO PORT Bit Set/Reset Register */
	volatile uint32_t LCKR;                 /* GPIO PORT Lock Register */
	volatile uint32_t AFR[2];               /* GPIO PORT Alternate function Register */
}GPIO_RegDef_t;

#define GPIOA       	  ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB             ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC             ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD             ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE             ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF             ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG             ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH             ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)

/**************************************** RCC Peripheral Definition  *****************************/

#define RCC_BASE_ADDRESS				0x40023800U

typedef struct {
	volatile uint32_t CR;         /* Clock control register */
	volatile uint32_t PLLCFGR;    /* PLL configuration register */
	volatile uint32_t CFGR;       /* Clock configuration register */
	volatile uint32_t CIR;        /* Clock interrupt register */
	volatile uint32_t AHB1RSTR;   /* AHB1 peripheral reset register */
	volatile uint32_t AHB2RSTR;   /* AHB2 peripheral reset register */
	volatile uint32_t AHB3RSTR;   /* AHB3 peripheral reset register */
	uint32_t RESERVED0;           /* Reserved */
	volatile uint32_t APB1RSTR;   /* APB1 peripheral reset register */
	volatile uint32_t APB2RSTR;   /* APB2 peripheral reset register */
	uint32_t RESERVED1[2];        /* Reserved */
	volatile uint32_t AHB1ENR;    /* AHB1 peripheral clock enable register */
	volatile uint32_t AHB2ENR;    /* AHB2 peripheral clock enable register */
	volatile uint32_t AHB3ENR;    /* AHB3 peripheral clock enable register */
	uint32_t RESERVED2;           /* Reserved */
	volatile uint32_t APB1ENR;    /* APB1 peripheral clock enable register */
	volatile uint32_t APB2ENR;    /* APB2 peripheral clock enable register */
	uint32_t RESERVED3[2];        /* Reserved */
	volatile uint32_t AHB1LPENR;  /* AHB1 peripheral clock enable in low power mode register */
	volatile uint32_t AHB2LPENR;  /* AHB2 peripheral clock enable in low power mode register */
	volatile uint32_t AHB3LPENR;  /* AHB3 peripheral clock enable in low power mode register */
	uint32_t RESERVED4;           /* Reserved */
	volatile uint32_t APB1LPENR;  /* APB1 peripheral clock enable in low power mode register */
	volatile uint32_t APB2LPENR;  /* APB2 peripheral clock enable in low power mode register */
	uint32_t RESERVED5[2];        /* Reserved */
	volatile uint32_t BDCR;       /* Backup domain control register */
	volatile uint32_t CSR;        /* Clock control & status register */
	uint32_t RESERVED6[2];        /* Reserved */
	volatile uint32_t SSCGR;      /* Spread spectrum clock generation register */
	volatile uint32_t PLLI2SCFGR; /* PLLI2S configuration register */
} RCC_RegDef_t;

#define RCC       	   ((RCC_RegDef_t*)RCC_BASE_ADDRESS)

/******************************* STK Register Definition Structure *******************************/
#define SysTick_BASE_ADDRESS 			0xE000E010UL

typedef struct{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;

}MSTK_RegDef_t;

#define STK  		   ((MSTK_RegDef_t*)SysTick_BASE_ADDRESS)

/******************************* NVIC Register Definition Structure *******************************/
#define NVIC_BASE_ADDRESS 	   			0xE000E100UL

typedef struct{
	volatile uint32_t NVIC_ISER[8];
	volatile uint32_t Reserved1[24];
	volatile uint32_t NVIC_ICER[8];
	volatile uint32_t Reserved2[24];
	volatile uint32_t NVIC_ISPR[8];
	volatile uint32_t Reserved3[24];
	volatile uint32_t NVIC_ICPR[8];
	volatile uint32_t Reserved4[24];
	volatile uint32_t NVIC_IABR[8];
	volatile uint32_t Reserved5[24];
	volatile uint8_t  NVIC_IPR [240];
	volatile uint32_t Reserved6[644];
	volatile uint32_t NVIC_STIR;

}NVIC_RegDef_t;

#define NVIC  		   ((NVIC_RegDef_t*)NVIC_BASE_ADDRESS)

/******************************* SCB Register Definition Structure *******************************/
#define SCB_BASE_ADDRESS 	   			0xE000E008UL

typedef struct{
	uint32_t ACTLR;
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint8_t  SHP[12U];
	uint32_t SHCSR;
}SCB_RegDef_t;

#define  SCB  		   ((SCB_RegDef_t*)SCB_BASE_ADDRESS)

/******************************* SYSCFG Register Definition Structure *******************************/

#define SYSCFG_BASE_ADDRESS		  	0x40013800UL

typedef struct
{
	volatile uint32_t MEMRMP;	 	/* SYSCFG Memory Remap Register */
	volatile uint32_t PMC;		 	/* SYSCFG Peripheral Mode Configuration Register */
	volatile uint32_t EXTICR[4]; 	/* SYSCFG External Interrupt Configuration Registers*/
	uint32_t RESERVED0[2];
	volatile uint32_t CMPCR; 		/* Compensation Cell Control Register */
	uint32_t RESERVED1[2];
	volatile uint32_t CFGR; 		/* SYSCFG Configuration Register */

} SYSCFG_RegDef_t;

#define SYSCFG 			((SYSCFG_RegDef_t *)SYSCFG_BASE_ADDRESS)

/******************************* EXTI Register Definition Structure *******************************/

#define EXTI_BASE_ADDRESS		    0x40013C00UL

typedef struct
{
	volatile uint32_t IMR;	 /* Interrupt Mask Register */
	volatile uint32_t EMR;	 /* Event Mask Register */
	volatile uint32_t RTSR;	 /* Rising Trigger Selection Register */
	volatile uint32_t FTSR;	 /* Falling Trigger Selection Register */
	volatile uint32_t SWIER; /* Software Interrupt Event Register */
	volatile uint32_t PR;	 /* Pending Register */
} EXTI_RegDef_t;

#define EXTI			 ((EXTI_RegDef_t *)EXTI_BASE_ADDRESS)

/******************************* DMA Register Definition Structure *******************************/
#define DMA1_BASE_ADRESS		 0x40026000U
#define DMA2_BASE_ADRESS		 0x40026400U

typedef struct
{
	volatile uint32_t CR;	/* DMA Stream x Configuration Register */
	volatile uint32_t NDTR; /* DMA Stream x Number of Data Register */
	volatile uint32_t PAR;	/* DMA Stream x Peripheral Address Register */
	volatile uint32_t M0AR; /* DMA Stream x Memory 0 Address Register */
	volatile uint32_t M1AR; /* DMA Stream x Memory 1 Address Register */
	volatile uint32_t FCR;	/* DMA Stream x FIFO Control Register */

} DMA_Stream_RegDef_t;

typedef struct
{
	volatile uint16_t ISR[4];				/* DMA Interrupt Status Registers */
	volatile uint16_t IFCR[4];				/* DMA Interrupt Flag Clear Registers */
	volatile DMA_Stream_RegDef_t STREAM[8]; /* DMA Stream Registers */

} DMA_RegDef_t;

#define DMA1              ((DMA_RegDef_t *)DMA1_BASE_ADDRESS)
#define DMA2              ((DMA_RegDef_t *)DMA2_BASE_ADDRESS)

typedef enum
{
	EN = 0,		 /* DMA Stream Enable */
	DMEIE = 1,	 /* Direct Mode Error Interrupt Enable */
	TEIE = 2,	 /* Transfer Error Interrupt Enable */
	HTIE = 3,	 /* Half Transfer Interrupt Enable */
	TCIE = 4,	 /* Transfer Complete Interrupt Enable */
	PFCTRL = 5,	 /* Peripheral Flow Controller */
	DIR = 6,	 /* Data Transfer Direction */
	CIRC = 8,	 /* Circular Mode */
	PINC = 9,	 /* Peripheral Increment Mode */
	MINC = 10,	 /* Memory Increment Mode */
	PSIZE = 11,	 /* Peripheral Size */
	MSIZE = 13,	 /* Memory Size */
	PINCOS = 15, /* Peripheral Increment Offset Size */
	PL = 16,	 /* Priority Level */
	DBM = 18,	 /* Double Buffer Mode */
	CT = 19,	 /* Current Target Memory */
	PBURST = 21, /* Peripheral Burst Transfer Configuration */
	MBURST = 23, /* Memory Burst Transfer Configuration */
	CHSEL = 25	 /* Channel Selection */
} DMA_STREAM_CONFIGURATION_BITS_t;

typedef enum
{
	FTH = 0,   /* FIFO Threshold Selection */
	DMDIS = 2, /* Direct Mode Disable */
	FS = 3,	   /* FIFO Status */
	FEIE = 7   /* FIFO Error Interrupt Enable */
} DMA_FIFO_CONTROL_BITS_t;



/******************************* I2C Register Definition Structure *******************************/


/******************************* UART Register Definition Structure *******************************/

#define USART1_BASE_ADDRESS 0x40011000UL
#define USART2_BASE_ADDRESS 0x40004400UL
#define USART3_BASE_ADDRESS 0x40004800UL
#define UART4_BASE_ADDRESS  0x40004C00UL
#define UART5_BASE_ADDRESS  0x40005000UL
#define USART6_BASE_ADDRESS 0x40011400UL

typedef struct{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_RegDef_t;

#define  USART1  	   ((USART_RegDef_t*)USART1_BASE_ADDRESS)
#define  USART2 	   ((USART_RegDef_t*)USART2_BASE_ADDRESS)
#define  USART3 	   ((USART_RegDef_t*)USART3_BASE_ADDRESS)
#define  UART4  	   ((USART_RegDef_t*)UART4_BASE_ADDRESS)
#define  UART5  	   ((USART_RegDef_t*)UART5_BASE_ADDRESS)
#define  USART6 	   ((USART_RegDef_t*)USART6_BASE_ADDRESS)

/******************************* SPI Register Definition Structure *******************************/

/******************************* CRC Register Definition Structure *******************************/

#define CRC_BASE_ADDRESS        0x40023000UL

typedef struct
{
    volatile uint32_t DR;           /**< @brief CRC data register               Address offset 0x00 */
    volatile uint32_t IDR;          /**< @brief CRC independent data register   Address offset 0x04 */
    volatile uint32_t CR;           /**< @brief CRC control register            Address offset 0x08 */
}CRC_RegDef_t;

#define CRC         ((CRC_RegDef_t*)CRC_BASE_ADDRESS)

/******************************* FLASH DRIVER Register Definition Structure *******************************/
#define FLASH_BASE_ADDRESS   	0x40023C00UL

typedef struct
{
    volatile uint32_t ACR;          /**< @brief Flash access control register   Address offset 0x00 */
    volatile uint32_t KEYR;         /**< @brief Flash key register              Address offset 0x04 */
    volatile uint32_t OPTKEYR;      /**< @brief Flash option key register       Address offset 0x08 */
    volatile uint32_t SR;           /**< @brief Flash status register           Address offset 0x0C */
    volatile uint32_t CR;           /**< @brief Flash control register          Address offset 0x10 */
    volatile uint32_t OPTCR;        /**< @brief Flash option control register   Address offset 0x14 */
}FLASH_RegDef_t;

#define FLASH   ((FLASH_RegDef_t*)FLASH_BASE_ADDRESS)

#endif
/********************************************************************************************/
/* END OF FILE: STM32F446xx.h                                                               */
/********************************************************************************************/
