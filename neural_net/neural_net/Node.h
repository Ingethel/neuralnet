#pragma once

/*used as Hidden Neuron that holds its value and all weights associated with it*/

class Node
{
public:
	Node(void);
	~Node(void);
	double value, WeightOfInputToNode, WeightOfNodeToOutput1, WeightOfNodeToOutput2, WeightOfThresholdToNode;
};

