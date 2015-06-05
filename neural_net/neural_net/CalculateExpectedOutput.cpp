#include "CalculateExpectedOutput.h"

CalculateExpectedOutput::CalculateExpectedOutput(void)
{
}


CalculateExpectedOutput::~CalculateExpectedOutput(void)
{
}

double CalculateExpectedOutput::Y1(double x){
	return 2*sin(x) - 1.0;
}

double CalculateExpectedOutput::Y2(double x){
	return cos(x) + 1.0;
}