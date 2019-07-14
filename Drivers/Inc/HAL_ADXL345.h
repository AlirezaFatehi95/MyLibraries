#ifndef __HAL_ADXL345_H__
#define __HAL_ADXL345_H__

#include "stm32f4xx_hal.h"
#include "main.h"

/* Device identification registers */
#define ADXL345_DEVICEIDADD          0x00
#define ADXL345_DEVICEID             0xE5
/* ADXL345 registers */
#define ADXL345_OFFSET_X             0x1E
#define ADXL345_OFFSET_Y             0x1F
#define ADXL345_OFFSET_Z             0x20
#define ADXL345_POWER_CTL            0x2D
#define ADXL345_DATA_FORMAT          0x31
#define ADXL345_DATA_X0              0x32
#define ADXL345_DATA_X1              0x33
#define ADXL345_DATA_Y0              0x34
#define ADXL345_DATA_Y1              0x35
#define ADXL345_DATA_Z0              0x36
#define ADXL345_DATA_Z1              0x37

typedef enum
{
	ADXL345_RESULT_OK    = 0x00U,
	ADXL345_RESULT_ERROR = 0X01U
}ADXL345_Result;

ADXL345_Result ADXL345_Init(SPI_HandleTypeDef* SPIx);
ADXL345_Result ADXL345_WriteData(SPI_HandleTypeDef* SPIx, uint8_t addr, uint8_t data);
ADXL345_Result ADXL345_ReadData(SPI_HandleTypeDef* SPIx, uint8_t* buffer, uint8_t addr, uint8_t num);

#endif /* __HAL_ADXL345_H__*/
