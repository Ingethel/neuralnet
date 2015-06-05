#include "Node.h"


Node::Node(void)
{
	this->value = 0.0;
	this->WeightOfInputToNode = 0.0;
	this->WeightOfNodeToOutput1 = 0.0;
	this->WeightOfNodeToOutput2 = 0.0;
	this->WeightOfThresholdToNode = 0.0;
}


Node::~Node(void)
{
}
