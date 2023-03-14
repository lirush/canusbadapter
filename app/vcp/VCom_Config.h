//VCom_Config.h

#ifndef __VCOM_CONFIG_h__
#define __VCOM_CONFIG_h__

#include "MDR32Fx.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include <MDR32F9Qx_eeprom.h>

//static void Setup_CPU_Clock(void);
//static void Setup_USB(void);
//static void VCom_Configuration(void);

#define USB_DEBUG_NUM_PACKETS   100
#define BUFFER_LENGTH       		100 

extern uint8_t Buffer[BUFFER_LENGTH];

 void Setup_CPU_Clock(void);
 void Setup_USB(void);
 void VCom_Configuration(void);



#endif // __VCOM_CONFIG_h__

