/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "BackPropagationTrainingAlgorithm.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

BackPropagationTrainingAlgorithm::BackPropagationTrainingAlgorithm(void)
{
	max_epochs=5000;
	current_epoch=0;
	init_weights_to_random_values=true;
    srand((unsigned int)time(0));  // Initialize random number generator.
	objective_min_cuadratic_error=0.05;

}

BackPropagationTrainingAlgorithm::~BackPropagationTrainingAlgorithm(void)
{
}

BackPropagationTrainingAlgorithm::BackPropagationTrainingAlgorithm(NeuralNet *the_net)
{
	this->net=the_net;
	max_epochs=5000;
	current_epoch=0;
	init_weights_to_random_values=true;
	srand((unsigned int)time(0));  // Initialize random number generator.
	objective_min_cuadratic_error=0.05;
}



bool BackPropagationTrainingAlgorithm::stop_condition()
{
 if ( current_epoch>max_epochs)
 {
	 net->logger.fout<<"STOP CONDITION: MAX_EPOCHS"<<endl;
	 cout<<"STOP CONDITION: MAX_EPOCHS"<<endl;
	 return true;
 }

 //cout<<"objective min error"<<objective_min_cuadratic_error<<endl;
 if (median_cuadratic_error_in_this_epoch<=objective_min_cuadratic_error)
 {
	 net->logger.fout<<"STOP CONDITION: MIN_CUADRATIC_ERROR_REACHED"<<endl;
	 cout<<"STOP CONDITION: MIN_CUADRATIC_ERROR_REACHED"<<endl;
	 return true;
 }
 return false;
}


void BackPropagationTrainingAlgorithm::fill_weights_with_little_random_values()
{
 
 list<Sinapsis*>::iterator sinapsis_iter=net->sinapsis_list.begin();

 while(sinapsis_iter!=net->sinapsis_list.end())
 {
	double random = generate_random(-0.5,0.5);

	//((double)rand() / ((double)RAND_MAX));
	//random-=0.5;
	 
	 Sinapsis *sinapsis=*sinapsis_iter;
	 sinapsis->setWeight(random);
	 sinapsis_iter++;
 }
}

void BackPropagationTrainingAlgorithm::NW_weights_initialization()
{
	// Recorremos todas las sinapsis de entrada de las neuronas de las capas ocultas
	// se supone que todos sus pesos ya han sido inicializados a valores
	// random en el rando -0.5 a 0.5
	double n=0.0; // numero de neuronas de entrada
	double p=0.0; // numero de neuronas en la capa oculta
	

	n=this->net->input_layer->getNeuron_list().size();
	
	list<Neuron*> neuronlist=net->input_layer->getNeuron_list();
	list<Layer*>::iterator hidden_layer_iter=net->hidden_layers.begin();
	while(hidden_layer_iter!=net->hidden_layers.end())
	{
	 Layer *layer=*hidden_layer_iter++;
	 //Recorremos todas las neuronas de la capa 
	 neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
	 while (hidden_neuron_iter!=neuronlist.end())
	 {
			Neuron *neuron=*hidden_neuron_iter++;
			if (!net->isBias(neuron))
			{
				p++;
			}
	  }		 
	}

	double beta=0.7*pow(p,1/n);
	hidden_layer_iter=net->hidden_layers.begin();
	while(hidden_layer_iter!=net->hidden_layers.end())
	{
	 Layer *layer=*hidden_layer_iter++;
	 //Recorremos todas las neuronas de la capa 
	 neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
	 while (hidden_neuron_iter!=neuronlist.end())
	 {
			Neuron *neuron=*hidden_neuron_iter++;
			if (!net->isBias(neuron))
			{
				list<Sinapsis*>::iterator hidden_sinapsis_iter;
				hidden_sinapsis_iter=neuron->getInputs()->begin();
     		    double modulus=0.0;
				while (hidden_sinapsis_iter!=neuron->getInputs()->end())
				{
					Sinapsis *sinapsis=*hidden_sinapsis_iter++;
					modulus+=sinapsis->getWeight()*sinapsis->getWeight();
				}
				modulus=sqrt(modulus);
				hidden_sinapsis_iter=neuron->getInputs()->begin();
     		   	while (hidden_sinapsis_iter!=neuron->getInputs()->end())
				{
					Sinapsis *sinapsis=*hidden_sinapsis_iter++;
					if (!net->isBias(sinapsis->getStart()))
					{
					 sinapsis->setWeight((beta*sinapsis->getWeight())/modulus);
					} else // es un bias
					{
						sinapsis->setWeight(generate_random(-beta,beta));
					}

				}

			}
	 }		 
	}

}


void BackPropagationTrainingAlgorithm::train(void)
{
    BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);

	
	current_epoch=1;
	//Inicializar todos los pesos
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	if (init_weights_to_random_values==true)
	{
		net->resetKnowledge();
		srand((unsigned int)time(0)); 
		fill_weights_with_little_random_values();
		NW_weights_initialization();
	}

	 
	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
	this->net->logger.fout<<"BackPropagation TRAINING START:"<<endl;
	this->net->print();
	do
	{
	 this->net->logger.fout<<"\nEPOCA:"<<current_epoch<<"\n";
	 //cout<<"\nEPOCA:"<<current_epoch<<endl;

     current_epoch++;
	 median_cuadratic_error_in_this_epoch=0.0;
	 
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
	  //cout<<"\nAplicando vector de entrenamiento:"<<endl;
	  //training_pattern->print();
	  //cout<<endl;
	  while(training_pattern_data_index<training_pattern_data_size)
	  {
		//Aplicamos ese valor en las neuronas de entrada
		Neuron *neuron=*input_neuron_iter;
		if (!net->isBias(neuron))
		{
		 double fired_value=training_pattern->data[training_pattern_data_index];
		 neuron->setFired_output(fired_value);

		 net->logger.fout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;
		 training_pattern_data_index++;
		}
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
		  net->logger.fout<<"||HIDDEN_LAYER NEURONS:"<<endl;
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			if (!net->isBias(neuron))
			{
				net->transfer_function->calculate_output(neuron);
				net->logger.fout<<neuron->name<<": zin["<<neuron->getReceived_input()<<"] ";
				net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]"<<endl;
			}
			hidden_neuron_iter++;
		  }
		  
		  hidden_layer_iter++;
	  }

	  
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA
		neuronlist=net->output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();
	  net->logger.fout<<"||OUTPUT_LAYER NEURONS:"<<endl;
	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		
		if (!net->isBias(neuron))
		{
		 ((BackPropagation*)net)->transfer_function->calculate_output(neuron);
		  net->logger.fout<<neuron->name<<": yin["<<neuron->getReceived_input()<<"] ";
		  net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]"<<endl;
		  //net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;
		}
		output_neuron_iter++;
	  }


	  /**************************
	   RETROPROPAGACION DEL ERROR
	  ***************************/
	   /* Recorremos la capa de salida calculando los deltas de error y 
	   acumulandolos en la neurona */
	    Pattern *target_pattern=(*target_patterns_iter);
		int target_pattern_data_size=target_pattern->rows*training_pattern->cols;
		int target_pattern_data_index=0;
		neuronlist=net->output_layer->getNeuron_list();
		output_neuron_iter = neuronlist.begin();
	  
	  net->logger.fout<<"\nBACKPROPAGATION:"<<endl;
		
	  while (output_neuron_iter!=neuronlist.end())
	  {
	    Neuron *neuron=*output_neuron_iter;
		if (!net->isBias(neuron))
		{
		 double target=target_pattern->data[target_pattern_data_index];
		 
		 net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
		 net->logger.fout<<" target:"<<target<<endl;
		 //cout<<" target:"<<target<<endl;

		 // E=1/2*sum([tk-yk]^2)
		 //median_cuadratic_error_in_this_epoch+=pow(target-neuron->getFired_output(),2.0);
		 median_cuadratic_error_in_this_epoch+=(target-neuron->getFired_output())*(target-neuron->getFired_output());
 
		 BackPropagationlearning_function->calculate_error_delta(neuron,target);
		 BackPropagationlearning_function->calculate_weight_updates(neuron);	 
		 target_pattern_data_index++; 
		}
		
		output_neuron_iter++;
	  }

	  /* Retropropagacion en las capas ocultas desde la ultima a la primera*/
	  list<Layer*>::reverse_iterator hidden_layer_reverse_iter=net->hidden_layers.rbegin();
	  hidden_layer_iter=net->hidden_layers.end();
	  while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
	  {
		  Layer *layer=*hidden_layer_reverse_iter++;
		  neuronlist=layer->getNeuron_list();
		  list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		  //net->logger.fout<<"||HIDEN_LAYER NEURONS:"<<endl;
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			if (!net->isBias(neuron))
			{
			 BackPropagationlearning_function->calculate_error_delta(neuron);;
			 BackPropagationlearning_function->calculate_weight_updates(neuron);	
			}

			hidden_neuron_iter++;
		  }
		 // this->net->logger.fout<<endl;
	  }


	  /** ACTUALIZACION DE PESOS **/
	  /* Actualizacion pesos capa de salida */
	  neuronlist=net->output_layer->getNeuron_list();
	  output_neuron_iter = neuronlist.begin();	
	  while (output_neuron_iter!=neuronlist.end())
	  {
	     Neuron *neuron=*output_neuron_iter;
		 
		 BackPropagationlearning_function->update_weight(neuron);	 

		 output_neuron_iter++;
	  }
	  /* Actualizacion pesos de las capas ocultas */
	  hidden_layer_reverse_iter=net->hidden_layers.rbegin();
	  while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
	  {
		  Layer *layer=*hidden_layer_reverse_iter++;
		  neuronlist=layer->getNeuron_list();
		  list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			
			BackPropagationlearning_function->update_weight(neuron);	


			hidden_neuron_iter++;
		  }
		 // this->net->logger.fout<<endl;
	  }



	  //this->net->logger.fout<<endl<<"ESTADO DE LA RED:"<<endl;
	  //this->net->print();
	  // Siguiente patrón
	  //this->net->logger.fout<<"Siguiente Patron"<<endl;
	  training_patterns_iter++;
	  target_patterns_iter++;
	 }
	 // E=1/2*sum([tk-yk]^2), el sumatorio fue hecho durante el bucle
	 median_cuadratic_error_in_this_epoch*=0.5;

	 if (current_epoch%100==0)
	 {
		 cout<<"\nEPOCH:"<<current_epoch<<":";
	  this->net->logger.fout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
	  cout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
	 }
	}while(stop_condition()==false);

	this->net->logger.fout<<"*********************"<<endl;
	this->net->logger.fout<<"BackPropagation training finished."<<endl;
	//this->net->print();
	
 return;
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

#include "BackPropagationTrainingAlgorithm.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

BackPropagationTrainingAlgorithm::BackPropagationTrainingAlgorithm(void)
{
	max_epochs=5000;
	current_epoch=0;
	init_weights_to_random_values=true;
    srand((unsigned int)time(0));  // Initialize random number generator.
	objective_min_cuadratic_error=0.05;

}

BackPropagationTrainingAlgorithm::~BackPropagationTrainingAlgorithm(void)
{
}

BackPropagationTrainingAlgorithm::BackPropagationTrainingAlgorithm(NeuralNet *the_net)
{
	this->net=the_net;
	max_epochs=5000;
	current_epoch=0;
	init_weights_to_random_values=true;
	srand((unsigned int)time(0));  // Initialize random number generator.
	objective_min_cuadratic_error=0.05;
}



bool BackPropagationTrainingAlgorithm::stop_condition()
{
 if ( current_epoch>max_epochs)
 {
	 net->logger.fout<<"STOP CONDITION: MAX_EPOCHS"<<endl;
	 cout<<"STOP CONDITION: MAX_EPOCHS"<<endl;
	 return true;
 }

 //cout<<"objective min error"<<objective_min_cuadratic_error<<endl;
 if (median_cuadratic_error_in_this_epoch<=objective_min_cuadratic_error)
 {
	 net->logger.fout<<"STOP CONDITION: MIN_CUADRATIC_ERROR_REACHED"<<endl;
	 cout<<"STOP CONDITION: MIN_CUADRATIC_ERROR_REACHED"<<endl;
	 return true;
 }
 return false;
}


void BackPropagationTrainingAlgorithm::fill_weights_with_little_random_values()
{
 
 list<Sinapsis*>::iterator sinapsis_iter=net->sinapsis_list.begin();

 while(sinapsis_iter!=net->sinapsis_list.end())
 {
	double random = generate_random(-0.5,0.5);

	//((double)rand() / ((double)RAND_MAX));
	//random-=0.5;
	 
	 Sinapsis *sinapsis=*sinapsis_iter;
	 sinapsis->setWeight(random);
	 sinapsis_iter++;
 }
}

void BackPropagationTrainingAlgorithm::NW_weights_initialization()
{
	// Recorremos todas las sinapsis de entrada de las neuronas de las capas ocultas
	// se supone que todos sus pesos ya han sido inicializados a valores
	// random en el rando -0.5 a 0.5
	double n=0.0; // numero de neuronas de entrada
	double p=0.0; // numero de neuronas en la capa oculta
	

	n=this->net->input_layer->getNeuron_list().size();
	
	list<Neuron*> neuronlist=net->input_layer->getNeuron_list();
	list<Layer*>::iterator hidden_layer_iter=net->hidden_layers.begin();
	while(hidden_layer_iter!=net->hidden_layers.end())
	{
	 Layer *layer=*hidden_layer_iter++;
	 //Recorremos todas las neuronas de la capa 
	 neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
	 while (hidden_neuron_iter!=neuronlist.end())
	 {
			Neuron *neuron=*hidden_neuron_iter++;
			if (!net->isBias(neuron))
			{
				p++;
			}
	  }		 
	}

	double beta=0.7*pow(p,1/n);
	hidden_layer_iter=net->hidden_layers.begin();
	while(hidden_layer_iter!=net->hidden_layers.end())
	{
	 Layer *layer=*hidden_layer_iter++;
	 //Recorremos todas las neuronas de la capa 
	 neuronlist=layer->getNeuron_list();
	 list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
	 while (hidden_neuron_iter!=neuronlist.end())
	 {
			Neuron *neuron=*hidden_neuron_iter++;
			if (!net->isBias(neuron))
			{
				list<Sinapsis*>::iterator hidden_sinapsis_iter;
				hidden_sinapsis_iter=neuron->getInputs()->begin();
     		    double modulus=0.0;
				while (hidden_sinapsis_iter!=neuron->getInputs()->end())
				{
					Sinapsis *sinapsis=*hidden_sinapsis_iter++;
					modulus+=sinapsis->getWeight()*sinapsis->getWeight();
				}
				modulus=sqrt(modulus);
				hidden_sinapsis_iter=neuron->getInputs()->begin();
     		   	while (hidden_sinapsis_iter!=neuron->getInputs()->end())
				{
					Sinapsis *sinapsis=*hidden_sinapsis_iter++;
					if (!net->isBias(sinapsis->getStart()))
					{
					 sinapsis->setWeight((beta*sinapsis->getWeight())/modulus);
					} else // es un bias
					{
						sinapsis->setWeight(generate_random(-beta,beta));
					}

				}

			}
	 }		 
	}

}


void BackPropagationTrainingAlgorithm::train(void)
{
    BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);

	
	current_epoch=1;
	//Inicializar todos los pesos
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	if (init_weights_to_random_values==true)
	{
		net->resetKnowledge();
		srand((unsigned int)time(0)); 
		fill_weights_with_little_random_values();
		NW_weights_initialization();
	}

	 
	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
	this->net->logger.fout<<"BackPropagation TRAINING START:"<<endl;
	this->net->print();
	do
	{
	 this->net->logger.fout<<"\nEPOCA:"<<current_epoch<<"\n";
	 //cout<<"\nEPOCA:"<<current_epoch<<endl;

     current_epoch++;
	 median_cuadratic_error_in_this_epoch=0.0;
	 
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
	  //cout<<"\nAplicando vector de entrenamiento:"<<endl;
	  //training_pattern->print();
	  //cout<<endl;
	  while(training_pattern_data_index<training_pattern_data_size)
	  {
		//Aplicamos ese valor en las neuronas de entrada
		Neuron *neuron=*input_neuron_iter;
		if (!net->isBias(neuron))
		{
		 double fired_value=training_pattern->data[training_pattern_data_index];
		 neuron->setFired_output(fired_value);

		 net->logger.fout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;
		 training_pattern_data_index++;
		}
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
		  net->logger.fout<<"||HIDDEN_LAYER NEURONS:"<<endl;
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			if (!net->isBias(neuron))
			{
				net->transfer_function->calculate_output(neuron);
				net->logger.fout<<neuron->name<<": zin["<<neuron->getReceived_input()<<"] ";
				net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]"<<endl;
			}
			hidden_neuron_iter++;
		  }
		  
		  hidden_layer_iter++;
	  }

	  
	  //CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA
		neuronlist=net->output_layer->getNeuron_list();
		list<Neuron*>::iterator output_neuron_iter = neuronlist.begin();
	  net->logger.fout<<"||OUTPUT_LAYER NEURONS:"<<endl;
	  while (output_neuron_iter!=neuronlist.end())
	  {
		Neuron *neuron=*output_neuron_iter;
		
		if (!net->isBias(neuron))
		{
		 ((BackPropagation*)net)->transfer_function->calculate_output(neuron);
		  net->logger.fout<<neuron->name<<": yin["<<neuron->getReceived_input()<<"] ";
		  net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]"<<endl;
		  //net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;
		}
		output_neuron_iter++;
	  }


	  /**************************
	   RETROPROPAGACION DEL ERROR
	  ***************************/
	   /* Recorremos la capa de salida calculando los deltas de error y 
	   acumulandolos en la neurona */
	    Pattern *target_pattern=(*target_patterns_iter);
		int target_pattern_data_size=target_pattern->rows*training_pattern->cols;
		int target_pattern_data_index=0;
		neuronlist=net->output_layer->getNeuron_list();
		output_neuron_iter = neuronlist.begin();
	  
	  net->logger.fout<<"\nBACKPROPAGATION:"<<endl;
		
	  while (output_neuron_iter!=neuronlist.end())
	  {
	    Neuron *neuron=*output_neuron_iter;
		if (!net->isBias(neuron))
		{
		 double target=target_pattern->data[target_pattern_data_index];
		 
		 net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
		 net->logger.fout<<" target:"<<target<<endl;
		 //cout<<" target:"<<target<<endl;

		 // E=1/2*sum([tk-yk]^2)
		 //median_cuadratic_error_in_this_epoch+=pow(target-neuron->getFired_output(),2.0);
		 median_cuadratic_error_in_this_epoch+=(target-neuron->getFired_output())*(target-neuron->getFired_output());
 
		 BackPropagationlearning_function->calculate_error_delta(neuron,target);
		 BackPropagationlearning_function->calculate_weight_updates(neuron);	 
		 target_pattern_data_index++; 
		}
		
		output_neuron_iter++;
	  }

	  /* Retropropagacion en las capas ocultas desde la ultima a la primera*/
	  list<Layer*>::reverse_iterator hidden_layer_reverse_iter=net->hidden_layers.rbegin();
	  hidden_layer_iter=net->hidden_layers.end();
	  while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
	  {
		  Layer *layer=*hidden_layer_reverse_iter++;
		  neuronlist=layer->getNeuron_list();
		  list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		  //net->logger.fout<<"||HIDEN_LAYER NEURONS:"<<endl;
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			if (!net->isBias(neuron))
			{
			 BackPropagationlearning_function->calculate_error_delta(neuron);;
			 BackPropagationlearning_function->calculate_weight_updates(neuron);	
			}

			hidden_neuron_iter++;
		  }
		 // this->net->logger.fout<<endl;
	  }


	  /** ACTUALIZACION DE PESOS **/
	  /* Actualizacion pesos capa de salida */
	  neuronlist=net->output_layer->getNeuron_list();
	  output_neuron_iter = neuronlist.begin();	
	  while (output_neuron_iter!=neuronlist.end())
	  {
	     Neuron *neuron=*output_neuron_iter;
		 
		 BackPropagationlearning_function->update_weight(neuron);	 

		 output_neuron_iter++;
	  }
	  /* Actualizacion pesos de las capas ocultas */
	  hidden_layer_reverse_iter=net->hidden_layers.rbegin();
	  while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
	  {
		  Layer *layer=*hidden_layer_reverse_iter++;
		  neuronlist=layer->getNeuron_list();
		  list<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		  while (hidden_neuron_iter!=neuronlist.end())
		  {
			Neuron *neuron=*hidden_neuron_iter;
			
			BackPropagationlearning_function->update_weight(neuron);	


			hidden_neuron_iter++;
		  }
		 // this->net->logger.fout<<endl;
	  }



	  //this->net->logger.fout<<endl<<"ESTADO DE LA RED:"<<endl;
	  //this->net->print();
	  // Siguiente patrón
	  //this->net->logger.fout<<"Siguiente Patron"<<endl;
	  training_patterns_iter++;
	  target_patterns_iter++;
	 }
	 // E=1/2*sum([tk-yk]^2), el sumatorio fue hecho durante el bucle
	 median_cuadratic_error_in_this_epoch*=0.5;

	 if (current_epoch%100==0)
	 {
		 cout<<"\nEPOCH:"<<current_epoch<<":";
	  this->net->logger.fout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
	  cout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
	 }
	}while(stop_condition()==false);

	this->net->logger.fout<<"*********************"<<endl;
	this->net->logger.fout<<"BackPropagation training finished."<<endl;
	//this->net->print();
	
 return;
}
