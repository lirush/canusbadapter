/*
*** Разработано коллективом АО НПП АМЭ 02.2022 г.
***
*** передача данным USB<->CAN
*** 
*** в основе аналог адаптера CANHacker V3
***
*** разработано для плат на базе 1986ВЕ92У
*** кварц =8МГц PLL =10 USBCLK =48МГц
***
*/

#include "main.h"
#include "ringqueue.h"
#include "task.h"

RingQueue_typedef QueUSB;
RingQueue_typedef QueCAN1;
RingQueue_typedef QueCAN2;
uint8_t RingBufferUSB[QUE_USB_NUMBER];
uint8_t RingBufferCAN1[QUE_CAN1_NUMBER];
uint8_t RingBufferCAN2[QUE_CAN2_NUMBER];
uint8_t usb_dont_sleep=1;

void Task1(void)
{
		Lawicel();
}

void Task2(void)
{
		if(CAN2Receive.HaveSendData==2)
		{
			CAN_Transmit(MDR_CAN2, 0, &CAN2Receive.TxMessage);
			CAN2Receive.HaveSendData=0;
			LedSwitch(MDR_PORTA,CANACT2);
		}	
}

void Task3(void)
{
		if(CAN1Receive.HaveSendData==2)
		{
			CAN_Transmit(MDR_CAN1, 0, &CAN1Receive.TxMessage);
			CAN1Receive.HaveSendData=0;
			LedSwitch(MDR_PORTA,CANACT1);
		}	
}

void Task4(void)
{
		SendToCANHacker(CAN1);
}

void Task5(void)
{
		SendToCANHacker(CAN2);	
}

void IWDG_ReloadCounter(void)
{
  MDR_IWDG->KR = KR_KEY_Reload;
}

void InitWdt(void)
{
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG,ENABLE);	
	
	MDR_IWDG->KR = KR_KEY_Enable;

	MDR_IWDG->KR = KR_KEY_WriteEnable;

	MDR_IWDG->PR = IWDG_Prescaler_128;

	while(MDR_IWDG->SR & IWDG_SR_PVU){;}

	MDR_IWDG->RLR = 0xc35;																			//С…РѕС‚РµР»РѕСЃСЊ 10СЃРµРє., РїРѕ С„Р°РєС‚Сѓ РїРѕР»СѓС‡РёР»РѕСЃСЊ ~14СЃРµРє
		
	MDR_IWDG->KR = KR_KEY_Reload;
	
}

uint8_t timeslotes=0;
uint8_t f=1; uint8_t set_ticks=0; 
volatile uint32_t cnt=0;
uint32_t sa=0;
int main(void)
{	
	
  VCom_Configuration();

  USB_CDC_Init(Buffer, 1, SET);
	
	Setup_USB();
	
	CANInit();
	
	SysTick_Config(80000);
	
	InitLeds(5);
	
	RingQueInit(&QueUSB,RingBufferUSB,QUE_USB_NUMBER);
	RingQueInit(&QueCAN1,RingBufferCAN1,QUE_CAN1_NUMBER);
	RingQueInit(&QueCAN2,RingBufferCAN2,QUE_CAN2_NUMBER);
	
	xCreateTask(Task1);
	xCreateTask(Task2);
	xCreateTask(Task3);
	xCreateTask(Task4);
	xCreateTask(Task5);
	
	InitWdt();
	
	while(1)
	{	
		USB_DeviceDispatchEvent();
		
		vTaskScheduler();
		
		USB_DeviceCheckSleep();
		
		if(usb_dont_sleep)
		IWDG_ReloadCounter();		
	
	}
	
}

