/**
  ******************************************************************************
  * @file    system_MDR32F9Qx.h
  * @author  Phyton Application Team
  * @version V1.0.0
  * @date    11/06/2010
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
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
  * FILE system_MDR32F9Qx.h
  */

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup __MDR32F9QX MDR32F9QX System
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_MDR32F9Qx_H
#define __SYSTEM_MDR32F9Qx_H

/** @addtogroup __MDR32F9QX_System_Exported_Variables MDR32F9QX System Exported Variables
  * @{
  */
	
#define CPU_PLLmul1                     ((uint32_t)0x00000000)
#define CPU_PLLmul2                     ((uint32_t)0x00000001)
#define CPU_PLLmul3                     ((uint32_t)0x00000002)
#define CPU_PLLmul4                     ((uint32_t)0x00000003)
#define CPU_PLLmul5                     ((uint32_t)0x00000004)
#define CPU_PLLmul6                     ((uint32_t)0x00000005)
#define CPU_PLLmul7                     ((uint32_t)0x00000006)
#define CPU_PLLmul8                     ((uint32_t)0x00000007)
#define CPU_PLLmul9                     ((uint32_t)0x00000008)
#define CPU_PLLmul10                    ((uint32_t)0x00000009)
#define CPU_PLLmul11                    ((uint32_t)0x0000000A)
#define CPU_PLLmul12                    ((uint32_t)0x0000000B)
#define CPU_PLLmul13                    ((uint32_t)0x0000000C)
#define CPU_PLLmul14                    ((uint32_t)0x0000000D)
#define CPU_PLLmul15                    ((uint32_t)0x0000000E)
#define CPU_PLLmul16                    ((uint32_t)0x0000000F)	

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock)
                                           *   default value */

/** @} */ /* End of group __MDR32F9QX_System_Exported_Variables */

/** @addtogroup __MDR32F9QX_System_Exported_Functions MDR32F9QX System Exported Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/** @} */ /* End of group __MDR32F9QX_System_Exported_Functions */

#endif /*__SYSTEM_MDR32F9Qx_H */

/** @} */ /* End of group __MDR32F9QX */

/** @} */ /* End of group __CMSIS */

/******************* (C) COPYRIGHT 2010 Phyton *********************************
*
* END OF FILE system_MDR32F9Qx.h */
