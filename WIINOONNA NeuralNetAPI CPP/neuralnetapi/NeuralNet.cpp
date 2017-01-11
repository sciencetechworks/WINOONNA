/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "NeuralNet.h"

NeuralNet::NeuralNet(void)
{
	logger.init("c:/neural_net.log");
	this->input_layer=new Layer();
	this->output_layer=new Layer();
	
}

NeuralNet::~NeuralNet(void)
{
	//logger.log("NeuralNet destructor called\n");
	
	empty_contents();
	logger.close();
	delete input_layer;
	delete output_layer;
}

void NeuralNet::empty_contents()
{
	while(!neurons_list.empty())
	{
		delete(neurons_list.back());
		neurons_list.pop_back();
	}

	while(!sinapsis_list.empty())
	{
		delete(sinapsis_list.back());
		sinapsis_list.pop_back();
	}

	while (!input_layer->neuron_list.empty())
	{
		input_layer->neuron_list.pop_back();
	}

	while (!output_layer->neuron_list.empty())
	{
		output_layer->neuron_list.pop_back();
	}

	while (!hidden_layers.empty())
	{
		delete(hidden_layers.back());
		hidden_layers.pop_back();
	}

	while (!biases_list.empty())
	{
		biases_list.pop_back();
	}



}

Neuron* NeuralNet::createNeuron()
{
	Neuron *neuron=new Neuron();
	neurons_list.push_back(neuron);
	neuron->net=this;
	return neuron;
}

Sinapsis *NeuralNet::createSinapsis(Neuron *start,Neuron *end,double weight)
{
 Sinapsis *sinapsis=new Sinapsis();
 sinapsis->setStart(start);
 sinapsis->setEnd(end);
 sinapsis->setWeight(weight);
 sinapsis_list.push_back(sinapsis);

 start->getOutputs()->push_back(sinapsis);
 end->getInputs()->push_back(sinapsis);

 return sinapsis;
}

void NeuralNet::resetKnowledge()
{
	list<Neuron*>::iterator niter=neurons_list.begin();
	while (niter!=neurons_list.end())
	{
		Neuron *neuron=*niter++;
		neuron->commited_error=0.0;
		neuron->setFired_output(0.0);
		neuron->setReceived_input(0.0);

	}

	list<Neuron*>::iterator biter=biases_list.begin();
	while (biter!=biases_list.end())
	{
		Neuron *neuron=*biter++;
		neuron->commited_error=0.0;
		neuron->setFired_output(1.0);
	}


	list<Sinapsis*>::iterator current = this->sinapsis_list.begin();
	while (current != this->sinapsis_list.end())
	{
		Sinapsis *sinapsis=*current;
		sinapsis->setWeight(0.0);
		sinapsis->setWeight_update(0.0);
		current++;
	}
}

void NeuralNet::setTransfer_function(TransferFunction *tf)
{
	transfer_function=tf;
}

void NeuralNet::setLearning_function(LearningFunction *lf)
{
	learning_function=lf;
}


void NeuralNet::setTraining_algorithm(TrainingAlgorithm *algo)
{
	training_algorithm=algo;
	algo->net=this;
}


void NeuralNet::registerAsBias(Neuron *neuron)
{
	biases_list.push_back(neuron);
}

void NeuralNet::turn_on_all_Bias()
{
	list<Neuron*>::iterator iter=biases_list.begin();
	while (iter!=biases_list.end())
	{
		Neuron *bias=*iter;
		bias->setFired_output(1.0);
		iter++;
	}
}

void NeuralNet::registerAsInputLayerNeuron(Neuron *neuron)
{
	input_layer->add(neuron);
}

void NeuralNet::registerAsOutputLayerNeuron(Neuron *neuron)
{
	output_layer->add(neuron);
}


void NeuralNet::registerAsHiddenLayerNeuron(Neuron *neuron,Layer *layer)
{
	layer->add(neuron);
}

Layer *NeuralNet::createHiddenLayer(void)
{
	Layer *layer=new Layer();
	hidden_layers.push_back(layer);
	return layer;
}


Neuron *NeuralNet::getNeuron(string name)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
	int i=0;
	while(iter!=this->neurons_list.end())
	{
	 Neuron *current=*iter++;
	 if (current->name==name)
		 return current;
	}
	return NULL;
}

int NeuralNet::getNeuronIndex(Neuron *neuron)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
	int i=0;
	while(iter!=this->neurons_list.end())
	{
	 if (*iter==neuron)
		 return i;
	 i++;
	 iter++;
	}
	return -1;
}

Neuron *NeuralNet::getNeuronAt(int index)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
     advance(iter, index);
    return *iter;
}



bool NeuralNet::isBias(Neuron *neuron)
{
	list<Neuron*>::iterator iter = this->biases_list.begin();
	while (iter!=biases_list.end())
	{
		if (*iter==neuron)
			return true;
		iter++;
	}
	return false;
}

Neuron *NeuralNet::getBias(Neuron *neuron)
{
	list<Sinapsis*>::iterator iter=neuron->getInputs()->begin();
	while (iter!=neuron->getInputs()->end())
	{
		Sinapsis *sinapsis=*iter;
		if (isBias(sinapsis->getStart()))
			return sinapsis->getStart();
		iter++;
	}
	return NULL;
}

Sinapsis *NeuralNet::getSinapsis(Neuron *n1,Neuron *n2)
{
	list<Sinapsis*>::iterator iter=n1->getOutputs()->begin();
	while (iter!=n1->getOutputs()->end())
	{
		Sinapsis *sinapsis=*iter++;
		if (sinapsis->getEnd()==n2)
			return sinapsis;
	}
	return NULL;
}

bool NeuralNet::save(const char *path)
{
	ofstream fout;
	fout.open(path);
	if (fout==NULL)
		return false;

	fout<<"<NEURAL_NET>"<<endl;
		fout<<"<NEURONS>"<<endl;
			size_t n=this->neurons_list.size();
			fout<<n<<endl;
		fout<<"</NEURONS>"<<endl;
		fout<<"<BIAS_LIST>"<<endl;
			list<Neuron*> biaslist=biases_list;
			list<Neuron*>::iterator biter = biaslist.begin();
			while(biter!=biaslist.end())
			{
			 fout<<"<BIAS>"<<endl;
			 fout<<getNeuronIndex(*biter)<<endl;
			 fout<<"</BIAS>"<<endl;
			 biter++;
			}
		fout<<"</BIAS_LIST>"<<endl;

		
		fout<<"<INPUT_LAYER>"<<endl;
			list<Neuron*> neuronlist=this->input_layer->getNeuron_list();
			list<Neuron*>::iterator iter = neuronlist.begin();
			while(iter!=neuronlist.end())
			{
			 fout<<"<NEURON>"<<endl;
			 fout<<getNeuronIndex(*iter)<<endl;
			 fout<<"</NEURON>"<<endl;
			 iter++;
			}
		fout<<"</INPUT_LAYER>"<<endl;
			
		fout<<"<HIDDEN_LAYERS>"<<endl;
			list<Layer*>::iterator liter = hidden_layers.begin();
			while(liter!=hidden_layers.end())
			{
			 fout<<"<HIDDEN_LAYER>"<<endl;
			 Layer *layer=*liter;
			 neuronlist=layer->getNeuron_list();
			 iter = neuronlist.begin();
			 while(iter!=neuronlist.end())
			 {
			  fout<<"<NEURON>"<<endl;
			  fout<<getNeuronIndex(*iter)<<endl;
			  fout<<"</NEURON>"<<endl;
			  iter++;
			 }
			 liter++;
			 fout<<"</HIDDEN_LAYER>"<<endl;
			}
		fout<<"</HIDDEN_LAYERS>"<<endl;

		fout<<"<OUTPUT_LAYER>"<<endl;
			neuronlist=this->output_layer->getNeuron_list();
			iter = neuronlist.begin();
			while(iter!=neuronlist.end())
			{
			 fout<<"<NEURON>"<<endl;
			 fout<<getNeuronIndex(*iter)<<endl;
			 fout<<"</NEURON>"<<endl;
			 iter++;
			}
		fout<<"</OUTPUT_LAYER>"<<endl;

		fout<<"<SINAPSIS_LIST>"<<endl;
			list<Sinapsis*> sinapsislist=this->sinapsis_list;
			list<Sinapsis*>::iterator siter = sinapsislist.begin();
			while(siter!=sinapsislist.end())
			{
			 Sinapsis *sinapsis=*siter;
			 fout<<"<SINAPSIS>"<<endl;
			 fout<<"<FROM>"<<endl;
			 fout<<getNeuronIndex(sinapsis->getStart())<<endl;
			 fout<<"</FROM>"<<endl;
			 fout<<"<TO>"<<endl;
			 fout<<getNeuronIndex(sinapsis->getEnd())<<endl;
			 fout<<"</TO>"<<endl;
			 fout<<"<WEIGHT>"<<endl;
			 fout<<sinapsis->getWeight()<<endl;
			 fout<<"</WEIGHT>"<<endl;

			 fout<<"</SINAPSIS>"<<endl;
			 siter++;
			}
		fout<<"</SINAPSIS_LIST>"<<endl;
	fout<<"</NEURAL_NET>"<<endl;
	fout.close();
	return true;
}

bool NeuralNet::load(const char *path)
{
	ifstream fin;
	fin.open(path);
	if (fin==NULL)
		return false;
	empty_contents();
	string line;
	
	fin >> line;
	/*if (line.compare("<NEURAL_NET>")==0)
	{
	 cout<<"Neural net found";
	}*/
	 
	 while (line.compare("<NEURONS>")!=0)
		{
		fin>>line;
		}
		//cout<<"<NEURONS> FOUND"<<endl;
		fin>>line;
		int n_neurons;
		istringstream ss(line);
		ss >> n_neurons;
		//cout<<"Neuronas:"<<n_neurons<<endl;
		for (int i=0;i<n_neurons;i++)
		{
		createNeuron();
		}
	 while (line.compare("</NEURONS>")!=0)
	 {
		fin>>line;
	 }

	 while (line.compare("<BIAS_LIST>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("</BIAS_LIST>")!=0)
		{
		fin>>line;
		if (line.compare("<BIAS>")==0)
		{
		 fin>>line;

		 int index_bias=0;
		 istringstream ss_bias(line);
		 ss_bias >> index_bias;
		 registerAsBias(getNeuronAt(index_bias));
		 while (line.compare("</BIAS>")==0) fin>>line;
		}
		}
	

	 while (line.compare("<INPUT_LAYER>")!=0)
		{
		fin>>line;
		}
		
	 while (line.compare("</INPUT_LAYER>")!=0)
		{
		fin>>line;
		if (line.compare("<NEURON>")==0)
		{
		 fin>>line;
		 int n_index;
		 istringstream ss_n(line);
		 ss_n >> n_index;
		 this->registerAsInputLayerNeuron(this->getNeuronAt(n_index));
		}
		}

	 while (line.compare("<HIDDEN_LAYERS>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("</HIDDEN_LAYERS>")!=0)
		{
		fin>>line;
		if (line.compare("<HIDDEN_LAYER>")==0)
		 {
		  Layer *layer=createHiddenLayer();
		  while (line.compare("</HIDDEN_LAYER>")!=0)
		  {
			fin>>line;
			if (line.compare("<NEURON>")==0)
			{
			fin>>line;
			int n_index;
			istringstream ss_n(line);
			ss_n >> n_index;
			this->registerAsHiddenLayerNeuron(this->getNeuronAt(n_index),layer);
			}
		  }
		 }
		}

	 while (line.compare("</OUTPUT_LAYER>")!=0)
		{
		fin>>line;
		if (line.compare("<NEURON>")==0)
		{
		 fin>>line;
		 int n_index;
		 istringstream ss_n(line);
		 ss_n >> n_index;
		 this->registerAsOutputLayerNeuron(this->getNeuronAt(n_index));
		}
		}

	 while (line.compare("</OUTPUT_LAYER>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("<SINAPSIS_LIST>")!=0)
		{
		fin>>line;
		}
	 while (line.compare("</SINAPSIS_LIST>")!=0)
		{
		fin>>line;
		if (line.compare("<SINAPSIS>")==0)
		{
		 int start_index,end_index;
		 double weight;
		 //cout<<"SINAPSIS FOUND";
		 while (line.compare("<FROM>")!=0)
			 fin>>line;
		 fin>>line;
		 istringstream ss(line);
		 ss >> start_index;
		 while (line.compare("<TO>")!=0)
			 fin>>line;
		 fin>>line;
		 istringstream ss2(line);
		 ss2>>end_index;
		 while (line.compare("<WEIGHT>")!=0) fin>>line;
		 fin>>line;
		 istringstream ssw(line);
		 ssw>>weight;
		 while (line.compare("</SINAPSIS>")!=0) fin>>line;
		 Neuron *start=getNeuronAt(start_index);
		 Neuron *end=getNeuronAt(end_index);
		 createSinapsis(start,end,weight);
		}
		}
	while(!fin.eof())
	{
    //cout<<line;
	fin>>line;
	}
	fin.close();
	turn_on_all_Bias();
	return true;
}

void NeuralNet::predict()
{
	//APLICAMOS LA FUNCION DE TRANSFERENCIA POR CAPAS
	
	//CAPAS OCULTAS
	list<Layer*>::iterator layer_iter= hidden_layers.begin();
	while(layer_iter!=hidden_layers.end())
	{
	 Layer *layer=*layer_iter;
	 list<Neuron*> neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator neuron_iter = neuronlist.begin();
	 while(neuron_iter!=neuronlist.end())
	 {
	  Neuron *neuron=*neuron_iter;
	  transfer_function->calculate_output(neuron);
      neuron_iter++;
	 }
	 layer_iter++;
	}

	//CAPA DE SALIDA
	list<Neuron*> neuronlist=this->output_layer->getNeuron_list();
	list<Neuron*>::iterator iter = neuronlist.begin();
	while(iter!=neuronlist.end())
	{
	 Neuron *neuron=*iter;
	 this->transfer_function->calculate_output(neuron);
     iter++;
	}

	
}

void NeuralNet::print()
{
	list<Neuron*> neuronlist=this->neurons_list;
	list<Neuron*>::iterator iter = neuronlist.begin();
	while(iter!=neuronlist.end())
	{
		Neuron *neuron=*iter;
		neuron->print();
		iter++;
	}

	list<Sinapsis*> sinapsislist=this->sinapsis_list;
	list<Sinapsis*>::iterator siter = sinapsislist.begin();
	while(siter!=sinapsislist.end())
	{
		Sinapsis *sinapsis=*siter;
		sinapsis->print();
		siter++;
	}	

}

void NeuralNet::setInput(Pattern *pattern)
{
	/*Recorremos la capa de entrada asignando valores de entrenamiento*/
		list<Neuron*> input_neuron_list=input_layer->getNeuron_list();
		list<Neuron*>::iterator input_neuron_iter=input_neuron_list.begin();
		double *pattern_data=pattern->data;
		int pattern_data_index=0;

	while(input_neuron_iter!=input_neuron_list.end())
		{
		 Neuron *Xi=*input_neuron_iter;
		 if (isBias(Xi))
		 {
			 input_neuron_iter++;
			 continue;
		 }
		 double input;

		 input=pattern_data[pattern_data_index];
 
		 Xi->setFired_output(input);
		 //cout<<Xi->name<<"="<<input;
		 input_neuron_iter++;
		 pattern_data_index++;
		}
}

Pattern *NeuralNet::getOutput(int rows,int cols)
{
	Pattern *pattern=new Pattern(rows,cols);
	list<double> results;
		// Cargamos en resultados la capa de salida de la red
		// saltandonos los bias
		list<Neuron*> output_neurons_list=output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neurons_iter=output_neurons_list.begin();

		while(output_neurons_iter!=output_neurons_list.end())
		{
			Neuron* Y=*output_neurons_iter;
			if (!isBias(Y))
			{
				//net->logger.fout<<Y->name<<"="<<Y->getFired_output()<<endl;
				//cout<<Y->name<<"="<<Y->getFired_output();
				results.push_back(Y->getFired_output());
			}
			output_neurons_iter++;
		}

	
		double *results_data=new double[results.size()];
		int i=0;
		list<double>::iterator iter=results.begin();
		while (iter!=results.end())
		{
		 results_data[i++]=(*iter);
		 iter++;
		}
		pattern->rows=rows;
		pattern->cols=cols;
		pattern->data=results_data;
		//pattern->print();
		return pattern;
}
/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "NeuralNet.h"

NeuralNet::NeuralNet(void)
{
	logger.init("c:/neural_net.log");
	this->input_layer=new Layer();
	this->output_layer=new Layer();
	
}

NeuralNet::~NeuralNet(void)
{
	//logger.log("NeuralNet destructor called\n");
	
	empty_contents();
	logger.close();
	delete input_layer;
	delete output_layer;
}

void NeuralNet::empty_contents()
{
	while(!neurons_list.empty())
	{
		delete(neurons_list.back());
		neurons_list.pop_back();
	}

	while(!sinapsis_list.empty())
	{
		delete(sinapsis_list.back());
		sinapsis_list.pop_back();
	}

	while (!input_layer->neuron_list.empty())
	{
		input_layer->neuron_list.pop_back();
	}

	while (!output_layer->neuron_list.empty())
	{
		output_layer->neuron_list.pop_back();
	}

	while (!hidden_layers.empty())
	{
		delete(hidden_layers.back());
		hidden_layers.pop_back();
	}

	while (!biases_list.empty())
	{
		biases_list.pop_back();
	}



}

Neuron* NeuralNet::createNeuron()
{
	Neuron *neuron=new Neuron();
	neurons_list.push_back(neuron);
	neuron->net=this;
	return neuron;
}

Sinapsis *NeuralNet::createSinapsis(Neuron *start,Neuron *end,double weight)
{
 Sinapsis *sinapsis=new Sinapsis();
 sinapsis->setStart(start);
 sinapsis->setEnd(end);
 sinapsis->setWeight(weight);
 sinapsis_list.push_back(sinapsis);

 start->getOutputs()->push_back(sinapsis);
 end->getInputs()->push_back(sinapsis);

 return sinapsis;
}

void NeuralNet::resetKnowledge()
{
	list<Neuron*>::iterator niter=neurons_list.begin();
	while (niter!=neurons_list.end())
	{
		Neuron *neuron=*niter++;
		neuron->commited_error=0.0;
		neuron->setFired_output(0.0);
		neuron->setReceived_input(0.0);

	}

	list<Neuron*>::iterator biter=biases_list.begin();
	while (biter!=biases_list.end())
	{
		Neuron *neuron=*biter++;
		neuron->commited_error=0.0;
		neuron->setFired_output(1.0);
	}


	list<Sinapsis*>::iterator current = this->sinapsis_list.begin();
	while (current != this->sinapsis_list.end())
	{
		Sinapsis *sinapsis=*current;
		sinapsis->setWeight(0.0);
		sinapsis->setWeight_update(0.0);
		current++;
	}
}

void NeuralNet::setTransfer_function(TransferFunction *tf)
{
	transfer_function=tf;
}

void NeuralNet::setLearning_function(LearningFunction *lf)
{
	learning_function=lf;
}


void NeuralNet::setTraining_algorithm(TrainingAlgorithm *algo)
{
	training_algorithm=algo;
	algo->net=this;
}


void NeuralNet::registerAsBias(Neuron *neuron)
{
	biases_list.push_back(neuron);
}

void NeuralNet::turn_on_all_Bias()
{
	list<Neuron*>::iterator iter=biases_list.begin();
	while (iter!=biases_list.end())
	{
		Neuron *bias=*iter;
		bias->setFired_output(1.0);
		iter++;
	}
}

void NeuralNet::registerAsInputLayerNeuron(Neuron *neuron)
{
	input_layer->add(neuron);
}

void NeuralNet::registerAsOutputLayerNeuron(Neuron *neuron)
{
	output_layer->add(neuron);
}


void NeuralNet::registerAsHiddenLayerNeuron(Neuron *neuron,Layer *layer)
{
	layer->add(neuron);
}

Layer *NeuralNet::createHiddenLayer(void)
{
	Layer *layer=new Layer();
	hidden_layers.push_back(layer);
	return layer;
}


Neuron *NeuralNet::getNeuron(string name)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
	int i=0;
	while(iter!=this->neurons_list.end())
	{
	 Neuron *current=*iter++;
	 if (current->name==name)
		 return current;
	}
	return NULL;
}

int NeuralNet::getNeuronIndex(Neuron *neuron)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
	int i=0;
	while(iter!=this->neurons_list.end())
	{
	 if (*iter==neuron)
		 return i;
	 i++;
	 iter++;
	}
	return -1;
}

Neuron *NeuralNet::getNeuronAt(int index)
{
	list<Neuron*>::iterator iter = this->neurons_list.begin();
     advance(iter, index);
    return *iter;
}



bool NeuralNet::isBias(Neuron *neuron)
{
	list<Neuron*>::iterator iter = this->biases_list.begin();
	while (iter!=biases_list.end())
	{
		if (*iter==neuron)
			return true;
		iter++;
	}
	return false;
}

Neuron *NeuralNet::getBias(Neuron *neuron)
{
	list<Sinapsis*>::iterator iter=neuron->getInputs()->begin();
	while (iter!=neuron->getInputs()->end())
	{
		Sinapsis *sinapsis=*iter;
		if (isBias(sinapsis->getStart()))
			return sinapsis->getStart();
		iter++;
	}
	return NULL;
}

Sinapsis *NeuralNet::getSinapsis(Neuron *n1,Neuron *n2)
{
	list<Sinapsis*>::iterator iter=n1->getOutputs()->begin();
	while (iter!=n1->getOutputs()->end())
	{
		Sinapsis *sinapsis=*iter++;
		if (sinapsis->getEnd()==n2)
			return sinapsis;
	}
	return NULL;
}

bool NeuralNet::save(const char *path)
{
	ofstream fout;
	fout.open(path);
	if (fout==NULL)
		return false;

	fout<<"<NEURAL_NET>"<<endl;
		fout<<"<NEURONS>"<<endl;
			size_t n=this->neurons_list.size();
			fout<<n<<endl;
		fout<<"</NEURONS>"<<endl;
		fout<<"<BIAS_LIST>"<<endl;
			list<Neuron*> biaslist=biases_list;
			list<Neuron*>::iterator biter = biaslist.begin();
			while(biter!=biaslist.end())
			{
			 fout<<"<BIAS>"<<endl;
			 fout<<getNeuronIndex(*biter)<<endl;
			 fout<<"</BIAS>"<<endl;
			 biter++;
			}
		fout<<"</BIAS_LIST>"<<endl;

		
		fout<<"<INPUT_LAYER>"<<endl;
			list<Neuron*> neuronlist=this->input_layer->getNeuron_list();
			list<Neuron*>::iterator iter = neuronlist.begin();
			while(iter!=neuronlist.end())
			{
			 fout<<"<NEURON>"<<endl;
			 fout<<getNeuronIndex(*iter)<<endl;
			 fout<<"</NEURON>"<<endl;
			 iter++;
			}
		fout<<"</INPUT_LAYER>"<<endl;
			
		fout<<"<HIDDEN_LAYERS>"<<endl;
			list<Layer*>::iterator liter = hidden_layers.begin();
			while(liter!=hidden_layers.end())
			{
			 fout<<"<HIDDEN_LAYER>"<<endl;
			 Layer *layer=*liter;
			 neuronlist=layer->getNeuron_list();
			 iter = neuronlist.begin();
			 while(iter!=neuronlist.end())
			 {
			  fout<<"<NEURON>"<<endl;
			  fout<<getNeuronIndex(*iter)<<endl;
			  fout<<"</NEURON>"<<endl;
			  iter++;
			 }
			 liter++;
			 fout<<"</HIDDEN_LAYER>"<<endl;
			}
		fout<<"</HIDDEN_LAYERS>"<<endl;

		fout<<"<OUTPUT_LAYER>"<<endl;
			neuronlist=this->output_layer->getNeuron_list();
			iter = neuronlist.begin();
			while(iter!=neuronlist.end())
			{
			 fout<<"<NEURON>"<<endl;
			 fout<<getNeuronIndex(*iter)<<endl;
			 fout<<"</NEURON>"<<endl;
			 iter++;
			}
		fout<<"</OUTPUT_LAYER>"<<endl;

		fout<<"<SINAPSIS_LIST>"<<endl;
			list<Sinapsis*> sinapsislist=this->sinapsis_list;
			list<Sinapsis*>::iterator siter = sinapsislist.begin();
			while(siter!=sinapsislist.end())
			{
			 Sinapsis *sinapsis=*siter;
			 fout<<"<SINAPSIS>"<<endl;
			 fout<<"<FROM>"<<endl;
			 fout<<getNeuronIndex(sinapsis->getStart())<<endl;
			 fout<<"</FROM>"<<endl;
			 fout<<"<TO>"<<endl;
			 fout<<getNeuronIndex(sinapsis->getEnd())<<endl;
			 fout<<"</TO>"<<endl;
			 fout<<"<WEIGHT>"<<endl;
			 fout<<sinapsis->getWeight()<<endl;
			 fout<<"</WEIGHT>"<<endl;

			 fout<<"</SINAPSIS>"<<endl;
			 siter++;
			}
		fout<<"</SINAPSIS_LIST>"<<endl;
	fout<<"</NEURAL_NET>"<<endl;
	fout.close();
	return true;
}

bool NeuralNet::load(const char *path)
{
	ifstream fin;
	fin.open(path);
	if (fin==NULL)
		return false;
	empty_contents();
	string line;
	
	fin >> line;
	/*if (line.compare("<NEURAL_NET>")==0)
	{
	 cout<<"Neural net found";
	}*/
	 
	 while (line.compare("<NEURONS>")!=0)
		{
		fin>>line;
		}
		//cout<<"<NEURONS> FOUND"<<endl;
		fin>>line;
		int n_neurons;
		istringstream ss(line);
		ss >> n_neurons;
		//cout<<"Neuronas:"<<n_neurons<<endl;
		for (int i=0;i<n_neurons;i++)
		{
		createNeuron();
		}
	 while (line.compare("</NEURONS>")!=0)
	 {
		fin>>line;
	 }

	 while (line.compare("<BIAS_LIST>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("</BIAS_LIST>")!=0)
		{
		fin>>line;
		if (line.compare("<BIAS>")==0)
		{
		 fin>>line;

		 int index_bias=0;
		 istringstream ss_bias(line);
		 ss_bias >> index_bias;
		 registerAsBias(getNeuronAt(index_bias));
		 while (line.compare("</BIAS>")==0) fin>>line;
		}
		}
	

	 while (line.compare("<INPUT_LAYER>")!=0)
		{
		fin>>line;
		}
		
	 while (line.compare("</INPUT_LAYER>")!=0)
		{
		fin>>line;
		if (line.compare("<NEURON>")==0)
		{
		 fin>>line;
		 int n_index;
		 istringstream ss_n(line);
		 ss_n >> n_index;
		 this->registerAsInputLayerNeuron(this->getNeuronAt(n_index));
		}
		}

	 while (line.compare("<HIDDEN_LAYERS>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("</HIDDEN_LAYERS>")!=0)
		{
		fin>>line;
		if (line.compare("<HIDDEN_LAYER>")==0)
		 {
		  Layer *layer=createHiddenLayer();
		  while (line.compare("</HIDDEN_LAYER>")!=0)
		  {
			fin>>line;
			if (line.compare("<NEURON>")==0)
			{
			fin>>line;
			int n_index;
			istringstream ss_n(line);
			ss_n >> n_index;
			this->registerAsHiddenLayerNeuron(this->getNeuronAt(n_index),layer);
			}
		  }
		 }
		}

	 while (line.compare("</OUTPUT_LAYER>")!=0)
		{
		fin>>line;
		if (line.compare("<NEURON>")==0)
		{
		 fin>>line;
		 int n_index;
		 istringstream ss_n(line);
		 ss_n >> n_index;
		 this->registerAsOutputLayerNeuron(this->getNeuronAt(n_index));
		}
		}

	 while (line.compare("</OUTPUT_LAYER>")!=0)
		{
		fin>>line;
		}

	 while (line.compare("<SINAPSIS_LIST>")!=0)
		{
		fin>>line;
		}
	 while (line.compare("</SINAPSIS_LIST>")!=0)
		{
		fin>>line;
		if (line.compare("<SINAPSIS>")==0)
		{
		 int start_index,end_index;
		 double weight;
		 //cout<<"SINAPSIS FOUND";
		 while (line.compare("<FROM>")!=0)
			 fin>>line;
		 fin>>line;
		 istringstream ss(line);
		 ss >> start_index;
		 while (line.compare("<TO>")!=0)
			 fin>>line;
		 fin>>line;
		 istringstream ss2(line);
		 ss2>>end_index;
		 while (line.compare("<WEIGHT>")!=0) fin>>line;
		 fin>>line;
		 istringstream ssw(line);
		 ssw>>weight;
		 while (line.compare("</SINAPSIS>")!=0) fin>>line;
		 Neuron *start=getNeuronAt(start_index);
		 Neuron *end=getNeuronAt(end_index);
		 createSinapsis(start,end,weight);
		}
		}
	while(!fin.eof())
	{
    //cout<<line;
	fin>>line;
	}
	fin.close();
	turn_on_all_Bias();
	return true;
}

void NeuralNet::predict()
{
	//APLICAMOS LA FUNCION DE TRANSFERENCIA POR CAPAS
	
	//CAPAS OCULTAS
	list<Layer*>::iterator layer_iter= hidden_layers.begin();
	while(layer_iter!=hidden_layers.end())
	{
	 Layer *layer=*layer_iter;
	 list<Neuron*> neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator neuron_iter = neuronlist.begin();
	 while(neuron_iter!=neuronlist.end())
	 {
	  Neuron *neuron=*neuron_iter;
	  transfer_function->calculate_output(neuron);
      neuron_iter++;
	 }
	 layer_iter++;
	}

	//CAPA DE SALIDA
	list<Neuron*> neuronlist=this->output_layer->getNeuron_list();
	list<Neuron*>::iterator iter = neuronlist.begin();
	while(iter!=neuronlist.end())
	{
	 Neuron *neuron=*iter;
	 this->transfer_function->calculate_output(neuron);
     iter++;
	}

	
}

void NeuralNet::print()
{
	list<Neuron*> neuronlist=this->neurons_list;
	list<Neuron*>::iterator iter = neuronlist.begin();
	while(iter!=neuronlist.end())
	{
		Neuron *neuron=*iter;
		neuron->print();
		iter++;
	}

	list<Sinapsis*> sinapsislist=this->sinapsis_list;
	list<Sinapsis*>::iterator siter = sinapsislist.begin();
	while(siter!=sinapsislist.end())
	{
		Sinapsis *sinapsis=*siter;
		sinapsis->print();
		siter++;
	}	

}

void NeuralNet::setInput(Pattern *pattern)
{
	/*Recorremos la capa de entrada asignando valores de entrenamiento*/
		list<Neuron*> input_neuron_list=input_layer->getNeuron_list();
		list<Neuron*>::iterator input_neuron_iter=input_neuron_list.begin();
		double *pattern_data=pattern->data;
		int pattern_data_index=0;

	while(input_neuron_iter!=input_neuron_list.end())
		{
		 Neuron *Xi=*input_neuron_iter;
		 if (isBias(Xi))
		 {
			 input_neuron_iter++;
			 continue;
		 }
		 double input;

		 input=pattern_data[pattern_data_index];
 
		 Xi->setFired_output(input);
		 //cout<<Xi->name<<"="<<input;
		 input_neuron_iter++;
		 pattern_data_index++;
		}
}

Pattern *NeuralNet::getOutput(int rows,int cols)
{
	Pattern *pattern=new Pattern(rows,cols);
	list<double> results;
		// Cargamos en resultados la capa de salida de la red
		// saltandonos los bias
		list<Neuron*> output_neurons_list=output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neurons_iter=output_neurons_list.begin();

		while(output_neurons_iter!=output_neurons_list.end())
		{
			Neuron* Y=*output_neurons_iter;
			if (!isBias(Y))
			{
				//net->logger.fout<<Y->name<<"="<<Y->getFired_output()<<endl;
				//cout<<Y->name<<"="<<Y->getFired_output();
				results.push_back(Y->getFired_output());
			}
			output_neurons_iter++;
		}

	
		double *results_data=new double[results.size()];
		int i=0;
		list<double>::iterator iter=results.begin();
		while (iter!=results.end())
		{
		 results_data[i++]=(*iter);
		 iter++;
		}
		pattern->rows=rows;
		pattern->cols=cols;
		pattern->data=results_data;
		//pattern->print();
		return pattern;
}
