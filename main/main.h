#ifndef __MAIN_H
#define __MAIN_H

#include "MDR32Fx.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_config.h"
#include "systick.h"
#include "canhacker.h"
#include "leds.h"

#define QUE_USB_NUMBER	(1000)
#define QUE_CAN1_NUMBER	(1000)
#define QUE_CAN2_NUMBER	(1000)

#define KR_KEY_Reload       				((uint32_t)0xAAAA)
#define KR_KEY_Enable       				((uint32_t)0xCCCC)
#define KR_KEY_WriteEnable  				((uint32_t)0x5555)
#define KR_KEY_WriteDisable 				((uint32_t)0x0000)

#define IWDG_Prescaler_4            ((uint32_t)0x00)
#define IWDG_Prescaler_8            ((uint32_t)0x01)
#define IWDG_Prescaler_16           ((uint32_t)0x02)
#define IWDG_Prescaler_32           ((uint32_t)0x03)
#define IWDG_Prescaler_64           ((uint32_t)0x04)
#define IWDG_Prescaler_128          ((uint32_t)0x05)
#define IWDG_Prescaler_256          ((uint32_t)0x06)

#define IWDG_SR_PVU                 ((uint32_t)0x00000001)
#define IWDG_SR_RVU                 ((uint32_t)0x00000002)

#endif
