/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "BackPropagation.h"
#include "utils.h"


BackPropagation::BackPropagation(void)
{
 transfer_function=new BackPropagationTransferFunction();
 learning_function=new BackPropagationLearningFunction();
 learning_function->setNet(this);
 training_algorithm=new BackPropagationTrainingAlgorithm(this);
 map_results_to_0_1=false;
}

BackPropagation::BackPropagation(int n_inputs,int n_hidden,int n_outputs)
{
 transfer_function=new BackPropagationTransferFunction();
 learning_function=new BackPropagationLearningFunction();
 learning_function->setNet(this);
 training_algorithm=new BackPropagationTrainingAlgorithm(this);
 map_results_to_0_1=false;
 

 for (int i=0;i<n_inputs;i++)
 {
	Neuron *neuron=createNeuron();
	neuron->name="X"+to_string(i+1);
	registerAsInputLayerNeuron(neuron);
 }

 
 int biascount=1;
 Layer *hidden_layer=createHiddenLayer();
 for (int i=0;i<n_hidden;i++)
 {
  	Neuron *neuron=createNeuron();
	neuron->name="Z"+to_string(i+1);	 
    registerAsHiddenLayerNeuron(neuron,hidden_layer);

	//BIAS
	Neuron *bias=createNeuron();
	bias->name="B"+to_string(biascount);
    registerAsHiddenLayerNeuron(bias,hidden_layer);
	registerAsBias(bias);

	Sinapsis *sinapsis=createSinapsis(bias,neuron,0.0);
	sinapsis->name="Wb"+to_string(biascount);
	biascount++;
 }

 
 for (int i=0;i<n_outputs;i++)
 {
	Neuron *neuron=createNeuron();
	neuron->name="Y"+to_string(i+1);
	registerAsOutputLayerNeuron(neuron);

	
	//BIAS
	Neuron *bias=createNeuron();
	bias->name="B"+to_string(biascount);
    registerAsOutputLayerNeuron(bias);
	registerAsBias(bias);
	Sinapsis *sinapsis=this->createSinapsis(bias,neuron,0.0);
	sinapsis->name="Wb"+to_string(biascount);
	biascount++;
 }
 
 list<Neuron*>::iterator input_neurons_iter; 
 list<Neuron*>::iterator hidden_neurons_iter;
 list<Neuron*>::iterator output_neurons_iter;
 //Sinapsis entrada->hidden:
 int i=1,j=1;

 list<Neuron*> input_neuron_list = input_layer->getNeuron_list();
 input_neurons_iter= input_neuron_list.begin();
 while (input_neurons_iter!= input_neuron_list.end())
 {
    list<Neuron*> hidden_neuron_list = hidden_layer->getNeuron_list();
	hidden_neurons_iter=hidden_neuron_list.begin();
	while(hidden_neurons_iter!=hidden_neuron_list.end())
	{
     Neuron *start=*input_neurons_iter;
	 Neuron *end=*hidden_neurons_iter;
	 if ((!isBias(end))&&(!isBias(start)))
	 {
		Sinapsis *sinapsis;
		sinapsis=createSinapsis(start,end,0.0);
		sinapsis->name="w"+to_string(i)+to_string(j);
		j++;
	 }
	 hidden_neurons_iter++;
	}
 i++;
 input_neurons_iter++;
 }
 
 //Sinapsis hidden->salida:
 i=1,j=1;
 list<Neuron*> hidden_neuron_list = hidden_layer->getNeuron_list();
 hidden_neurons_iter=hidden_neuron_list.begin();
 while(hidden_neurons_iter!=hidden_neuron_list.end())
 {
	list<Neuron*> output_neuron_list = output_layer->getNeuron_list();
	output_neurons_iter= output_neuron_list.begin();
	while (output_neurons_iter!= output_neuron_list.end())
	{
     Neuron *start=*hidden_neurons_iter;
	 Neuron *end=*output_neurons_iter;
	 if ((!isBias(end))&&(!isBias(start)))
	 {
		Sinapsis *sinapsis;
		sinapsis=createSinapsis(start,end,0.0);
		sinapsis->name="v"+to_string(i)+to_string(j);
		j++;
	 }
	 output_neurons_iter++;
	}
 i++;
 hidden_neurons_iter++;
 }

 turn_on_all_Bias();
}

BackPropagation::~BackPropagation(void)
{
	delete transfer_function;
	delete learning_function;
	delete training_algorithm;
}

void BackPropagation::setLearningFactor(double alpha)
{
	((BackPropagationLearningFunction*)learning_function)->setLearning_factor(alpha);
}

void BackPropagation::predict()
{
 NeuralNet::predict();
 
 // Recorremos la capa de salida convirtiendo las salidas 
 // en coma flotante a bipolar, si >0 => 1 si <0 => -1
  
  list<Neuron*> neuronlist=this->output_layer->getNeuron_list();
  list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();

	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		
		double output=neuron->getFired_output();
		//cout<<to_string<double>(output)<<endl;
		if (map_results_to_0_1==true)
		{
		if (output<=0)
			neuron->setFired_output(-1.0);
		else
			neuron->setFired_output(1.0);
		}

		output_neuron_iter++;
	  }
 
}/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "BackPropagation.h"
#include "utils.h"


BackPropagation::BackPropagation(void)
{
 transfer_function=new BackPropagationTransferFunction();
 learning_function=new BackPropagationLearningFunction();
 learning_function->setNet(this);
 training_algorithm=new BackPropagationTrainingAlgorithm(this);
 map_results_to_0_1=false;
}

BackPropagation::BackPropagation(int n_inputs,int n_hidden,int n_outputs)
{
 transfer_function=new BackPropagationTransferFunction();
 learning_function=new BackPropagationLearningFunction();
 learning_function->setNet(this);
 training_algorithm=new BackPropagationTrainingAlgorithm(this);
 map_results_to_0_1=false;
 

 for (int i=0;i<n_inputs;i++)
 {
	Neuron *neuron=createNeuron();
	neuron->name="X"+to_string(i+1);
	registerAsInputLayerNeuron(neuron);
 }

 
 int biascount=1;
 Layer *hidden_layer=createHiddenLayer();
 for (int i=0;i<n_hidden;i++)
 {
  	Neuron *neuron=createNeuron();
	neuron->name="Z"+to_string(i+1);	 
    registerAsHiddenLayerNeuron(neuron,hidden_layer);

	//BIAS
	Neuron *bias=createNeuron();
	bias->name="B"+to_string(biascount);
    registerAsHiddenLayerNeuron(bias,hidden_layer);
	registerAsBias(bias);

	Sinapsis *sinapsis=createSinapsis(bias,neuron,0.0);
	sinapsis->name="Wb"+to_string(biascount);
	biascount++;
 }

 
 for (int i=0;i<n_outputs;i++)
 {
	Neuron *neuron=createNeuron();
	neuron->name="Y"+to_string(i+1);
	registerAsOutputLayerNeuron(neuron);

	
	//BIAS
	Neuron *bias=createNeuron();
	bias->name="B"+to_string(biascount);
    registerAsOutputLayerNeuron(bias);
	registerAsBias(bias);
	Sinapsis *sinapsis=this->createSinapsis(bias,neuron,0.0);
	sinapsis->name="Wb"+to_string(biascount);
	biascount++;
 }
 
 list<Neuron*>::iterator input_neurons_iter; 
 list<Neuron*>::iterator hidden_neurons_iter;
 list<Neuron*>::iterator output_neurons_iter;
 //Sinapsis entrada->hidden:
 int i=1,j=1;

 list<Neuron*> input_neuron_list = input_layer->getNeuron_list();
 input_neurons_iter= input_neuron_list.begin();
 while (input_neurons_iter!= input_neuron_list.end())
 {
    list<Neuron*> hidden_neuron_list = hidden_layer->getNeuron_list();
	hidden_neurons_iter=hidden_neuron_list.begin();
	while(hidden_neurons_iter!=hidden_neuron_list.end())
	{
     Neuron *start=*input_neurons_iter;
	 Neuron *end=*hidden_neurons_iter;
	 if ((!isBias(end))&&(!isBias(start)))
	 {
		Sinapsis *sinapsis;
		sinapsis=createSinapsis(start,end,0.0);
		sinapsis->name="w"+to_string(i)+to_string(j);
		j++;
	 }
	 hidden_neurons_iter++;
	}
 i++;
 input_neurons_iter++;
 }
 
 //Sinapsis hidden->salida:
 i=1,j=1;
 list<Neuron*> hidden_neuron_list = hidden_layer->getNeuron_list();
 hidden_neurons_iter=hidden_neuron_list.begin();
 while(hidden_neurons_iter!=hidden_neuron_list.end())
 {
	list<Neuron*> output_neuron_list = output_layer->getNeuron_list();
	output_neurons_iter= output_neuron_list.begin();
	while (output_neurons_iter!= output_neuron_list.end())
	{
     Neuron *start=*hidden_neurons_iter;
	 Neuron *end=*output_neurons_iter;
	 if ((!isBias(end))&&(!isBias(start)))
	 {
		Sinapsis *sinapsis;
		sinapsis=createSinapsis(start,end,0.0);
		sinapsis->name="v"+to_string(i)+to_string(j);
		j++;
	 }
	 output_neurons_iter++;
	}
 i++;
 hidden_neurons_iter++;
 }

 turn_on_all_Bias();
}

BackPropagation::~BackPropagation(void)
{
	delete transfer_function;
	delete learning_function;
	delete training_algorithm;
}

void BackPropagation::setLearningFactor(double alpha)
{
	((BackPropagationLearningFunction*)learning_function)->setLearning_factor(alpha);
}

void BackPropagation::predict()
{
 NeuralNet::predict();
 
 // Recorremos la capa de salida convirtiendo las salidas 
 // en coma flotante a bipolar, si >0 => 1 si <0 => -1
  
  list<Neuron*> neuronlist=this->output_layer->getNeuron_list();
  list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();

	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		
		double output=neuron->getFired_output();
		//cout<<to_string<double>(output)<<endl;
		if (map_results_to_0_1==true)
		{
		if (output<=0)
			neuron->setFired_output(-1.0);
		else
			neuron->setFired_output(1.0);
		}

		output_neuron_iter++;
	  }
 
}