#include "can.h"
#include "MDR32F9Qx_port.h"
#include "ringqueue.h"
#include <string.h>
#include "leds.h"

CAN_TxMsgTypeDef TxMessage;
CAN_RxMsgTypeDef RxMessage;
CANReceive_typedef CAN1Receive;
CANReceive_typedef CAN2Receive;

static uint8_t skip_interrup=0;

/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
	CANReceive_typedef *ptr = &CAN1Receive;
	uint8_t data[20];	
	
	if(skip_interrup & (1<<CAN1))
	{
		CAN_ITClearRxTxPendingBit(MDR_CAN1, 1, CAN_STATUS_RX_READY);
		ClearSkipInterrupt(CAN1); 
		return;
	}

	if(!uiRingQueIsFull(&QueCAN1))
	{
		CAN_GetRawReceivedData(MDR_CAN1, 1, &ptr->Rx2Message);
		
		data[0]=0xaa;
		memcpy(data+1,&ptr->Rx2Message,sizeof(ptr->Rx2Message));
		uint16_t len = ptr->Rx2Message.Rx_Header.DLC + sizeof(ptr->Rx2Message.Rx_Header)+1;
		RingQuePut(&QueCAN1,data,len);	
		LedSwitch(MDR_PORTA,CANACT1);
	}
	
  CAN_ITClearRxTxPendingBit(MDR_CAN1, 1, CAN_STATUS_RX_READY);
	
}

void CAN2_IRQHandler(void)
{
	CANReceive_typedef *ptr = &CAN2Receive;
	uint8_t data[20];
	
	if(skip_interrup & (1<<CAN2))
	{
		CAN_ITClearRxTxPendingBit(MDR_CAN2, 1, CAN_STATUS_RX_READY);
		ClearSkipInterrupt(CAN2); 
		return;
	}	
	
	if(!uiRingQueIsFull(&QueCAN2))
	{
		CAN_GetRawReceivedData(MDR_CAN2, 1, &ptr->Rx2Message);
	
		data[0]=0xaa;
		memcpy(data+1,&ptr->Rx2Message,sizeof(ptr->Rx2Message));
		uint16_t len = ptr->Rx2Message.Rx_Header.DLC + sizeof(ptr->Rx2Message.Rx_Header)+1;
		RingQuePut(&QueCAN2,data,len);
		LedSwitch(MDR_PORTA,CANACT2);
	}
	
  CAN_ITClearRxTxPendingBit(MDR_CAN2, 1, CAN_STATUS_RX_READY);
	
}

void CANInit(void)
{
  CAN_InitTypeDef sCAN1;
  CAN_InitTypeDef sCAN2;
	
  PORT_InitTypeDef PortInitStructure;	
	
/************************ CAN1  Initialization*************************/
    /* Configure PORTC pins 9..10 for output to switch UART_RX UART_TX */
	PortInitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PortInitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
	PortInitStructure.PORT_PD = PORT_PD_DRIVER;
	PortInitStructure.PORT_GFEN = PORT_GFEN_OFF;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_OVERRID;
  PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  
	PortInitStructure.PORT_Pin   = PORT_Pin_1;
	PortInitStructure.PORT_OE    = PORT_OE_OUT;	
  PORT_Init(MDR_PORTE, &PortInitStructure);
	
	PortInitStructure.PORT_Pin   = PORT_Pin_0;
	PortInitStructure.PORT_OE    = PORT_OE_IN;	
  PORT_Init(MDR_PORTE, &PortInitStructure); 		
    
    //конфигурирование can1
    RST_CLK_PCLKcmd(RST_CLK_PCLK_CAN1 ,ENABLE);                                //тактирование can 1
		CAN_DeInit(MDR_CAN1);
    CAN_BRGInit(MDR_CAN1,CAN_HCLKdiv4);                                         //делитель частоты ћ   
		
    //125  бит
    sCAN1.CAN_ROP  = DISABLE;
    sCAN1.CAN_SAP  = DISABLE;
    sCAN1.CAN_STM  = DISABLE;
    sCAN1.CAN_ROM  = DISABLE;
    sCAN1.CAN_PSEG = CAN_PSEG_Mul_3TQ;
    sCAN1.CAN_SEG1 = CAN_SEG1_Mul_2TQ;
    sCAN1.CAN_SEG2 = CAN_SEG2_Mul_4TQ;
    sCAN1.CAN_SJW  = CAN_SJW_Mul_1TQ;
    sCAN1.CAN_SB   = CAN_SB_3_SAMPLE;
    sCAN1.CAN_BRP  = 15;																											//частота CLK=20ћ√ц, если частота будет 8ћ√ц, то выбрать BRP=4		

//    //500  бит
//    sCAN1.CAN_ROP  = DISABLE;
//    sCAN1.CAN_SAP  = DISABLE;
//    sCAN1.CAN_STM  = DISABLE;
//    sCAN1.CAN_ROM  = DISABLE;
//    sCAN1.CAN_PSEG = CAN_PSEG_Mul_7TQ;
//    sCAN1.CAN_SEG1 = CAN_SEG1_Mul_8TQ;
//    sCAN1.CAN_SEG2 = CAN_SEG2_Mul_4TQ;
//    sCAN1.CAN_SJW  = CAN_SJW_Mul_3TQ;
//    sCAN1.CAN_SB   = CAN_SB_1_SAMPLE;
//    sCAN1.CAN_BRP  = 1;																											//частота CLK=20ћ√ц, если частота будет 8ћ√ц, то выбрать BRP=4
//	
    CAN_Init(MDR_CAN1,&sCAN1);
		
		CAN_Cmd(MDR_CAN1, ENABLE);
		
		CAN_ITConfig(MDR_CAN1, CAN_IT_GLBINTEN | CAN_IT_RXINTEN, ENABLE);
		
//		NVIC_EnableIRQ(CAN1_IRQn);

//		MDR_CAN1->CAN_BUF_FILTER[1].MASK=0x0cf00400;
//		MDR_CAN1->CAN_BUF_FILTER[1].FILTER= 0x0cf00400;
		
		MDR_CAN1->INT_RX |= CAN_BUFFER_1;
		MDR_CAN1->BUF_CON[1] |= (1<<0) | (1<<1);

/************************ CAN2  Initialization*************************/
    /* Configure PORTE pins 6..7 for output to switch UART_RX UART_TX */
	PortInitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PortInitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
	PortInitStructure.PORT_PD = PORT_PD_DRIVER;
	PortInitStructure.PORT_GFEN = PORT_GFEN_OFF;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
  PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
  
	PortInitStructure.PORT_Pin   = PORT_Pin_7;
	PortInitStructure.PORT_OE    = PORT_OE_OUT;	
  PORT_Init(MDR_PORTE, &PortInitStructure);
	
	PortInitStructure.PORT_Pin   = PORT_Pin_6;
	PortInitStructure.PORT_OE    = PORT_OE_IN;	
  PORT_Init(MDR_PORTE, &PortInitStructure); 		
    
    //конфигурирование can2
    RST_CLK_PCLKcmd(RST_CLK_PCLK_CAN2 ,ENABLE);                                //тактирование can 1
		CAN_DeInit(MDR_CAN2);
    CAN_BRGInit(MDR_CAN2,CAN_HCLKdiv4);                                         //делитель частоты ћ   
		
    //125  бит
    sCAN2.CAN_ROP  = DISABLE;
    sCAN2.CAN_SAP  = DISABLE;
    sCAN2.CAN_STM  = DISABLE;
    sCAN2.CAN_ROM  = DISABLE;
    sCAN2.CAN_PSEG = CAN_PSEG_Mul_3TQ;
    sCAN2.CAN_SEG1 = CAN_SEG1_Mul_2TQ;
    sCAN2.CAN_SEG2 = CAN_SEG2_Mul_4TQ;
    sCAN2.CAN_SJW  = CAN_SJW_Mul_1TQ;
    sCAN2.CAN_SB   = CAN_SB_3_SAMPLE;
    sCAN2.CAN_BRP  = 15;																											//частота CLK=20ћ√ц, если частота будет 8ћ√ц, то выбрать BRP=4		

//    //500  бит
//    sCAN2.CAN_ROP  = DISABLE;
//    sCAN2.CAN_SAP  = DISABLE;
//    sCAN2.CAN_STM  = DISABLE;
//    sCAN2.CAN_ROM  = DISABLE;
//    sCAN2.CAN_PSEG = CAN_PSEG_Mul_7TQ;
//    sCAN2.CAN_SEG1 = CAN_SEG1_Mul_8TQ;
//    sCAN2.CAN_SEG2 = CAN_SEG2_Mul_4TQ;
//    sCAN2.CAN_SJW  = CAN_SJW_Mul_3TQ;
//    sCAN2.CAN_SB   = CAN_SB_1_SAMPLE;
//    sCAN2.CAN_BRP  = 1;																											//частота CLK=20ћ√ц, если частота будет 8ћ√ц, то выбрать BRP=4
	
    CAN_Init(MDR_CAN2,&sCAN2);
		
		CAN_Cmd(MDR_CAN2, ENABLE);
		
		CAN_ITConfig(MDR_CAN2, CAN_IT_GLBINTEN | CAN_IT_RXINTEN, ENABLE);
		
//		NVIC_EnableIRQ(CAN2_IRQn);

//		MDR_CAN2->CAN_BUF_FILTER[1].MASK=0x00CB4810;
//		MDR_CAN2->CAN_BUF_FILTER[1].FILTER= 0x00CB4810;
		
		MDR_CAN2->INT_RX |= CAN_BUFFER_1;
		MDR_CAN2->BUF_CON[1] |= (1<<0) | (1<<1);

}

void CANSendMsg(uint32_t id)
{

    TxMessage.IDE=CAN_ID_EXT;
    TxMessage.ID=id;
    TxMessage.DLC=8;
    TxMessage.PRIOR_0 = DISABLE;

    CAN_Transmit(MDR_CAN2, 0, &TxMessage);
    
}

void SetSkipInterrupt(uint8_t ch)
{
	skip_interrup |= (1<<ch);
}

void ClearSkipInterrupt(uint8_t ch)
{
	skip_interrup &= ~(1<<ch);
}
