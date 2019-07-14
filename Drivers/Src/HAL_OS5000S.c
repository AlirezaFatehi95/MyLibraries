#include "HAL_OS5000S.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
void OS5000S_Init(CompassTypeDef *cps)
{
	cps->Counter = 0;
	cps->CheckSumCounter =0;
	cps->PacketStatus = NotStarted;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void OS5000S_Data_Update(CompassTypeDef *cps, double *table, uint8_t input_byte)
{
	cps->Buff[cps->Counter] = input_byte;
	if(cps->PacketStatus == NotStarted)
	{
		if(input_byte == '$')
		{
			cps->PacketStatus = OnGoing;
		}
		cps->Counter = 0;
	}
	else if(cps->PacketStatus == OnGoing)
	{
		if(input_byte == '*')
		{
			cps->PacketStatus = Finished;
		}
		else
		{
			cps->Counter++;
		}
	}
	else
	{
		if(cps->CheckSumCounter == 0)
		{
			cps->CheckSum[0] = input_byte;
			cps->CheckSumCounter++;
		}
		else if(cps->CheckSumCounter == 1)
		{
			cps->CheckSum[1] = input_byte;
			cps->CheckSumCounter++;
		}
		else
		{
//			if(CompassCheckSumClac(cps->Buff, cps->Counter - 1) == (cps->CheckSum[0] << 8 || cps->CheckSum[1]))
//			{
				if(CompassStringToInt(cps->Buff, cps->Counter - 1, table) != HAL_OK)
				{
					//go to error handler
				}
				cps->CheckSumCounter = 0;
				cps->Counter = 0;
				cps->PacketStatus = NotStarted;
//			}
//			else
//			{
//				//go to error handler
//			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//table[0]  -> Azimuth
//table[1]  -> Pitch Angle
//table[2]  -> Roll Angle
//table[3]  -> Temperature
//table[4]  -> Depth (NOT available)
//table[5]  -> Magnetic Vector Length
//table[6]  -> X axis Magnetic Field
//table[7]  -> Y axis Magnetic Field
//table[8]  -> Z axis Magnetic Field
//table[9]  -> Acceleration Vector Length
//table[10] -> X axis Acceleration
//table[11] -> Y axis Acceleration
//table[12] -> Z axis Acceleration
HAL_StatusTypeDef CompassStringToInt(uint8_t *buff, uint8_t nbuff, double *table)
{
	uint8_t n = 0;//buffer counter
	uint8_t m = 0;//table counter
	uint8_t order = 0;
	uint8_t nfraction = 0;
	double temp = 1;//temporary number
	double inum = 0.0;//integer number
	double fnum = 0.0;//fractional number
	uint8_t isnegative = 0;
	//----------------------------------------------------------------------------------------------------
	while(n < nbuff + 1)
	{
		switch(buff[n])
		{
			case 'C':
				m = 0;
				break;
			case 'P':
				m = 1;
				break;
			case 'R':
				m = 2;
				break;
			case 'T':
				m = 3;
				break;
			default:
				return HAL_ERROR;
		}
		n++;
		//----------------------------------------------------------------------------------------------------
		if(buff[n] == '-')
		{
			isnegative = 1;
			n++;
		}
		else
		{
			isnegative = 0;
		}
		//----------------------------------------------------------------------------------------------------
		while((buff[n] < 58) && (buff[n] > 47))//in ASCII table 57='9' and 48='0'
		{
			n++;
			order++;
		}
		while(order !=0)
		{
			order--;
			for(uint8_t i = 0; i < order; i++)
			{
				 temp *= 10;
			}
			inum += (buff[n - order -1] - 48) * temp;//converting to int and multiply by the needed order to remake the real number
			temp = 1;
		}
		order = 0;
		temp = 1;
		//----------------------------------------------------------------------------------------------------
		if(buff[n] == '.')
		{
			n++;
			while(((buff[n] < 58) && (buff[n] > 47)) && (n < nbuff + 1))//in ASCII table 57='9' and 48='0' and check for end of the buffer
			{
				n++;
				order++;
			}
			nfraction = order;
			while(order !=0)
			{
				order--;
				for(uint8_t i = order; i < nfraction; i++)
				{
					 temp /= 10.0;
				}
				fnum += (buff[n - order -1] - 48) * temp;//converting to int and multiply by the needed order to remake the real number
				temp = 1;
			}
		}
		order =0;
		nfraction = 0;
		temp = 1;
		//----------------------------------------------------------------------------------------------------
		if(isnegative)
		{
			table[m] = (inum + fnum) * -1;
		}
		else
		{
			table[m] = (inum + fnum);
		}
		inum = 0.0;
		fnum = 0.0;
	}
	return HAL_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
