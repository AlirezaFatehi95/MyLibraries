#include "SimpleFIR.h"

void FIRInit(FIRTypeDef *fir, double *coe, uint16_t ntaps)
{
	fir->CoE = coe;
	fir->nTaps = ntaps;
}

double FIRProcess(FIRTypeDef *fir ,double in)
{
	double out = 0;
	
	fir->Buff[fir->Index] = in;
	
	for(uint16_t i = 0;i < fir->nTaps;i++)
	{
		out += (fir->CoE[i] * fir->Buff[(i + fir->Index + 1) % fir->nTaps]);
	}
	
	fir->Index++;
	if(fir->Index == fir->nTaps)
		fir->Index = 0;
	
	return out;
}
