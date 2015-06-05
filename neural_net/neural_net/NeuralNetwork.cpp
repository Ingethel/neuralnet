#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(void)
{
}

NeuralNetwork::NeuralNetwork(int complexity){
	if(complexity >= MIN_NUMBER_OF_NODES && complexity <= MAX_NUMBER_OF_NODES){
		this->numberOfHiddenNodes = complexity;
	}
}

NeuralNetwork::~NeuralNetwork(void)
{
}

double NeuralNetwork::GenerateRandom(void){
	r = -10 + rand() % 20;
	r =	r/100.0;
	return r;
}

void NeuralNetwork::Initialise(void){
	this->hiddenNodes.clear();
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->hiddenNodes.push_back(new Node());
		this->hiddenNodes[i]->WeightOfInputToNode = GenerateRandom();
		this->hiddenNodes[i]->WeightOfNodeToOutput1 = GenerateRandom();
		this->hiddenNodes[i]->WeightOfNodeToOutput2 = GenerateRandom();
		this->hiddenNodes[i]->WeightOfThresholdToNode = GenerateRandom();
	}
	this->weightOfThresholdToOutput[0] = GenerateRandom();
	this->weightOfThresholdToOutput[1] = GenerateRandom();
	learningRate = 0.01;
}

void NeuralNetwork::MSE(double expectedOutput1, double expectedOutput2){
	this->E = ( pow((expectedOutput1 - y1),2) + pow((expectedOutput2 - y2),2) ) / 2.0;
}

double NeuralNetwork::InputWeight(double input, double weight){
	return input * weight;
}

double NeuralNetwork::Sigmoid(double input){
	return 1.0 / (1.0 + exp(-input));
}

double NeuralNetwork::DSigmoid(double input){
	return exp(-input) / pow( (1.0 + exp(-input)), 2);
}

void NeuralNetwork::CalculateHidden(double input){
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->hiddenNodes[i]->value = this->InputWeight(input, this->hiddenNodes[i]->WeightOfInputToNode);
	}
}

void NeuralNetwork::CalculateOutput1(double input){
	this->y1 = 0.0;
	this->CalculateHidden(input);
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->y1 += Sigmoid(this->hiddenNodes[i]->value + this->hiddenNodes[i]->WeightOfThresholdToNode)*this->hiddenNodes[i]->WeightOfNodeToOutput1;
	}
	this->y1 += this->weightOfThresholdToOutput[0];
}

void NeuralNetwork::CalculateOutput2(double input){
	this->y2 = 0.0;
	this->CalculateHidden(input);
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->y2 += Sigmoid(this->hiddenNodes[i]->value + this->hiddenNodes[i]->WeightOfThresholdToNode)*this->hiddenNodes[i]->WeightOfNodeToOutput2;
	}
	this->y2 += this->weightOfThresholdToOutput[1];
}

void NeuralNetwork::UpdateWeight(double input, double expectedOutput1, double expectedOutput2){
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->hiddenNodes[i]->WeightOfInputToNode += learningRate * ( (expectedOutput1 - this->y1)*this->hiddenNodes[i]->WeightOfNodeToOutput1 + (expectedOutput2 - this->y2)*this->hiddenNodes[i]->WeightOfNodeToOutput2 ) * DSigmoid(this->hiddenNodes[i]->value) * input;
		this->hiddenNodes[i]->WeightOfThresholdToNode += learningRate * ( (expectedOutput1 - this->y1)*this->hiddenNodes[i]->WeightOfNodeToOutput1 + (expectedOutput2 - this->y2)*this->hiddenNodes[i]->WeightOfNodeToOutput2 ) * DSigmoid(this->hiddenNodes[i]->value);
	}
}

void NeuralNetwork::UpdateVeight(double expectedOutput1, double expectedOutput2){
	for(int i = 0; i < this->numberOfHiddenNodes; i++){
		this->hiddenNodes[i]->WeightOfNodeToOutput1 += learningRate * (expectedOutput1 - this->y1) * Sigmoid(this->hiddenNodes[i]->value);
		this->hiddenNodes[i]->WeightOfNodeToOutput2 += learningRate * (expectedOutput2 - this->y2) * Sigmoid(this->hiddenNodes[i]->value);
	}
	this->weightOfThresholdToOutput[0] += learningRate * (expectedOutput1 - this->y1);// * Sigmoid(1.0);
	this->weightOfThresholdToOutput[1] += learningRate * (expectedOutput2 - this->y2);// * Sigmoid(1.0);
}

void NeuralNetwork::AssignError(double errorTR, double errorVL){
	this->TE = errorTR;
	this->VE = errorVL;
}

void NeuralNetwork::Run(double input, double expectedOutput1, double expectedOutput2){
	this->CalculateOutput1(input);
	this->CalculateOutput2(input);
	this->MSE(expectedOutput1, expectedOutput2);
}

void NeuralNetwork::Update(double input, double expectedOutput1, double expectedOutput2){
	this->UpdateVeight(expectedOutput1, expectedOutput2);
	this->UpdateWeight(input, expectedOutput1, expectedOutput2);
}

