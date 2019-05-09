#include "HAL_Signal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
HAL_StatusTypeDef SignalPosition_Update(SignalPositionTypeDef *sig, uint8_t data, double *pos)
{
	sig->SPos_Buff[sig->SPos_Counter] = data;
	if(sig->PacketStatus == NotStarted)
	{
		if(data == '$')
		{
			sig->PacketStatus = OnGoing;
		}
		sig->SPos_Counter = 0;
	}
	else if(sig->PacketStatus == OnGoing)
	{
		if(data == '*')
		{
			if(SignalStringToInt(sig->SPos_Buff, sig->SPos_Counter - 1, pos) == HAL_OK)
			{
				sig->SPos_Counter = 0;
				sig->PacketStatus = NotStarted;
				return HAL_OK;
			}
			else
			{
				sig->SPos_Counter = 0;
				sig->PacketStatus = NotStarted;
				//go to error handler
			}
		}
		else
		{
			sig->SPos_Counter++;
		}
	}
	return HAL_BUSY;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//table[0]  -> Azimuth
//table[1]  -> Elevation
//table[2]  -> Polar
HAL_StatusTypeDef SignalStringToInt(uint8_t *buff, uint8_t nbuff, double *table)
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
			case 'A':
				m = 0;
				break;
			case 'E':
				m = 1;
				break;
			case 'P':
				m = 2;
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
			n++;
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
HAL_StatusTypeDef SignalPower_Update(SignalPowerTypeDef *sig, uint8_t data, uint16_t *power, uint8_t *lock)
{
	sig->SPwr_Buff[sig->SPwr_Counter] = data;
	if(sig->SPwr_Counter == 0)
	{
		if(data == 'N')
		{
			*lock = 0;
			return HAL_ERROR;
		}
		else if(data == 'M')
		{
			sig->SPwr_Counter = 1;
		}
		else
		{
			sig->SPwr_Counter = 0;
		}
	}
	else
	{
		sig->SPwr_Counter++;
	}
	if(sig->SPwr_Counter == 4)
	{
		*power = (uint16_t)(sig->SPwr_Buff[1] << 8 | sig->SPwr_Buff[3]);
		*lock = 1;
		sig->SPwr_Counter = 0;
		return HAL_OK;
	}
	return HAL_BUSY;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
