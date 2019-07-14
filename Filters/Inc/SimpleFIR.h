#ifndef __SIMPLEFIR_H__
#define __SIMPLEFIR_H__

#include "stdint.h"

typedef struct
{
	double *CoE;
	uint16_t nTaps;
	double *Buff;
	uint16_t Index;
}FIRTypeDef;

void FIRInit(FIRTypeDef *fir, double *coe, uint16_t ntaps);
double FIRProcess(FIRTypeDef *fir ,double in);

#endif /* __SIMPLEFIR_H__ */
