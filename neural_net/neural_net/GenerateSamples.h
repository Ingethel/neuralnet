#pragma once

/*generate training and validation samples and store them in files*/

#include "FileReader.h"
#include "CalculateExpectedOutput.h"

class GenerateSamples
{
public:
	GenerateSamples(void);
	~GenerateSamples(void);
	void Generate();
	vector<double> trainingSamples, validationSamples;
	vector<double> trY1, trY2, vlY1, vlY2;
};

