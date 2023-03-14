#include "canhacker.h"
#include "stdint.h"
#include <stdio.h>
#include "ringqueue.h"
#include <string.h>

static uint8_t bytes =0;
static uint8_t tmp[100];
//static uint8_t interface=0;
static CANHacker_typedef CANHacker;

void TransmitStdCANFrame(void);
void TransmitExtCANFrame(void);
void SelectCh(uint8_t ch);
void UnselectChanel(uint8_t ch);
uint8_t GetVaSN(uint8_t p, char *vsn);

void Lawicel(void)
{
	uint8_t loctmp=0;
		if(QueUSB.avail==0)return;
			RingQueGet(&QueUSB,&loctmp,1);
			switch(loctmp)
			{
				case 'V':
					RingQueGet(&QueUSB,&loctmp,1);
					bytes=GetVaSN(loctmp,(char *)&tmp);
				break;		
				case 'O':
					RingQueGet(&QueUSB,&tmp[0],1);
					SelectCh(tmp[0]);
					bytes = sprintf((char *)&tmp,"\r");
				break;
				case 'C':
					RingQueGet(&QueUSB,&tmp[0],1);
					UnselectChanel(tmp[0]);
					bytes = sprintf((char *)&tmp,"\r");
				break;
				case 't':
					TransmitStdCANFrame();
					bytes = sprintf((char *)&tmp,"\r");
				break;
				case 'T':
					TransmitExtCANFrame();
					bytes = sprintf((char *)&tmp,"\r");
				break;
				case 'S':
					RingQueGet(&QueUSB,&tmp[0],1);
					bytes = sprintf((char *)&tmp,"\r");
				break;
				case 'Z':
					bytes = sprintf((char *)&tmp,"\r");
				break;
				default:
					bytes = sprintf((char *)&tmp,"\r");
					bytes=0;
				break;				
			}
			USB_CDC_SendData(tmp,bytes);
		
}

void SendToCANHacker(uint8_t ch)
{
	if(ch>CAN2)return;
	CAN_RxMsgTypeDef lRx2Message;
	uint8_t buf[40];
	uint8_t num=0;
	RingQueue_typedef *ptr;
	
	if(ch==CAN1)ptr = &QueCAN1;else ptr = &QueCAN2;
	
	if(uiRingQueEmpty(ptr))return;
	
	RingQueGet(ptr,buf,1);
	if(buf[0]!=0xaa)return;
	
	RingQueGet(ptr,buf,sizeof(lRx2Message.Rx_Header));
	memcpy(&lRx2Message.Rx_Header,buf,sizeof(lRx2Message.Rx_Header));							//преобразуем данные из ринг буфера в header пакета can
	RingQueGet(ptr,(uint8_t *)&lRx2Message.Data,lRx2Message.Rx_Header.DLC);
	
	uint32_t time=uiGetTimestamp();
	
	if(lRx2Message.Rx_Header.IDE)
	{
		buf[num++] = 'T';
		buf[num++] = uiNibble2ascii(ch);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>28);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>24);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>20);		
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>16);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>12);		
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>8);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>4);		
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>0);
	}
	else
	{
		buf[num++] = 't';
		buf[num++] = uiNibble2ascii(ch);
		buf[num++] = uiNibble2ascii((lRx2Message.Rx_Header.ID)>>26);
		buf[num++] = uiNibble2ascii((lRx2Message.Rx_Header.ID)>>22);
		buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.ID>>18);
	}
	buf[num++] = uiNibble2ascii(lRx2Message.Rx_Header.DLC);
	
	num=uiPackDataCANToCANHacker(num,lRx2Message.Rx_Header.DLC,lRx2Message.Data,buf);
	
	buf[num++] = uiNibble2ascii((time)>>12);
	buf[num++] = uiNibble2ascii((time)>>8);
	buf[num++] = uiNibble2ascii((time)>>4);
	buf[num++] = uiNibble2ascii(time);
	buf[num++] = '\r';	
	USB_CDC_SendData(buf,num);
}

void TransmitStdCANFrame(void)
{
	uint8_t data[30];
	CANReceive_typedef *ptr;
	
	RingQueGet(&QueUSB,data,5);
	uint8_t ch = uiAscii2byte(data[0]);
	if(ch>CAN2)return;
	if(ch==CAN1) ptr = &CAN1Receive;else ptr = &CAN2Receive;	
	CAN_TxMsgTypeDef *ptrtx = &ptr->TxMessage;
	uint16_t len = uiAscii2byte(data[4])*2;
	RingQueGet(&QueUSB,data+5,len);
	
	ptrtx->ID = uiAscii2byte(data[1])<<26 | uiAscii2byte(data[2])<<22 | uiAscii2byte(data[3])<<18;
	ptrtx->IDE =0;
	ptrtx->DLC = uiAscii2byte(data[4]);
	ptrtx->Data[0]=0;ptrtx->Data[1]=0;										//clear old data
	PackDataCANHackerToCAN(5,ptrtx->DLC,data,ptrtx->Data);
	
	if(CANHacker.numch & (1<<(ch-1)))
		ptr->HaveSendData=2;
	
}

void TransmitExtCANFrame(void)
{
	uint8_t data[30];
	CANReceive_typedef *ptr;
	
	RingQueGet(&QueUSB,data,10);
	uint8_t ch = uiAscii2byte(data[0]);
	if(ch>CAN2)return;
	if(ch==CAN1) ptr = &CAN1Receive;else ptr = &CAN2Receive;
	CAN_TxMsgTypeDef *ptrtx = &ptr->TxMessage;
	uint16_t len = uiAscii2byte(data[9])*2;
	RingQueGet(&QueUSB,data+10,len);	
	
	ptrtx->ID = uiAscii2byte(data[1])<<28 | uiAscii2byte(data[2])<<24 | uiAscii2byte(data[3])<<20
							| uiAscii2byte(data[4])<<16 | uiAscii2byte(data[5])<<12 | uiAscii2byte(data[6])<<8
							| uiAscii2byte(data[7])<<4 | uiAscii2byte(data[8]);
	ptrtx->IDE =1;
	ptrtx->DLC = uiAscii2byte(data[9]);
	ptrtx->Data[0]=0;ptrtx->Data[1]=0;										//clear old data
	PackDataCANHackerToCAN(10,ptrtx->DLC,data,ptrtx->Data);
	
	if(CANHacker.numch & (1<<(ch-1)))
		ptr->HaveSendData=2;
	
}

uint8_t GetVaSN(uint8_t p, char *vsn)
{
	if(p=='S') return sprintf(vsn,"0123456789ABCDEF");
	if (p=='N') return sprintf(vsn,"CANUSB\r");
	return sprintf(vsn,"VF_1.5\r");
}

void SelectCh(uint8_t ch)
{
	CANHacker_typedef *ptr = &CANHacker;
	ch = uiAscii2byte(ch);
	if (ch>CAN2)return;
	
	SetSkipInterrupt(ch);
	
	ch -=1;
	ptr->numch |=(1<<ch);
	ptr->mode = 0;
	
	NVIC_EnableIRQ((IRQn_Type)ch);
}

void UnselectChanel(uint8_t ch)
{
	CANHacker_typedef *ptr = &CANHacker;
	ch = uiAscii2byte(ch);
	if (ch>CAN2)return;
	ch -=1;
	ptr->numch &= ~(1<<ch);	
	
	NVIC_DisableIRQ((IRQn_Type)ch);
	
	RingQueue_typedef *ptrque = &QueCAN1;
	if(ch) ptrque= &QueCAN2;
	
	RingQueClear(ptrque);
	
	LedOff(ch);
}


