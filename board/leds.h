#ifndef _LEDS_H
#define _LEDS_H

#include "MDR32F9Qx_port.h"

#define nCANs						(2)

enum LEDs{CANACT1,CANACT2};

void InitLeds(uint16_t divled);
void LedSwitch(MDR_PORT_TypeDef* PORTx, uint8_t pin);
void LedOff(uint8_t ch);

#endif
