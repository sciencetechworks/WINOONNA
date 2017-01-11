/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#pragma once
#include "Sinapsis.h"
#include "Neuron.h"
#include "TransferFunction.h"
#include "LearningFunction.h"
#include "TrainingAlgorithm.h"
#include "Logger.h"
#include "Layer.h"
#include "Pattern.h"
// -- STL Imports --
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
// ------------------
class Layer;
class Sinapsis;
class Neuron;
class TransferFunction;
class LearningFunction;
class TrainingAlgorithm;
class PerceptronTrainingAlgorithm;


class NeuralNet
{

friend class Neuron;
friend class TrainingAlgorithm;
friend class PerceptronTrainingAlgorithm;
friend class Layer;

public:
 Layer *input_layer;
 Layer *output_layer;
 list<Sinapsis*> sinapsis_list;
 list<Neuron*> neurons_list;
 list<Neuron*> biases_list;
 list<Layer *> hidden_layers;

 
 

public:
 
 Logger logger;

 TransferFunction *transfer_function;
 LearningFunction *learning_function;
 TrainingAlgorithm *training_algorithm;


     NeuralNet(void);
	~NeuralNet(void);

	Neuron *createNeuron();
	Sinapsis *createSinapsis(Neuron *start,Neuron *end,double weight);
	void setTransfer_function(TransferFunction *tf);
	void setLearning_function(LearningFunction *lf);
	void setTraining_algorithm(TrainingAlgorithm *algo);
	void resetKnowledge();

	Layer *createHiddenLayer();
	void registerAsBias(Neuron *neuron);
	void registerAsInputLayerNeuron(Neuron *neuron);
	void registerAsOutputLayerNeuron(Neuron *neuron);	
	void registerAsHiddenLayerNeuron(Neuron *neuron,Layer *layer);

	void turn_on_all_Bias();

	bool save(const char *path);
	bool load(const char *path);

	int getNeuronIndex(Neuron *neuron);
	Neuron *getNeuronAt(int index);
	Neuron *getNeuron(string name);

	bool isBias(Neuron *neuron);
	Neuron *getBias(Neuron *neuron);

	Sinapsis *NeuralNet::getSinapsis(Neuron *n1,Neuron *n2);

	void print();

	void empty_contents();

	void setInput(Pattern *pattern);
	Pattern *getOutput(int rows,int cols);

	virtual void predict();
};
