#include "GeneticAlgorithm.h"

void convertInt(int number, string & name)
{
	stringstream ss;
	ss << number;
	name= ss.str();
}

void run_NN(){

	// generate samples
	GenerateSamples sample;
	sample.Generate();

	// initialise neural network with (5) hidden neurons
	NeuralNetwork network(5);
	network.Initialise();

	// set output file
	FileReader output;
	output.OpenFile("EMS.dat");

	double input, y1, y2;
	double TE, VE;

	int max_iterations = 5000;

	// run for maximum iterations
	for(int i = 0; i < max_iterations; i++){
		TE = 0.0;
		VE = 0.0;

		// train on data
		for(int k = 0; k < sample.trainingSamples.size(); k++){
			input = sample.trainingSamples[k];
			y1 = sample.trY1[k];
			y2 = sample.trY2[k];
			network.Run(input, y1, y2);
			TE += network.E;
			network.Update(input, y1, y2);
		}	

		// validate training
		for(int k = 0; k < sample.validationSamples.size(); k++){
			input = sample.validationSamples[k];
			y1 = sample.vlY1[k];
			y2 = sample.vlY2[k];
			network.Run(input, y1, y2);
			VE += network.E;
		}

		// save mean squared error for training and validation
		TE = TE / 25.0;
		VE = VE / 25.0;
		output.WriteFile(i+1, TE, VE);
	}	

	output.CloseFile();

}

void run_GA(){

	GenerateSamples sample;
	sample.Generate();

	GeneticAlgorithm GA;
	int pop;
	cout << "insert number of neural networks" << endl;
	cin >> pop;
	GA.Initialise(pop);

	string nameOfFile;
	vector<FileReader*> outputs;
	FileReader best;
	double input, y1, y2;
	double TE, VE;

	// open output data files
	for(int n = 0; n < GA.networks.size(); n++){
		outputs.push_back(new FileReader());
		string name;
		convertInt(n+1, name);
		nameOfFile = "EMS"+name+".dat";
		outputs[n]->OpenFile(nameOfFile);
		nameOfFile.clear();
	}
	best.OpenFile("best.dat");

	// different generation of GA
	for(int z = 0; z < 100; z++){
		// loop of GA to find optimal # of Nodes
		for(int n = 0; n < GA.networks.size(); n++){
			GA.networks[n]->Initialise();

			// loop of NN to find MSE and update weights
			for(int i = 0; i < 5000; i++){
				TE = 0.0;
				VE = 0.0;

				// loop of 1 NN generation through training input data
				for(int k = 0; k < sample.trainingSamples.size(); k++){
					if(GA.networks[n]->numberOfHiddenNodes != GA.bestNumberOfNodes){

						input = sample.trainingSamples[k];
						y1 = sample.trY1[k];
						y2 = sample.trY2[k];
						GA.networks[n]->Run(input, y1, y2);
						TE += GA.networks[n]->E;
						GA.networks[n]->Update(input, y1, y2);
					}
				}	

				// loop of 1 NN generation through validation input data
				for(int k = 0; k < sample.validationSamples.size(); k++){
					if(GA.networks[n]->numberOfHiddenNodes != GA.bestNumberOfNodes){
						input = sample.validationSamples[k];
						y1 = sample.vlY1[k];
						y2 = sample.vlY2[k];
						GA.networks[n]->Run(input, y1, y2);
						VE += GA.networks[n]->E;
					}
				}

				TE = TE / (double)sample.trainingSamples.size();
				VE = VE / (double)sample.validationSamples.size();
			}	
			if(GA.networks[n]->numberOfHiddenNodes != GA.bestNumberOfNodes){

				outputs[n]->WriteFile(GA.networks[n]->numberOfHiddenNodes, TE, VE);
				GA.networks[n]->AssignError(TE, VE);

			}else{
				outputs[n]->WriteFile(GA.networks[n]->numberOfHiddenNodes, 0.0, 0.0);
			}		
		}

		// after GA has run find best and mutate others
		GA.FindBest();
		best.WriteFile(GA.bestNumberOfNodes, GA.bestTrainingError, GA.bestValidationError);
		GA.Mutate();

		if(z == 0){
			cout << "iteration # : " << z << endl;
			for(int k = 0; k < GA.networks.size(); k++)
				cout << GA.networks[k]->numberOfHiddenNodes << endl;	
		}

		cout << "iteration # : " << z+1 << " best # " << GA.bestNumberOfNodes << endl;
		for(int k = 0; k < GA.networks.size(); k++)
			cout << GA.networks[k]->numberOfHiddenNodes<<endl;
	}

	// after the end of GA, close all files and clear vector memory
	for(int n = 0; n < GA.networks.size(); n++){
		outputs[n]->CloseFile();
	}

	outputs.clear();
	best.CloseFile();

}

int main(){
	
	// 1: runs simple neural network, 2: run optimisation of NN with Genetic Algorithm
	cout<<"RUN OPTION: Neural Network (1) or Genetic Algorithm (2)"<<endl;
	int a = 0;
	
	while (a != 1 && a !=2) 	
		cin>>a;

	if(a==1)
		run_NN();
	else
		run_GA();

	system("pause");
	return 0;
	
}