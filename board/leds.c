#include "leds.h"

static uint8_t sDivled=0;

void InitLeds(uint16_t divled)
{
	PORT_InitTypeDef PORT_InitStructure;	
	PORT_StructInit(&PORT_InitStructure);
		
	PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1);
  PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
  PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST;
	PORT_Init(MDR_PORTA, &PORT_InitStructure);	
	
	sDivled = divled;
}

void LedSwitch(MDR_PORT_TypeDef* PORTx, uint8_t pin)
{
	static uint8_t cnt[nCANs]={0};
	uint8_t tmp[nCANs];
	
	uint8_t ch= (1<<pin);
	tmp[ch] = ++cnt[ch] ^ sDivled;
	if(tmp[ch]==0){PORTx->RXTX ^= (1<<pin); cnt[ch]=0;}
}

void LedOff(uint8_t ch)
{
	MDR_PORTA->RXTX &= ~(1<<ch);
}
