#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(void)
{
	this->bestNumberOfNodes = 0;		
}


GeneticAlgorithm::~GeneticAlgorithm(void)
{
}

void GeneticAlgorithm::Initialise(int population){
	networks.clear();
	for(int i = 1; i <= population; i++){
		networks.push_back(new NeuralNetwork ( 1 + rand()%15 ));
	}
	this->mutationProp = 0.20;
}

void GeneticAlgorithm::FindBest(void){
	double min = 1000000.0;
	this->bestNumberOfNodes = 0;
	for(int i = 0; i < networks.size(); i++){
		if(networks[i]->TE < min) {
			min = networks[i]->TE;
			this->bestNumberOfNodes = networks[i]->numberOfHiddenNodes;
			this->bestTrainingError = networks[i]->TE;
			this->bestValidationError = networks[i]->VE;
		}
	}
}

void GeneticAlgorithm::Mutate(){
	vector<int> binary;
	for(int i = 0; i < networks.size(); i++){
		if(networks[i]->numberOfHiddenNodes != this->bestNumberOfNodes){
			this->encode(binary, networks[i]->numberOfHiddenNodes);
			while(binary.size()!=4) binary.push_back(0);
			for(int y = 0; y < binary.size(); y++){
				if( (rand()%100)/10 <= this->mutationProp) binary[y] ^= 1;
			}
			this->decode(binary, networks[i]->numberOfHiddenNodes);
		}
	}
}

void GeneticAlgorithm::encode(vector<int> & binary, int number){
	if(number > 0){
		encode(binary, number/2);
		binary.push_back(number%2);
	}
}

void GeneticAlgorithm::decode(vector<int> & binary, int & number){
	int temp = 0;
	for(int y = 0; y < binary.size(); y++){
		if(binary[y] == 1) temp += pow(2.0, y);
	}
	if(temp!=0) number = temp;
	binary.clear();
}