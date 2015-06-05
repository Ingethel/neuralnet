#pragma once

/*Neural Network for one input, two outputs, two threshold neurons and up to 15 hidden neurons, update weights with back propagation*/

#include "GenerateSamples.h"
#include "Node.h"

class NeuralNetwork
{
public:
	NeuralNetwork(void);
	NeuralNetwork(int complexity);
	~NeuralNetwork(void);
	void MSE(double expectedOutput1, double expectedOutput2);
	void UpdateWeight(double input, double expectedOutput1, double expectedOutput2);
	void UpdateVeight(double expectedOutput1, double expectedOutput2);
	void CalculateOutput1(double input);
	void CalculateOutput2(double input);
	void Initialise(void);
	double GenerateRandom(void);
	void AssignError(double errorTR, double errorVL);
	void Run(double input, double expectedOutput1, double expectedOutput2);
	void Update(double input, double expectedOutput1, double expectedOutput2);
	double E, TE, VE, y1, y2;
	int numberOfHiddenNodes;
	static const int MAX_NUMBER_OF_NODES = 15;
	static const int MIN_NUMBER_OF_NODES = 1;
	vector<Node*> hiddenNodes;
private:
	void CalculateHidden(double input);
	double InputWeight(double input, double weight);
	double Sigmoid(double input);
	double DSigmoid(double input);
	double learningRate;
	double r;
	double weightOfThresholdToOutput[2];
};