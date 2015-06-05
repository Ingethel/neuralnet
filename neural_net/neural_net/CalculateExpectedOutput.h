#pragma once

/*calculate the two expected outputs of the training and validation data*/

#include <cmath>

class CalculateExpectedOutput
{
public:
	CalculateExpectedOutput(void);
	~CalculateExpectedOutput(void);
	double Y1(double input);
	double Y2(double input);
};

