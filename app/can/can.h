#ifndef CAN_H
#define CAN_H

#include "MDR32F9Qx_config.h"
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_can.h>

enum CHCANs{CAN1=1,CAN2=2};

typedef struct{
	uint8_t HaveNewData;
	uint8_t HaveSendData;
	CAN_TxMsgTypeDef TxMessage;
	CAN_RxMsgTypeDef Rx2Message;
}CANReceive_typedef;

extern CANReceive_typedef CAN1Receive;
extern CANReceive_typedef CAN2Receive;

extern CAN_TxMsgTypeDef TxMessage;
extern CAN_RxMsgTypeDef RxMessage;

void CANInit(void);
void CANSendMsg(uint32_t id);

void SetSkipInterrupt(uint8_t ch);
void ClearSkipInterrupt(uint8_t ch);

#endif
