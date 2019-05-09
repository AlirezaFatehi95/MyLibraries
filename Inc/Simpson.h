#ifndef __SIMPSON_H__
#define __SIMPSON_H__

#include "stdint.h"
#include "MyDefault.h"

typedef struct
{
	double Integral;
	NumberState State;
}SimpsontypeDef;

void SimpsonIntegration_Init(SimpsontypeDef *simp);
double SimpsonIntegration_Update(SimpsontypeDef *simp, double input, double sec);

#endif /*__SIMPSON_H__*/
