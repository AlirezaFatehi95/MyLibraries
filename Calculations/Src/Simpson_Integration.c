#include "Simpson_Integration.h"

////////////////////////////////////////////////////////////////////////////////
void SimpsonIntegration_Init(SimpsontypeDef *simp)
{
	simp->Integral = 0.0;
	simp->State = IsZero;
}
////////////////////////////////////////////////////////////////////////////////
void SimpsonIntegration_Reset(SimpsontypeDef *simp)
{
	simp->Integral = 0.0;
	simp->State = IsZero;
}
////////////////////////////////////////////////////////////////////////////////
double SimpsonIntegration_Update(SimpsontypeDef *simp, double input, double delta_t)
{
	if(simp->State == IsOdd)
	{
		simp->Integral += (delta_t / 3) * 4 * input;
		simp->State = IsEven;
	}
	else if(simp->State == IsEven)
	{
		simp->Integral += (delta_t / 3) * 2 * input;
		simp->State = IsOdd;
	}
	else
	{
		simp->Integral += (delta_t / 3) * input;
		simp->State = IsOdd;
	}
	
	return simp->Integral;
}
////////////////////////////////////////////////////////////////////////////////
