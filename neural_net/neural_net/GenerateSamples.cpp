#include "GenerateSamples.h"

GenerateSamples::GenerateSamples(void)
{
}


GenerateSamples::~GenerateSamples(void)
{
}

void GenerateSamples::Generate(){
	FileReader train, valid;
	CalculateExpectedOutput output;
	vector<double> samples;
	double x = 0.0;
	double step = 0.06;
	int random = 0;
	int size = 0;
	for(int i = 0 ; i < 50 ; i++){
		x += step;
		samples.push_back(x);
	}
	train.OpenFile("train.dat");
	valid.OpenFile("valid.dat");
	int s = samples.size()/2;
	for(int i = 0; i < s; i++){
		random = rand() % (samples.size() - 1);
		train.WriteFile(samples[random], output.Y1(samples[random]), output.Y2(samples[random]));
		this->trainingSamples.push_back(samples[random]);
		this->trY1.push_back(output.Y1(samples[random]));
		this->trY2.push_back(output.Y2(samples[random]));
		samples.erase(samples.begin() + random);
	}
	for(int y = 0; y < samples.size(); y++){
		valid.WriteFile(samples[y], output.Y1(samples[y]), output.Y2(samples[y]));
		this->validationSamples.push_back(samples[y]);
		this->vlY1.push_back(output.Y1(samples[y]));
		this->vlY2.push_back(output.Y2(samples[y]));
	}
	samples.clear();
	train.CloseFile();
	valid.CloseFile();
}