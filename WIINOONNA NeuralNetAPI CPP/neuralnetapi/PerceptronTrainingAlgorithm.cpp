/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "PerceptronTrainingAlgorithm.h"

PerceptronTrainingAlgorithm::PerceptronTrainingAlgorithm(void)
{
}

PerceptronTrainingAlgorithm::~PerceptronTrainingAlgorithm(void)
{
}

PerceptronTrainingAlgorithm::PerceptronTrainingAlgorithm(NeuralNet *the_net)
{
	this->net=the_net;
}


bool PerceptronTrainingAlgorithm::stop_condition()
{
	// Si no se han actualizado pesos entonces
	// se ha alcanzado la condicion de finalizacion
	// de entrenamiento.
	return weights_updated==false;
}

void PerceptronTrainingAlgorithm::train(void)
{
    PerceptronLearningFunction *perceptronlearning_function=(PerceptronLearningFunction*)(net->learning_function);
	int contador_epocas=1;
	//Inicializar todos los pesos
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	net->resetKnowledge();
     
	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
	this->net->logger.fout<<"PERCEPTRON TRAINING START:"<<endl;
	this->net->print();
	do
	{
	 this->net->logger.fout<<"\nEPOCA:"<<contador_epocas<<"\n";
     perceptronlearning_function->setWeights_have_changed(false);
   	 weights_updated=false;

	 if (contador_epocas==max_epochs)
	 {
	  this->net->logger.fout<<"No se consiguio el objetivo\n";
	  break;
	 }
	 contador_epocas++;
	 
	 //Aplicar cada vector de entrenamiento:
	 list<Pattern*>::iterator training_patterns_iter = training_patterns.patterns_list.begin();
	 list<Pattern*>::iterator target_patterns_iter =  target_patterns.patterns_list.begin();

	 while (training_patterns_iter != training_patterns.patterns_list.end())
	 {
	  Pattern *training_pattern=(*training_patterns_iter);

	  

	  // ESTABLECER LAS ACTIVACIONES A LAS NEURONAS DE ENTRADA
	  //Aplicamos cada valor del vector de entrenamiento a cada neurona de entrada
	  	int training_pattern_data_size=training_pattern->rows*training_pattern->cols;
		int training_pattern_data_index=0;
		list<Neuron*> neuronlist=net->input_layer->getNeuron_list();
		list<Neuron*>::iterator input_neuron_iter = neuronlist.begin();
	  net->logger.fout<<"\nAplicando vector de entrenamiento:"<<endl;
	  while(training_pattern_data_index<training_pattern_data_size)
	  {
		//Aplicamos ese valor en las neuronas de entrada
		Neuron *neuron=*input_neuron_iter;
		if (net->isBias(neuron))
		{
		 input_neuron_iter++;
		 continue;
		}
		
		double fired_value=training_pattern->data[training_pattern_data_index];
		neuron->setFired_output(fired_value);

		net->logger.fout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;
		training_pattern_data_index++;
		input_neuron_iter++;
	  }
	 
	  
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA
		neuronlist=net->output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();

	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		net->transfer_function->calculate_output(neuron);

		net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;

		output_neuron_iter++;
	  }

	  //AJUSTAR PESOS Y SESGOS (Aplicar funcion de aprendizaje a las
	  //neuronas de salida
  	  //actualizo recorriendo todas las neuronas de salida
	  //comparandolas con sus targets, actualizo las que no
	  //aciertan.
		Pattern *target_pattern=(*target_patterns_iter);
		int target_pattern_data_size=target_pattern->rows*training_pattern->cols;
		int target_pattern_data_index=0;
		neuronlist=net->output_layer->getNeuron_list();
		output_neuron_iter = neuronlist.begin();
	  
		net->logger.fout<<"\nComparandolo con vector target:"<<endl;
		
	  while (output_neuron_iter!=neuronlist.end())
	  {
	     Neuron *neuron=*output_neuron_iter;
		 double target=target_pattern->data[target_pattern_data_index];
		 
		 net->logger.fout<<"F:"<<neuron->getFired_output()<<"= TARGET:"<<target<<"?"<<endl;
		 if (neuron->getFired_output()!=target)
			perceptronlearning_function->update_weights(neuron,target);
		//Observa si los pesos han cambiado
		 if (perceptronlearning_function->getWeights_have_changed())
		 {
		  net->logger.fout<<"Weights updated"<<endl;
		  weights_updated=true;
		 }
		 target_pattern_data_index++;
		 output_neuron_iter++;
	  }

	  this->net->logger.fout<<"Siguiente Patron"<<endl;
	  this->net->print();
	  // Siguiente patrón
	  training_patterns_iter++;
	  target_patterns_iter++;
	 }
	}while(stop_condition()==false);

	this->net->logger.fout<<"PERCEPTRON TRAINED:"<<endl;
	this->net->print();
	this->net->logger.fout<<"*********************"<<endl;
 return;
}/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "PerceptronTrainingAlgorithm.h"

PerceptronTrainingAlgorithm::PerceptronTrainingAlgorithm(void)
{
}

PerceptronTrainingAlgorithm::~PerceptronTrainingAlgorithm(void)
{
}

PerceptronTrainingAlgorithm::PerceptronTrainingAlgorithm(NeuralNet *the_net)
{
	this->net=the_net;
}


bool PerceptronTrainingAlgorithm::stop_condition()
{
	// Si no se han actualizado pesos entonces
	// se ha alcanzado la condicion de finalizacion
	// de entrenamiento.
	return weights_updated==false;
}

void PerceptronTrainingAlgorithm::train(void)
{
    PerceptronLearningFunction *perceptronlearning_function=(PerceptronLearningFunction*)(net->learning_function);
	int contador_epocas=1;
	//Inicializar todos los pesos
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	net->resetKnowledge();
     
	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
	this->net->logger.fout<<"PERCEPTRON TRAINING START:"<<endl;
	this->net->print();
	do
	{
	 this->net->logger.fout<<"\nEPOCA:"<<contador_epocas<<"\n";
     perceptronlearning_function->setWeights_have_changed(false);
   	 weights_updated=false;

	 if (contador_epocas==max_epochs)
	 {
	  this->net->logger.fout<<"No se consiguio el objetivo\n";
	  break;
	 }
	 contador_epocas++;
	 
	 //Aplicar cada vector de entrenamiento:
	 list<Pattern*>::iterator training_patterns_iter = training_patterns.patterns_list.begin();
	 list<Pattern*>::iterator target_patterns_iter =  target_patterns.patterns_list.begin();

	 while (training_patterns_iter != training_patterns.patterns_list.end())
	 {
	  Pattern *training_pattern=(*training_patterns_iter);

	  

	  // ESTABLECER LAS ACTIVACIONES A LAS NEURONAS DE ENTRADA
	  //Aplicamos cada valor del vector de entrenamiento a cada neurona de entrada
	  	int training_pattern_data_size=training_pattern->rows*training_pattern->cols;
		int training_pattern_data_index=0;
		list<Neuron*> neuronlist=net->input_layer->getNeuron_list();
		list<Neuron*>::iterator input_neuron_iter = neuronlist.begin();
	  net->logger.fout<<"\nAplicando vector de entrenamiento:"<<endl;
	  while(training_pattern_data_index<training_pattern_data_size)
	  {
		//Aplicamos ese valor en las neuronas de entrada
		Neuron *neuron=*input_neuron_iter;
		if (net->isBias(neuron))
		{
		 input_neuron_iter++;
		 continue;
		}
		
		double fired_value=training_pattern->data[training_pattern_data_index];
		neuron->setFired_output(fired_value);

		net->logger.fout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;
		training_pattern_data_index++;
		input_neuron_iter++;
	  }
	 
	  
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA
		neuronlist=net->output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();

	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		net->transfer_function->calculate_output(neuron);

		net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;

		output_neuron_iter++;
	  }

	  //AJUSTAR PESOS Y SESGOS (Aplicar funcion de aprendizaje a las
	  //neuronas de salida
  	  //actualizo recorriendo todas las neuronas de salida
	  //comparandolas con sus targets, actualizo las que no
	  //aciertan.
		Pattern *target_pattern=(*target_patterns_iter);
		int target_pattern_data_size=target_pattern->rows*training_pattern->cols;
		int target_pattern_data_index=0;
		neuronlist=net->output_layer->getNeuron_list();
		output_neuron_iter = neuronlist.begin();
	  
		net->logger.fout<<"\nComparandolo con vector target:"<<endl;
		
	  while (output_neuron_iter!=neuronlist.end())
	  {
	     Neuron *neuron=*output_neuron_iter;
		 double target=target_pattern->data[target_pattern_data_index];
		 
		 net->logger.fout<<"F:"<<neuron->getFired_output()<<"= TARGET:"<<target<<"?"<<endl;
		 if (neuron->getFired_output()!=target)
			perceptronlearning_function->update_weights(neuron,target);
		//Observa si los pesos han cambiado
		 if (perceptronlearning_function->getWeights_have_changed())
		 {
		  net->logger.fout<<"Weights updated"<<endl;
		  weights_updated=true;
		 }
		 target_pattern_data_index++;
		 output_neuron_iter++;
	  }

	  this->net->logger.fout<<"Siguiente Patron"<<endl;
	  this->net->print();
	  // Siguiente patrón
	  training_patterns_iter++;
	  target_patterns_iter++;
	 }
	}while(stop_condition()==false);

	this->net->logger.fout<<"PERCEPTRON TRAINED:"<<endl;
	this->net->print();
	this->net->logger.fout<<"*********************"<<endl;
 return;
}