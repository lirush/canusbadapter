/**
  ******************************************************************************
  * @file    MDR32F9Qx_ebc.c
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    22/02/2011
  * @brief   This file provides all the EBC firmware functions.
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
  * FILE MDR32F9Qx_ebc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_ebc.h"
#include "MDR32F9Qx_config.h"

#define ASSERT_INFO_FILE_ID FILEID__MDR32F9X_EBC_C

/** @addtogroup __MDR32F9Qx_StdPeriph_Driver MDR32F9Qx Standard Peripherial Driver
  * @{
  */

/** @defgroup EBC EBC
  * @{
  */

/** @defgroup EBC_Private_Defines EBC Private Defines
  * @{
  */

#define WAIT_STATES_COEF        1000000
#define WAIT_STATES_MIN         3
#define WAIT_STATES_MAX         18

#define NAND_SYCLES_COEF        1000000
#define NAND_SYCLES_MAX         15

/** @} */ /* End of group EBC_Private_Defines */

/** @defgroup EBC_Private_Functions EBC Private Functions
  * @{
  */

/**
  * @brief  Resets the EBC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EBC_DeInit(void)
{
  MDR_EBC_TypeDef *EBCx;

  EBCx = MDR_EBC;

  EBCx->CONTROL = 0;
  EBCx->NAND_CYCLES = 0;
}

/**
  * @brief  Initializes the EBC peripheral according to the specified
  *         parameters in the EBC_InitStruct.
  * @param  EBC_InitStruct: pointer to a EBC_InitTypeDef structure that
  *         contains the configuration information for the specified EBC peripheral.
  * @retval None
  */
void EBC_Init(const EBC_InitTypeDef* EBC_InitStruct)
{
  MDR_EBC_TypeDef *EBCx;
  uint32_t tmpreg_CONTROL;
  uint32_t tmpreg_CYCLES;

  /* Check the parameters */
  assert_param(IS_EBC_MODE(EBC_InitStruct->EBC_Mode));
  assert_param(IS_EBC_CPOL(EBC_InitStruct->EBC_Cpol));
  assert_param(IS_EBC_WAIT_STATE(EBC_InitStruct->EBC_WaitState));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTrc));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTwc));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTrea));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTwp));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTwhr));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTalea));
  assert_param(IS_EBC_NAND_CYCLES(EBC_InitStruct->EBC_NandTrr));

  /* Form new value for the EBC_CONTROL register */
  tmpreg_CONTROL = (EBC_InitStruct->EBC_Mode)
                 | (EBC_InitStruct->EBC_Cpol)
                 | (EBC_InitStruct->EBC_WaitState << EBC_CONTROL_WAIT_STATE_Pos);

  /* Form new value for the EBC_NAND_CYCLES register */
  tmpreg_CYCLES  = (EBC_InitStruct->EBC_NandTrc       << EBC_NAND_CYCLES_TRC_Pos)
                 | (EBC_InitStruct->EBC_NandTwc       << EBC_NAND_CYCLES_TWC_Pos)
                 | (EBC_InitStruct->EBC_NandTrea      << EBC_NAND_CYCLES_TREA_Pos)
                 | (EBC_InitStruct->EBC_NandTwp       << EBC_NAND_CYCLES_TWP_Pos)
                 | (EBC_InitStruct->EBC_NandTwhr      << EBC_NAND_CYCLES_TWHR_Pos)
                 | (EBC_InitStruct->EBC_NandTalea << EBC_NAND_CYCLES_TALEA_Pos)
                 | (EBC_InitStruct->EBC_NandTrr       << EBC_NAND_CYCLES_TRR_Pos);

  EBCx = MDR_EBC;

  /* Configure EBC registers with new values */
  EBCx->NAND_CYCLES = tmpreg_CYCLES;
  EBCx->CONTROL = tmpreg_CONTROL;
}

/**
  * @brief  Fills each EBC_InitStruct member with its default value.
  * @param  EBC_InitStruct: pointer to a EBC_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void EBC_StructInit(EBC_InitTypeDef* EBC_InitStruct)
{
  /* Reset EBC initialization structure parameters values */
  EBC_InitStruct->EBC_Mode          = EBC_MODE_OFF;
  EBC_InitStruct->EBC_Cpol          = EBC_CPOL_POSITIVE;
  EBC_InitStruct->EBC_WaitState = EBC_WAIT_STATE_3HCLK;
  EBC_InitStruct->EBC_NandTrc       = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTwc       = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTrea      = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTwp       = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTwhr      = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTalea = EBC_NAND_CYCLES_0HCLK;
  EBC_InitStruct->EBC_NandTrr       = EBC_NAND_CYCLES_0HCLK;
}

/**
  * @brief  Calculates the Wait States number for selected HCLK frequency and
  *         time interval.
  * @param  HCLK_Frequency_KHz: specifies the HCLK frequency.
  * @param  Time_ns: specifies the time interval.
  * @retval The Wait States number in range 0..15 or 0xFFFFFFFF if result is
  *         out of range 0..15.
  */
uint32_t EBC_CalcWaitStates(uint32_t HCLK_Frequency_KHz, uint32_t Time_ns)
{
  uint32_t Cycles;

  if ( HCLK_Frequency_KHz == 0 )
  {
    Cycles = 0;
  }
  else if ( Time_ns > WAIT_STATES_MAX * WAIT_STATES_COEF / HCLK_Frequency_KHz )
  {
    Cycles = 0xFFFFFFFF;
  }
  else
  {
    Cycles = (HCLK_Frequency_KHz * Time_ns + WAIT_STATES_COEF - 1) / WAIT_STATES_COEF;
    if ( Cycles > WAIT_STATES_MAX)
    {
      Cycles = 0xFFFFFFFF;
    }
    else if ( Cycles >= WAIT_STATES_MIN)
    {
      Cycles -= WAIT_STATES_MIN;
    }
    else
    {
      Cycles = 0;
    }
  }

  return Cycles;
}

/**
  * @brief  Calculates the NAND Sycles number for selected HCLK frequency and
  *         time interval.
  * @param  HCLK_Frequency_KHz: specifies the HCLK frequency.
  * @param  Time_ns: specifies the time interval.
  * @retval The NAND Sycles number in range 0..15 or 0xFFFFFFFF if result is
  *         out of range 0..15.
  */
uint32_t EBC_CalcNandCycles(uint32_t HCLK_Frequency_KHz, uint32_t Time_ns)
{
  uint32_t Cycles;

  if ( HCLK_Frequency_KHz == 0 )
  {
    Cycles = 0;
  }
  else if ( Time_ns > NAND_SYCLES_MAX * NAND_SYCLES_COEF / HCLK_Frequency_KHz )
  {
    Cycles = 0xFFFFFFFF;
  }
  else
  {
    Cycles = (HCLK_Frequency_KHz * Time_ns + NAND_SYCLES_COEF - 1) / NAND_SYCLES_COEF;
    if ( Cycles > NAND_SYCLES_MAX)
    {
      Cycles = 0xFFFFFFFF;
    }
  }

  return Cycles;
}

/**
  * @brief  Returns the BUSY status of the NAND Flash.
  * @param  None.
  * @retval The NAND Flash BUSY status (NandFlashReady or NandFlashBusy).
  */
FlagStatus EBC_GetBusyStatus(void)
{
  MDR_EBC_TypeDef *EBCx;
  FlagStatus tmpreg_BUSY_STS;

  EBCx = MDR_EBC;

  if ((EBCx->CONTROL & EBC_CONTROL_BUSY) == 0)
  {
    tmpreg_BUSY_STS = RESET;
  }
  else
  {
    tmpreg_BUSY_STS = SET;
  }

  return tmpreg_BUSY_STS;
}

/** @} */ /* End of group EBC_Private_Functions */

/** @} */ /* End of group EBC */

/** @} */ /* End of group __MDR32F9Qx_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE MDR32F9Qx_ebc.c */

