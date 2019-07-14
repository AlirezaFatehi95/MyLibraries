#ifndef __SIMPSON_H__
#define __SIMPSON_H__

#include "stdint.h"

typedef enum
{
	IsZero = 0,
	IsOdd = 1,
	IsEven = 2
}NumberState;

typedef struct
{
	double Integral;
	NumberState State;
}SimpsontypeDef;

void SimpsonIntegration_Init(SimpsontypeDef *simp);
void SimpsonIntegration_Reset(SimpsontypeDef *simp);
double SimpsonIntegration_Update(SimpsontypeDef *simp, double input, double sec);

#endif /*__SIMPSON_H__*/
