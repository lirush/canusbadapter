#ifndef _CANHACKER_IMPL_H
#define _CANHACKER_IMPL_H

#include "VCom_Config.h"

/*!
Timestamp � ������� ��������� Lawicel
*/
uint32_t uiGetTimestamp(void);

/*!
��������� ascii � ����
*/
uint8_t uiAscii2byte(uint8_t val);

/*!
��������� ���� � ascii
*/
uint8_t uiNibble2ascii(uint8_t byte);

/*!
�������� ������ � CAN �� CANHacker
*/
void PackDataCANHackerToCAN(int offset, uint8_t dlc,uint8_t *dataforpack,uint32_t *dataispack);
uint8_t uiPackDataCANToCANHacker(int offset, uint8_t dlc,uint32_t *dataforpack,uint8_t *dataispack);

#endif
