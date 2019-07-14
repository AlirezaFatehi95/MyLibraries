#include "HAL_ADXL345.h"
uint8_t TEST = 0, TEST1 = 0;
ADXL345_Result ADXL345_Init(SPI_HandleTypeDef* SPIx)
{
	uint8_t reg = (uint8_t)ADXL345_DEVICEIDADD;
	uint8_t temp;
	uint8_t transmit_buffer[2]={0,0};
	
	/* Check Device ID */
//	ADXL345_ReadData(SPIx, &TEST, reg, 1);
//	if(TEST != ADXL345_DEVICEID)
//	{
//		//go to error function
//	}
//	HAL_Delay(5);
//	transmit_buffer[0] = (uint8_t)ADXL345_POWER_CTL;
//	transmit_buffer[1] = 0x00;
//	ADXL345_WriteData(SPIx, transmit_buffer[0], transmit_buffer[1]);
//	HAL_Delay(5);
//	
//	transmit_buffer[1] = 0x10;
//	ADXL345_WriteData(SPIx, transmit_buffer[0], transmit_buffer[1]);
//	HAL_Delay(5);
//	
//	transmit_buffer[1] = 0x08;
//	ADXL345_WriteData(SPIx, transmit_buffer[0], transmit_buffer[1]);
//	HAL_Delay(5);
//	
////	ADXL345_ReadData(SPIx, &TEST1, transmit_buffer[0], 1);
////	HAL_Delay(5);
////	
//	transmit_buffer[0] = (uint8_t)ADXL345_DATA_FORMAT;
//	transmit_buffer[1] = 0x00;
//	ADXL345_WriteData(SPIx, transmit_buffer[0], transmit_buffer[1]);
//	HAL_Delay(25);
//	ADXL345_ReadData(SPIx, &TEST2, transmit_buffer[0], 1);
//	HAL_Delay(25);
	
	/* Return OK */
	return ADXL345_RESULT_OK;
}

//SPI Write Reg

ADXL345_Result ADXL345_WriteData(SPI_HandleTypeDef* SPIx, uint8_t addr, uint8_t data)
{
	uint8_t buffer[2] = {addr, data};
	HAL_GPIO_WritePin(GY291_CS_GPIO_Port, GY291_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPIx, buffer, 2, 10);
	HAL_GPIO_WritePin(GY291_CS_GPIO_Port, GY291_CS_Pin, GPIO_PIN_SET);
	
	/* Return OK */
	return ADXL345_RESULT_OK;
}

//SPI Read Reg

ADXL345_Result ADXL345_ReadData(SPI_HandleTypeDef* SPIx, uint8_t* buffer, uint8_t addr, uint8_t num)
{
	uint8_t reg = addr | 0x80;
	HAL_GPIO_WritePin(GY291_CS_GPIO_Port, GY291_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(SPIx, &reg, 1, 10);
	HAL_SPI_Receive(SPIx, buffer, num, 10);
	HAL_GPIO_WritePin(GY291_CS_GPIO_Port, GY291_CS_Pin, GPIO_PIN_SET);
	
	/* Return OK */
	return ADXL345_RESULT_OK;
}
