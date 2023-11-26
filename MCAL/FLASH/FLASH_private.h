#ifndef  FLASH_PRIVATE_H
#define  FLASH_PRIVATE_H

static void voidMassErase(uint8_t Copy_u8VoltageRange, uint32_t Copy_u32Banks);

#define MAX_NUM_SECTOR  8

#define FLASH_TYPEERASE_SECTORS         0x00000000U  /*!< Sectors erase only          */
#define FLASH_TYPEERASE_MASSERASE       0x00000001U  /*!< Flash Mass erase activation */


#define FLASH_ACR_LATENCY   0  /**< @brief Latency offset */
#define FLASH_ACR_PRFTEN    8  /**< @brief Prefetch enable offset */
#define FLASH_ACR_ICEN      9  /**< @brief Instruction cache enable offset */
#define FLASH_ACR_DCEN      10 /**< @brief Data cache enable offset */
#define FLASH_ACR_ICRST     11 /**< @brief Instruction cache reset offset */
#define FLASH_ACR_DCRST     12 /**< @brief Data cache reset offset */
/** @} */

/**
 * @name Bit position definition FLASH_KEYR.
 * @{
 */
#define FLASH_KEYR          0   /**< @brief FPEC key offset */
/** @} */

/**
 * @name Bit position definition FLASH_OPTKEYR.
 * @{
 */
#define FLASH_OPTKEYR       0   /**< @brief Option byte key offset */
/** @} */

#define FLASH_CR_PG_Msk                (0x1UL)               /*!< 0x00000001 */

#define FLASH_CR_MER_Msk               (0x1UL)               /*!< 0x00000004 */

#define FLASH_CR_PSIZE_Msk             (0x3UL)               /*!< 0x00000300 */

#define FLASH_CR_SNB_Msk               (0x1FU)               /*!< 0x000000F8 */

#define FLASH_CR_SER_Msk               (0x1UL)               /*!< 0x00000002 */

#define FLASH_CR_STRT_Msk              (0x1UL)               /*!< 0x00010000 */

#define FLASH_OPTCR_NWRP_Msk           (0x1UL)               /*!< 0x00010000 */

#define FLASH_OPTCR_NWRP_MASK          (0b11111111)



/**
 * @name Bit position definition FLASH status register.
 * @{
 */
#define FLASH_SR_EOP        0  /**< @brief End of operation offset */
#define FLASH_SR_OPERR      1  /**< @brief Operation error offset */
#define FLASH_SR_WRPERR     4  /**< @brief Write protection error offset */
#define FLASH_SR_PGAERR     5  /**< @brief Programming alignment error offset */
#define FLASH_SR_PGPERR     6  /**< @brief Programming parallelism error offset */
#define FLASH_SR_PGSERR     7  /**< @brief Programming sequence error offset */
#define FLASH_SR_RDERR      8  /**< @brief Read Protection Error (pcrop) offset */
#define FLASH_SR_BSY        16 /**< @brief Busy offset */
/** @} */

/**
 * @name Bit position definition FLASH control register.
 * @{
 */
#define FLASH_CR_PG         0  /**< @brief Programming offset */
#define FLASH_CR_SER        1  /**< @brief Sector erase offset */
#define FLASH_CR_MER        2  /**< @brief Mass erase offset */
#define FLASH_CR_SNB        3  /**< @brief Sector number offset */
#define FLASH_CR_PSIZE      8  /**< @brief Program size offset */
#define FLASH_CR_STRT       16 /**< @brief Start offset */
#define FLASH_CR_EOPIE      24 /**< @brief End of operation interrupt enable offset */
#define FLASH_CR_ERRIE      25 /**< @brief Error interrupt enable offset */
#define FLASH_CR_LOCK       31 /**< @brief Lock offset */
/** @} */

/**
 * @name Bit position definition FLASH option control register.
 * @{
 */
#define FLASH_OPTCR_OPTLOCK     0  /**< @brief Option lock offset */
#define FLASH_OPTCR_OPTSTRT     1  /**< @brief Option start offset */
#define FLASH_OPTCR_BOR_LEV     2  /**< @brief BOR reset level offset */
#define FLASH_OPTCR_WDG_SW      5  /**< @brief User option byte (WDG_SW) offset */
#define FLASH_OPTCR_NRST_STOP   6  /**< @brief User option byte (nRST_STOP) offset */
#define FLASH_OPTCR_NRST_STDBY  7  /**< @brief User option byte (nRST_STDBY) offset */
#define FLASH_OPTCR_RDP         8  /**< @brief Read protect offset */
#define FLASH_OPTCR_NWRP        16 /**< @brief Not write protect offset */
#define FLASH_OPTCR_SPRMOD      31 /**< @brief Selection of Protection Mode of nWRPi bits offset */
/** @} */





#endif
