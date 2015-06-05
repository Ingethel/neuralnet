#pragma once

/*Genetic Algorithm that generates different neural networks and optimises the number of hidden neurons*/

#include "NeuralNetwork.h"
#include <time.h>

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(void);
	~GeneticAlgorithm(void);
	void Initialise(int population);
	void FindBest(void);
	void Mutate(void);
	vector<NeuralNetwork*> networks;
	int bestNumberOfNodes;
	double bestTrainingError, bestValidationError;
private:
	void encode(vector<int> & binary, int number);
	void decode(vector<int> & binary, int & number);
	double mutationProp;
};

