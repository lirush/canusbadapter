/**
  ******************************************************************************
  * @file    MDR32F9Qx_ebc.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    16/02/2011
  * @brief   This file contains all the functions prototypes for the EBC
  *          firmware library.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, PHYTON SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 Phyton</center></h2>
  ******************************************************************************
  * FILE MDR32F9Qx_ebc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32F9X_EBC_H
#define __MDR32F9X_EBC_H

/* Includes ------------------------------------------------------------------*/
#include "MDR32Fx.h"
#include "MDR32F9Qx_lib.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Driver MDR32F9Qx Standard Peripherial Driver
  * @{
  */

/** @addtogroup EBC
  * @{
  */

/** @defgroup EBC_Exported_Types EBC Exported Types
  * @{
  */

/**
  * @brief  EBC Init structure definition
  */

typedef struct
{
  uint32_t EBC_Mode;        /*!< Specifies external bus mode.
                               This parameter can be a value of @ref EBC_MODE. */
  uint32_t EBC_Cpol;        /*!< Specifies CLOCK signal polarity.
                               This parameter can be a value of @ref EBC_CPOL. */
  uint8_t  EBC_WaitState;   /*!< Specifies wait states number.
                               This parameter can be a value of @ref EBC_WAIT_STATE. */
  uint8_t  EBC_NandTrc;     /*!< Specifies NAND read cycle time t_rc.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTwc;     /*!< Specifies NAND write cycle time t_wc.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTrea;    /*!< Specifies NAND read access time t_rea.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTwp;     /*!< Specifies NAND write access time t_wp.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTwhr;    /*!< Specifies NAND status register access time t_whr.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTalea;   /*!< Specifies NAND ID registers access time t_alea.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
  uint8_t  EBC_NandTrr;     /*!< Specifies NAND delay from Busy release to read operation.
                               This parameter can be a value of @ref EBC_NAND_CYCLES. */
}EBC_InitTypeDef;

/** @} */ /* End of group EBC_Exported_Types */

/** @defgroup EBC_Exported_Constants EBC Exported Constants
  * @{
  */

/** @defgroup EBC_MODE EBC mode
  * @{
  */

#define EBC_MODE_OFF                ((uint32_t)0x0)                 /*!< EBC disabled */
#define EBC_MODE_ROM                (((uint32_t)0x1) << 0)          /*!< EBC works with external ROM */
#define EBC_MODE_RAM                (((uint32_t)0x1) << 1)          /*!< EBC works with external RAM */
#define EBC_MODE_NAND               (((uint32_t)0x1) << 2)          /*!< EBC works with external NAND Flash memory */

#define EBC_MODE_MSK                (EBC_MODE_ROM | EBC_MODE_RAM | EBC_MODE_NAND)

#define IS_EBC_MODE(MODE) (((MODE) == EBC_MODE_OFF ) || \
                               ((MODE) == EBC_MODE_ROM ) || \
                               ((MODE) == EBC_MODE_RAM ) || \
                               ((MODE) == EBC_MODE_NAND))

/** @} */ /* End of group EBC_MODE */

/** @defgroup EBC_CPOL EBC CLOCK polarity
  * @{
  */

#define EBC_CPOL_POSITIVE           (((uint32_t)0x0) << 3)          /*!< EBC generates the positive CLOCK signal */
#define EBC_CPOL_NEGATIVE           (((uint32_t)0x1) << 3)          /*!< EBC generates the negative CLOCK signal */

#define IS_EBC_CPOL(CPOL) (((CPOL) == EBC_CPOL_POSITIVE) || \
                               ((CPOL) == EBC_CPOL_NEGATIVE))

/** @} */ /* End of group EBC_CPOL */

/** @defgroup EBC_WAIT_STATE EBC Wait States number
  * @{
  */

#define EBC_WAIT_STATE_3HCLK        ((uint32_t)0x0)                 /*!< Wait State = 3 HCLK clocks */
#define EBC_WAIT_STATE_4HCLK        ((uint32_t)0x1)                 /*!< Wait State = 4 HCLK clocks */
#define EBC_WAIT_STATE_5HCLK        ((uint32_t)0x2)                 /*!< Wait State = 5 HCLK clocks */
#define EBC_WAIT_STATE_6HCLK        ((uint32_t)0x3)                 /*!< Wait State = 6 HCLK clocks */
#define EBC_WAIT_STATE_7HCLK        ((uint32_t)0x4)                 /*!< Wait State = 7 HCLK clocks */
#define EBC_WAIT_STATE_8HCLK        ((uint32_t)0x5)                 /*!< Wait State = 8 HCLK clocks */
#define EBC_WAIT_STATE_9HCLK        ((uint32_t)0x6)                 /*!< Wait State = 9 HCLK clocks */
#define EBC_WAIT_STATE_10HCLK       ((uint32_t)0x7)                 /*!< Wait State = 10 HCLK clocks */
#define EBC_WAIT_STATE_11HCLK       ((uint32_t)0x8)                 /*!< Wait State = 11 HCLK clocks */
#define EBC_WAIT_STATE_12HCLK       ((uint32_t)0x9)                 /*!< Wait State = 12 HCLK clocks */
#define EBC_WAIT_STATE_13HCLK       ((uint32_t)0xA)                 /*!< Wait State = 13 HCLK clocks */
#define EBC_WAIT_STATE_14HCLK       ((uint32_t)0xB)                 /*!< Wait State = 14 HCLK clocks */
#define EBC_WAIT_STATE_15HCLK       ((uint32_t)0xC)                 /*!< Wait State = 15 HCLK clocks */
#define EBC_WAIT_STATE_16HCLK       ((uint32_t)0xD)                 /*!< Wait State = 16 HCLK clocks */
#define EBC_WAIT_STATE_17HCLK       ((uint32_t)0xE)                 /*!< Wait State = 17 HCLK clocks */
#define EBC_WAIT_STATE_18HCLK       ((uint32_t)0xF)                 /*!< Wait State = 18 HCLK clocks */

#define EBC_WAIT_STATE_MSK          ((uint32_t)0xF)                 /*!< Wait State value mask */

#define IS_EBC_WAIT_STATE(WAIT_STATE) (((WAIT_STATE) & ~EBC_WAIT_STATE_MSK) == 0 )

/** @} */ /* End of group EBC_WAIT_STATE */

/** @defgroup EBC_NAND_CYCLES EBC NAND Cycles
  * @{
  */

#define EBC_NAND_CYCLES_0HCLK       ((uint32_t)0x0)                 /*!< NAND Cycles = 0 HCLK clocks */
#define EBC_NAND_CYCLES_1HCLK       ((uint32_t)0x1)                 /*!< NAND Cycles = 1 HCLK clocks */
#define EBC_NAND_CYCLES_2HCLK       ((uint32_t)0x2)                 /*!< NAND Cycles = 2 HCLK clocks */
#define EBC_NAND_CYCLES_3HCLK       ((uint32_t)0x3)                 /*!< NAND Cycles = 3 HCLK clocks */
#define EBC_NAND_CYCLES_4HCLK       ((uint32_t)0x4)                 /*!< NAND Cycles = 4 HCLK clocks */
#define EBC_NAND_CYCLES_5HCLK       ((uint32_t)0x5)                 /*!< NAND Cycles = 5 HCLK clocks */
#define EBC_NAND_CYCLES_6HCLK       ((uint32_t)0x6)                 /*!< NAND Cycles = 6 HCLK clocks */
#define EBC_NAND_CYCLES_7HCLK       ((uint32_t)0x7)                 /*!< NAND Cycles = 7 HCLK clocks */
#define EBC_NAND_CYCLES_8HCLK       ((uint32_t)0x8)                 /*!< NAND Cycles = 8 HCLK clocks */
#define EBC_NAND_CYCLES_9HCLK       ((uint32_t)0x9)                 /*!< NAND Cycles = 9 HCLK clocks */
#define EBC_NAND_CYCLES_10HCLK      ((uint32_t)0xA)                 /*!< NAND Cycles = 10 HCLK clocks */
#define EBC_NAND_CYCLES_11HCLK      ((uint32_t)0xB)                 /*!< NAND Cycles = 11 HCLK clocks */
#define EBC_NAND_CYCLES_12HCLK      ((uint32_t)0xC)                 /*!< NAND Cycles = 12 HCLK clocks */
#define EBC_NAND_CYCLES_13HCLK      ((uint32_t)0xD)                 /*!< NAND Cycles = 13 HCLK clocks */
#define EBC_NAND_CYCLES_14HCLK      ((uint32_t)0xE)                 /*!< NAND Cycles = 14 HCLK clocks */
#define EBC_NAND_CYCLES_15HCLK      ((uint32_t)0xF)                 /*!< NAND Cycles = 15 HCLK clocks */

#define EBC_NAND_CYCLES_MSK         ((uint32_t)0xF)                 /*!< NAND Cycles value mask */

#define IS_EBC_NAND_CYCLES(NAND_CYCLES) (((NAND_CYCLES) & ~EBC_NAND_CYCLES_MSK) == 0 )

/** @} */ /* End of group EBC_NAND_CYCLES */

/** @} */ /* End of group EBC_Exported_Constants */

/** @defgroup EBC_Exported_Macros EBC Exported Macros
  * @{
  */

/** @} */ /* End of group EBC_Exported_Macros */

/** @defgroup EBC_Exported_Functions EBC Exported Functions
  * @{
  */

void EBC_DeInit(void);
void EBC_Init(const EBC_InitTypeDef* EBC_InitStruct);
void EBC_StructInit(EBC_InitTypeDef* EBC_InitStruct);
uint32_t EBC_CalcWaitStates(uint32_t HCLK_Frequency_KHz, uint32_t Time_ns);
uint32_t EBC_CalcNandCycles(uint32_t HCLK_Frequency_KHz, uint32_t Time_ns);
FlagStatus EBC_GetBusyStatus(void);

/** @} */ /* End of group EBC_Exported_Functions */

/** @} */ /* End of group EBC */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Driver */

#endif /* __MDR32F9X_EBC_H */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE MDR32F9Qx_ebc.h */

