#ifndef __HAL_OS5000S_H__
#define __HAL_OS5000S_H__

#include "stm32f4xx_hal.h"
#include "MyDefault.h"

#define COMPASSBUFF_MAX 40

typedef struct
{
	uint8_t Buff[COMPASSBUFF_MAX];
	uint8_t Counter;
	uint8_t CheckSum[2];
	uint8_t CheckSumCounter;	
	PacketStatus PacketStatus;
}CompassTypeDef;

void OS5000S_Init(CompassTypeDef *cps);
void OS5000S_Data_Update(CompassTypeDef *cps, double *table, uint8_t input_byte);
HAL_StatusTypeDef CompassStringToInt(uint8_t *buff, uint8_t nbuff, double *table);
#endif /*__HAL_OS5000S_H__*/
