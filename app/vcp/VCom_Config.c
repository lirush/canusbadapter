//  VCom_Config.c

#include "VCom_Config.h"

//#include "main.h"

//----------- main 02.09.2020 
//extern Header_i2c ptr_Header_i2c ;
//--  end main 02.09.2020-
/* Private variables ---------------------------------------------------------*/
USB_Clock_TypeDef USB_Clock_InitStruct;
USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;

uint8_t Buffer[BUFFER_LENGTH];


#ifdef USB_CDC_LINE_CODING_SUPPORTED
static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_VCOM_SYNC
volatile uint32_t PendingDataLength = 0;
#endif /* USB_VCOM_SYNC */

/* USB protocol debugging */
#ifdef USB_DEBUG_PROTO

//#define USB_DEBUG_NUM_PACKETS   100

typedef struct {
  USB_SetupPacket_TypeDef packet;
  uint32_t address;
} TDebugInfo;

static TDebugInfo SetupPackets[USB_DEBUG_NUM_PACKETS];
static uint32_t SPIndex;
static uint32_t ReceivedByteCount, SentByteCount, SkippedByteCount;

#endif /* USB_DEBUG_PROTO */


/* Private function prototypes -----------------------------------------------*/
//static void Setup_CPU_Clock(void);
//static void Setup_USB(void);
//static void VCom_Configuration(void);

 void Setup_CPU_Clock(void);
 void Setup_USB(void);
 void VCom_Configuration(void);


/* Frequencies setup */
void Setup_CPU_Clock(void)
{
  /* Enable HSE (High Speed External) clock */
  RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() == ERROR) {
    while (1);
  }

  /* Configures the CPU_PLL clock source */
  RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);

  /* Enables the CPU_PLL */
  RST_CLK_CPU_PLLcmd(ENABLE);
  if (RST_CLK_CPU_PLLstatus() == ERROR) {
    while (1);
  }

  /* Enables the RST_CLK_PCLK_EEPROM */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
  /* Sets the code latency value */
  EEPROM_SetLatency(EEPROM_Latency_3);

  /* Select the CPU_PLL output as input for CPU_C3_SEL */
  RST_CLK_CPU_PLLuse(ENABLE);
  /* Set CPUClk Prescaler */
  RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

  /* Select the CPU clock source */
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);	
	
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF, ENABLE);
	
}

/* USB Device layer setup and powering on */
void Setup_USB(void)
{
	  /* Enables the CPU_CLK clock on USB */
	  RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);

	  /* Device layer initialization */
	  USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv1;
	  USB_Clock_InitStruct.USB_PLLUSBMUL    = USB_PLLUSBMUL6;

//	USB_DeviceBUSParam.MODE  = USB_SC_SCFSP_Low;
//	USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_1_5Mb;
//	USB_DeviceBUSParam.PULL  = USB_HSCR_DM_PULLUP_Set;

	  USB_DeviceBUSParam.MODE  = USB_SC_SCFSP_Full;
	  USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
	  USB_DeviceBUSParam.PULL  = USB_HSCR_DP_PULLUP_Set;

	  USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);

	  /* Enable all USB interrupts */
	  USB_SetSIM(USB_SIS_Msk);

	  USB_DevicePowerOn();

	  /* Enable interrupt on USB */
	#ifdef USB_INT_HANDLE_REQUIRED
	  NVIC_EnableIRQ(USB_IRQn);
	#endif /* USB_INT_HANDLE_REQUIRED */

	  USB_DEVICE_HANDLE_RESET;
}


/* Example-relating data initialization */
 void VCom_Configuration(void)
{
#ifdef USB_CDC_LINE_CODING_SUPPORTED
  LineCoding.dwDTERate = 115200;
  LineCoding.bCharFormat = 0;
  LineCoding.bParityType = 0;
  LineCoding.bDataBits = 8;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */
}


/* USB_CDC_HANDLE_DATA_RECEIVE implementation - data echoing */
USB_Result USB_CDC_RecieveData(uint8_t* Buffer, uint32_t Length)
{

  USB_Result result;

#ifdef USB_DEBUG_PROTO
  ReceivedByteCount += Length;
#endif /* USB_DEBUG_PROTO */
	
//	result = USB_CDC_SendData(Buffer , 2) ;	

#ifdef USB_DEBUG_PROTO
  if (result == USB_SUCCESS)
  {
    SentByteCount += Length;
  }
#ifndef USB_VCOM_SYNC
  else
  {
    SkippedByteCount += Length;
  }
#endif /* !USB_VCOM_SYNC */
#endif /* USB_DEBUG_PROTO */

#ifdef USB_VCOM_SYNC
  if (result != USB_SUCCESS)
  {
    /* If data cannot be sent now, it will await nearest possibility
     * (see USB_CDC_DataSent) */
    PendingDataLength = Length;
  }
  return result;
#else
  return USB_SUCCESS;
#endif /* USB_VCOM_SYNC */
}


#ifdef USB_VCOM_SYNC

/* USB_CDC_HANDLE_DATA_SENT implementation - sending of pending data */
USB_Result USB_CDC_DataSent(void)
{
  USB_Result result = USB_SUCCESS;
	
  if (PendingDataLength)
  {
    result = USB_CDC_SendData(Buffer, PendingDataLength);
#ifdef USB_DEBUG_PROTO
    if (result == USB_SUCCESS)
    {
      SentByteCount += PendingDataLength;
    }
    else
    {
      SkippedByteCount += PendingDataLength;
    }
#endif /* USB_DEBUG_PROTO */
    PendingDataLength = 0;
    USB_CDC_ReceiveStart();
  }
  return USB_SUCCESS;
}

#endif /* USB_VCOM_SYNC */


#ifdef USB_CDC_LINE_CODING_SUPPORTED

/* USB_CDC_HANDLE_GET_LINE_CODING implementation example */
USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Just store received settings */
  *DATA = LineCoding;
  return USB_SUCCESS;
}

/* USB_CDC_HANDLE_SET_LINE_CODING implementation example */
USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef* DATA)
{
  assert_param(DATA);
  if (wINDEX != 0)
  {
    /* Invalid interface */
    return USB_ERR_INV_REQ;
  }

  /* Just send back settings stored earlier */
  LineCoding = *DATA;
  return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

#ifdef USB_DEBUG_PROTO

/* Overwritten USB_DEVICE_HANDLE_SETUP default handler - to dump received setup packets */
USB_Result USB_DeviceSetupPacket_Debug(USB_EP_TypeDef EPx, const USB_SetupPacket_TypeDef* USB_SetupPacket)
{

#ifdef USB_DEBUG_PROTO
  SetupPackets[SPIndex].packet = *USB_SetupPacket;
  SetupPackets[SPIndex].address = USB_GetSA();
  SPIndex = (SPIndex < USB_DEBUG_NUM_PACKETS ? SPIndex + 1 : 0);
#endif /* USB_DEBUG_PROTO */

  return USB_DeviceSetupPacket(EPx, USB_SetupPacket);
}

#endif /* USB_DEBUG_PROTO */


