#ifndef __HAL_SIGNAL_H__
#define __HAL_SIGNAL_H__

#include "stm32f4xx_hal.h"
#include "MyDefault.h"

typedef struct
{
	uint8_t SPwr_Buff[5];
	uint8_t SPwr_Counter;
}SignalPowerTypeDef;

typedef struct
{
	uint8_t SPos_Buff[30];
	uint8_t SPos_Counter;
	PacketStatus PacketStatus;
}SignalPositionTypeDef;

HAL_StatusTypeDef SignalPower_Update(SignalPowerTypeDef *sig, uint8_t data, uint16_t *power, uint8_t *lock);
HAL_StatusTypeDef SignalPosition_Update(SignalPositionTypeDef *sig, uint8_t data, double *pos);
HAL_StatusTypeDef SignalStringToInt(uint8_t *buff, uint8_t nbuff, double *table);

#endif /*__HAL_SIGNAL_H__*/
