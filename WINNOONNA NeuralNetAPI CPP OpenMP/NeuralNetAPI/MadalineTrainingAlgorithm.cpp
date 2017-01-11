/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "MadalineTrainingAlgorithm.h"
#include <cmath>

MadalineTrainingAlgorithm::MadalineTrainingAlgorithm(void)
{
}

MadalineTrainingAlgorithm::~MadalineTrainingAlgorithm(void)
{
}


MadalineTrainingAlgorithm::MadalineTrainingAlgorithm(NeuralNet*the_net)
{
	max_epochs=10000;
	this->net=the_net;
}


bool MadalineTrainingAlgorithm::stop_condition()
{
	// Si no se han actualizado pesos entonces
	// se ha alcanzado la condicion de finalizacion
	// de entrenamiento.
	return weights_updated==false;
}

void MadalineTrainingAlgorithm::configurar_capa_entrada_como_puerta_or(void)
{
	list<Neuron*> outputneuronlist=net->output_layer->getNeuron_list();
	list<Neuron*>::iterator outputneuroniter = outputneuronlist.begin();
	while(outputneuroniter!=outputneuronlist.end())
	{
		Neuron *neuron=*outputneuroniter;
		if (!this->net->isBias(neuron))
		{
		 list<Sinapsis*> *sinapsis_list= neuron->getInputs();
		 size_t howmany=sinapsis_list->size()-1;
		 list<Sinapsis*>::iterator sinapsisiter=sinapsis_list->begin();
		 while(sinapsisiter!=sinapsis_list->end())
		 {
			Sinapsis *sinapsis=*sinapsisiter;
			sinapsis->setWeight(1.0/(double)howmany);
			sinapsisiter++;
		 }
		}
		outputneuroniter++;
	}
}

void MadalineTrainingAlgorithm::loggear_pesos()
{
	list<Layer*>::iterator layer_iter= this->net->hidden_layers.begin();
	while (layer_iter!=this->net->hidden_layers.end())
	{  
		list<Neuron*> neuron_list=(*layer_iter)->getNeuron_list();
		list<Neuron*>::iterator neuron_iter=neuron_list.begin();
		while (neuron_iter!=neuron_list.end())
		{
			loggear_pesos(*neuron_iter);
			neuron_iter++;
		}
	 layer_iter++;
	}
	
	//this->net->logger.fout<<endl;
}


void MadalineTrainingAlgorithm::loggear_pesos(Neuron *neuron)
{
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current;
		//this->net->logger.fout<<"["<<sinapsis->getWeight()<<"]";
		current++;
	 }
}


void MadalineTrainingAlgorithm::fill_weights_with_little_random_values()
{
 net->resetKnowledge();

 list<Sinapsis*>::iterator sinapsis_iter=net->sinapsis_list.begin();

 while(sinapsis_iter!=net->sinapsis_list.end())
 {
	 double random=rand()/10000.00;
	 Sinapsis *sinapsis=*sinapsis_iter;
	 sinapsis->setWeight(random);
	 sinapsis_iter++;
 }
}


void MadalineTrainingAlgorithm::train(void)
{
	int contador_epocas=1;
	weights_updated=false;
	//Inicializar todos los pesos a valores aleatorios 
	fill_weights_with_little_random_values();
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	//net->resetKnowledge();

	// AJUSTAMOS LOS PESOS DE LA CAPA DE SALIDA DE MANERA QUE IMPLEMENTEN PUERTAS OR
	configurar_capa_entrada_como_puerta_or();
	/**/
	
	net->logger.fout<<"RED DE PARTIDA"<<endl;
	net->print();
	net->logger.fout<<"COMENZANDO ENTRENAMIENTO"<<endl;

	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
	do
	{
	 //this->net->logger.fout<<"\nEPOCA:"<<contador_epocas<<"\n";;
	 net->logger.fout<<"\nEPOCA:"<<contador_epocas<<"\n";
	 net->logger.fout<<"Estado red"<<endl;
	 net->print();
	 if (contador_epocas>max_epochs)
	 { net->logger.fout<<"No se consiguio el objetivo\n"; break;}
	 contador_epocas++;
	 weights_updated=false;

	 //Aplicar cada vector de entrenamiento 
	 list<list<double>>::iterator training_pattern_iter = training_patterns.begin();
	 list<list<double>>::iterator training_targets_list_iter = target_patterns.begin();

	 
	 while (training_pattern_iter != training_patterns.end())
	 {
	  //this->net->logger<<"\nAplicando vector de entrenamiento:";
	  list<double>input_values_list=*training_pattern_iter;
	  // ESTABLECER LAS ACTIVACIONES A LAS NEURONAS DE ENTRADA
	  //Aplicamos cada valor del vector de entrenamiento a cada neurona de entrada
	  list<double>::iterator input_value_iter = input_values_list.begin();
	  list<Neuron*> neuronlist=net->input_layer->getNeuron_list();
	  list<Neuron*>::iterator input_neuron_iter = neuronlist.begin();
  	  
	  net->logger.fout<<"INPUTS:"<<endl;
	  while (input_value_iter!=input_values_list.end())
	  {
	    double fired_value=*input_value_iter;
		//this->net->logger.fout<<"["<<fired_value<<"]";
		//Aplicamos ese valor en las neuronas de entrada
		Neuron *neuron=*input_neuron_iter;
		neuron->setFired_output(fired_value);
		net->logger.fout<<"INPUT:"<<neuron->name<<"="<<fired_value<<endl;
		
		input_value_iter++;
		input_neuron_iter++;
	  }

	 // PROPAGAR LAS ENTRADAS A CADA UNA DE LAS CAPAS OCULTAS
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE LAS CAPAS OCULTAS
	  list<Layer*>::iterator hidden_layer_iter=net->hidden_layers.begin();
	  while(hidden_layer_iter!=net->hidden_layers.end())
	  {
		  Layer *layer=*hidden_layer_iter;
		  //Recorremos todas las neuronas de la capa aplicando la funcion
		  //de transferencia
		  neuronlist=layer->getNeuron_list();
		  list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		  net->logger.fout<<"||HIDEN_LAYER NEURONS:"<<endl;
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			if (!net->isBias(neuron))
			{
				net->transfer_function->calculate_output(neuron);
				//net->logger.fout<<"yin["<<neuron->getReceived_input()<<"]";
				//net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]";
			}
			hidden_neuron_iter++;
		  }
		  //this->net->logger.fout<<endl;
		  hidden_layer_iter++;
	  }
	  
	  // Calculamos la salida de la red:

	  /***/
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA

	  //this->net->logger.fout<<"||OUTPUTS:";
	  list<Neuron*> outputneuronlist=net->output_layer->getNeuron_list();
	  list<Neuron*>::iterator output_neuron_iter = outputneuronlist.begin();
	  

	  //double target=-111;
	  while (output_neuron_iter!=outputneuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		if (!net->isBias(neuron))
		{
			net->transfer_function->calculate_output(neuron);
			//net->logger.fout<<"y_in["<<neuron->getReceived_input()<<"]";
			//net->logger.fout<<"f["<<neuron->getFired_output()<<"]";		
    		//target=*current_target_values_iterator;
			//net->logger.fout<<"Red responde:"<<neuron->getFired_output()<<endl;
			//net->logger.fout<<"Target es "<<target<<endl;
			//current_target_values_iterator++;
		}
		output_neuron_iter++;
	  }
	
	  
	  net->logger.fout<<"carga de entradas y respuesta de la red"<<endl;
	  net->print();



        //AJUSTAR PESOS Y SESGOS (Aplicar funcion de aprendizaje a las
		//neuronas de las CAPAS OCULTAS
		
		//controlamos el cambio de pesos
		MadalineLearningFunction *Madalinelearning_function=(MadalineLearningFunction*)(net->learning_function);
		Madalinelearning_function->setWeights_have_changed(false);

	  outputneuronlist=net->output_layer->getNeuron_list();
	  output_neuron_iter = outputneuronlist.begin();

	  list<double>::iterator current_target_values_iterator=(*training_targets_list_iter).begin();
	  
	  while (output_neuron_iter!=outputneuronlist.end())
	  {
	    Neuron *neuron=*output_neuron_iter; 	

		if (net->isBias(neuron))
		{
			output_neuron_iter++;
			continue;
		}

		double target=*current_target_values_iterator;

		net->logger.fout<<"Output "<<neuron->name<<" es "<<neuron->getFired_output()<<endl;
		net->logger.fout<<"Target es "<<target<<endl;


		// Si el disparo es el esperado, no cambies pesos
		if (target==neuron->getFired_output())
		{
		  //do nothing
			net->logger.fout<<"Target "<<target<<" obtenido, no se actualizan pesos"<<endl;
		} else
		if (target==-1)
		{
			net->logger.fout<<"Target "<<target<<" es -1 aplicamos delta a entradas positivas"<<endl;
		 // Si el target es -1 se aplica la regla delta a todas las 
		 // neuronas de las capas ocultas que tengan entradas positivas
			list<Layer*>::iterator hidden_layer_update_iter=net->hidden_layers.begin();
			Layer *layer_to_update=*hidden_layer_update_iter;
			while(hidden_layer_update_iter!=net->hidden_layers.end())
			{
				list<Neuron*> neurons_to_update=layer_to_update->getNeuron_list();
				list<Neuron*>::iterator neurons_to_update_iter=neurons_to_update.begin();
				while(neurons_to_update_iter!=neurons_to_update.end())
				 {
					Neuron *neuron_to_update=*neurons_to_update_iter;
					//solo las de entrada positiva
					// que no sea un bias!
					if (!net->isBias(neuron_to_update))
					 if (neuron_to_update->getReceived_input()>0)
						Madalinelearning_function->update_weights(neuron_to_update,target);
					neurons_to_update_iter++;
				 }
				hidden_layer_update_iter++;
			}			
		} else if (target=1)
		{
			// Si el target es 1 se aplica la regla delta a la neurona
			// de las capas oculta que tenga la entrada neta (y_in) mas proxima a cero
			net->logger.fout<<"target "<<target<<" es 1, aplicamos delta a la neurona de entrada mas cercana a cero"<<endl;
			list<Layer*>::iterator hidden_layer_update_iter=net->hidden_layers.begin();
			Layer *layer_to_update=*hidden_layer_update_iter;
			while(hidden_layer_update_iter!=net->hidden_layers.end())
			{
				list<Neuron*> neurons=layer_to_update->getNeuron_list();
				list<Neuron*>::iterator neurons_iter=neurons.begin();
				double min_input=fabs((*neurons_iter)->getReceived_input());
				Neuron *min_input_neuron=NULL;
				while(neurons_iter!=neurons.end())
				{
				//que no sea un bias!!
					if (!net->isBias((*neurons_iter)))
					{
					double zinput=fabs((*neurons_iter)->getReceived_input());
					if ((zinput<min_input)||(min_input_neuron==NULL))
						min_input_neuron=*neurons_iter;
					}
					neurons_iter++;
				}
				net->logger.fout<<"indice de la neurona con menor entrada:"<<net->getNeuronIndex(min_input_neuron)<<endl;
				net->logger.fout<<"nombre de la neurona con menor entrada:"<<min_input_neuron->name<<endl;
				Madalinelearning_function->update_weights(min_input_neuron,target);
				hidden_layer_update_iter++;
			}
		} //ENDELSEIF 
			
		//Observa si los pesos han cambiado
		if (Madalinelearning_function->getWeights_have_changed())
		{
		 weights_updated=true;
		 //this->net->logger.fout<<"||UPDATED"<<endl;
		 }
		output_neuron_iter++;
		current_target_values_iterator++;
	  }
	  loggear_pesos();

	  net->logger.fout<<"Resultados actualizar pesos"<<endl;
	  net->print();
	  // Siguiente patrón
	  training_pattern_iter++;
	  training_targets_list_iter++;
	  //this->net->logger.fout<<"\n";
	 }
	}while(stop_condition()==false);

 return;
}