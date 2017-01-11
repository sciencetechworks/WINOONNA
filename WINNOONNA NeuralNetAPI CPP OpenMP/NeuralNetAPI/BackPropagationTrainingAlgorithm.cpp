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
#include <omp.h>


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

	vector<Sinapsis*>::iterator sinapsis_iter=net->sinapsis_list.begin();
	int seed1,seed2,seed3;
	seed1=clock()%30000;
	seed2=clock()%30000;
	seed3=clock()%30000;

	while(sinapsis_iter!=net->sinapsis_list.end())
	{
		double random = generate_random_r8(-0.5,0.5,&seed1,&seed2,&seed3);

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

	int seed1,seed2,seed3;
	seed1=clock()%30000;
	seed2=clock()%30000;
	seed3=clock()%30000;

	n=this->net->input_layer->getNeuron_list().size();

	vector<Neuron*> neuronlist=net->input_layer->getNeuron_list();
	list<Layer*>::iterator hidden_layer_iter=net->hidden_layers.begin();
	while(hidden_layer_iter!=net->hidden_layers.end())
	{
		Layer *layer=*hidden_layer_iter++;
		//Recorremos todas las neuronas de la capa 
		neuronlist=layer->getNeuron_list();
		vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		while (hidden_neuron_iter!=neuronlist.end())
		{
			Neuron *neuron=*hidden_neuron_iter++;
			if (!(net->isBias(neuron)))
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
		vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
		while (hidden_neuron_iter!=neuronlist.end())
		{
			Neuron *neuron=*hidden_neuron_iter++;
			if (!(net->isBias(neuron)))
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
						sinapsis->setWeight(generate_random_r8(-beta,beta,&seed1,&seed2,&seed3));
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
		//net->resetKnowledge();
		//srand((unsigned int)time(0)); 
		fill_weights_with_little_random_values();
		// Simplificamos: eliminamos inicializacion NW
		//NW_weights_initialization();
	}


	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
#ifdef DO_LOGGIN
	this->net->logger.fout<<"BackPropagation TRAINING START:"<<endl;
	this->net->print();
#endif

	do
	{
		//this->net->logger.fout<<"\nEPOCA:"<<current_epoch<<"\n";
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
			vector<Neuron*> neuronlist=net->input_layer->getNeuron_list();
			vector<Neuron*>::iterator input_neuron_iter = neuronlist.begin();
#ifdef DO_LOGGIN
			net->logger.fout<<"\nAplicando vector de entrenamiento:"<<endl;
			//cout<<"\nAplicando vector de entrenamiento:"<<endl;
			//training_pattern->print();
			//cout<<endl;
#endif
			while(training_pattern_data_index<training_pattern_data_size)
			{
				//Aplicamos ese valor en las neuronas de entrada
				Neuron *neuron=*input_neuron_iter;
				if (!(net->isBias(neuron)))
				{
					double fired_value=training_pattern->data[training_pattern_data_index];
					neuron->setFired_output(fired_value);
#ifdef DO_LOGGIN
					net->logger.fout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;
#endif
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
				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
#ifdef DO_LOGGIN
				net->logger.fout<<"||HIDDEN_LAYER NEURONS:"<<endl;
#endif
				while (hidden_neuron_iter!=neuronlist.end())
				{
					Neuron *neuron=*hidden_neuron_iter;
					if (!(net->isBias(neuron)))
					{
						net->transfer_function->calculate_output(neuron);
#ifdef DO_LOGGIN
						net->logger.fout<<neuron->name<<": zin["<<neuron->getReceived_input()<<"] ";
						net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]"<<endl;
#endif
					}
					hidden_neuron_iter++;
				}

				hidden_layer_iter++;
			}


			//CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA
			neuronlist=net->output_layer->getNeuron_list();
			vector<Neuron*>::iterator output_neuron_iter = neuronlist.begin();
#ifdef DO_LOGGIN
			net->logger.fout<<"||OUTPUT_LAYER NEURONS:"<<endl;
#endif
			while (output_neuron_iter!=neuronlist.end())
			{
				Neuron *neuron=*output_neuron_iter;

				if (!(net->isBias(neuron)))
				{
					((BackPropagation*)net)->transfer_function->calculate_output(neuron);
#ifdef DO_LOGGIN
					net->logger.fout<<neuron->name<<": yin["<<neuron->getReceived_input()<<"] ";
					net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]"<<endl;
					//net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;
#endif
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
#ifdef DO_LOGGIN
			net->logger.fout<<"\nBACKPROPAGATION:"<<endl;
#endif	

			while (output_neuron_iter!=neuronlist.end())
			{
				Neuron *neuron=*output_neuron_iter;
				if (!(net->isBias(neuron)))
				{
					double target=target_pattern->data[target_pattern_data_index];
#ifdef DO_LOGGIN 
					net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
					net->logger.fout<<" target:"<<target<<endl;
					//cout<<" target:"<<target<<endl;
#endif
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
				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
				//net->logger.fout<<"||HIDEN_LAYER NEURONS:"<<endl;
				while (hidden_neuron_iter!=neuronlist.end())
				{
					Neuron *neuron=*hidden_neuron_iter;
					if (!(net->isBias(neuron)))
					{
						BackPropagationlearning_function->calculate_error_delta(neuron);;
						BackPropagationlearning_function->calculate_weight_updates(neuron);	
					}

					hidden_neuron_iter++;
				}
#ifdef DO_LOGGIN
				// this->net->logger.fout<<endl;
#endif
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
				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
				while (hidden_neuron_iter!=neuronlist.end())
				{
					Neuron *neuron=*hidden_neuron_iter;

					BackPropagationlearning_function->update_weight(neuron);	


					hidden_neuron_iter++;
				}
#ifdef DO_LOGGIN
				// this->net->logger.fout<<endl;
#endif
			}

#ifdef DO_LOGGIN
			//this->net->logger.fout<<endl<<"ESTADO DE LA RED:"<<endl;
			//this->net->print();
			// Siguiente patrón
			//this->net->logger.fout<<"Siguiente Patron"<<endl;
#endif
			training_patterns_iter++;
			target_patterns_iter++;
		}
		// E=1/2*sum([tk-yk]^2), el sumatorio fue hecho durante el bucle
		median_cuadratic_error_in_this_epoch*=0.5;

		if (current_epoch%100==0)
		{
			cout<<"\nEPOCH:"<<current_epoch<<":";
#ifdef DO_LOGGIN
			this->net->logger.fout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
#endif
			cout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
		}
	}while(stop_condition()==false);

#ifdef DO_LOGGIN
	this->net->logger.fout<<"*********************"<<endl;
	this->net->logger.fout<<"BackPropagation training finished."<<endl;
	//this->net->print();
#endif
	return;
}

/*********************************************************************************
OPEN MP VERSIONS
**********************************************************************************/

void BackPropagationTrainingAlgorithm::fill_weights_with_little_random_values_omp()
{

	vector<Sinapsis*>::iterator sinapsis_iter=net->sinapsis_list.begin();
	//int seed1,seed2,seed3;


	/* WHILE SUBSTITUIDO POR SU VERSION OPENMP MAS ABAJO
	while(sinapsis_iter!=net->sinapsis_list.end())
	{
	double random = generate_random_r8(-0.5,0.5,&seed1,&seed2,&seed3);

	//((double)rand() / ((double)RAND_MAX));
	//random-=0.5;

	Sinapsis *sinapsis=*sinapsis_iter;
	sinapsis->setWeight(random);
	sinapsis_iter++;
	}*/

	/** OPENMP: SUBSTITUCION DE WHILE*/
	int i=0;
	int sinapsis_index=0;
	int sinapsis_list_length=net->sinapsis_list.size();
	omp_set_num_threads(omp_get_max_threads());
	//Sinapsis **arr_sinapsis=(Sinapsis**)malloc(omp_get_max_threads()*sizeof(Sinapsis*));
	int* random_seeds=(int*)malloc(3*omp_get_max_threads()*sizeof(int));
	// Inicializamos el array de semillas independientes de cada hilo.
	//#pragma omp parallel for private (i) 
	for (i=0;i<3*omp_get_max_threads();i++)
	{
		random_seeds[i]=clock();
	}

	Sinapsis *sinapsis;
	double random;

#pragma omp parallel for private(sinapsis,random,i)
	for (i=0;i<sinapsis_list_length;i++)
	{
		sinapsis=net->sinapsis_list[i];
		random = generate_random_r8(-0.5,0.5,&(random_seeds[omp_get_thread_num()]),&(random_seeds[omp_get_thread_num()+1]),&(random_seeds[omp_get_thread_num()+2]));
		sinapsis->setWeight(random);
	}

	free(random_seeds);
}


inline void ParalellInputLayer(NeuralNet *net,double *input_values)
{


	vector<Neuron*> process_vector=net->input_layer->getPure_Neuron_list();
	int index_neuron=0;
	Neuron *neuron;
	double fired_value;



	//omp_set_num_threads(omp_get_max_threads());

#pragma omp parallel for private(neuron,fired_value,index_neuron)
	for(index_neuron=0;index_neuron<(int)(process_vector.size());index_neuron++)
	{
		//printf("Procesando indices %d a %d\n",training_pattern_data_index,training_pattern_data_index+omp_get_max_threads());
		neuron=process_vector[index_neuron]; 
		//cout<<"OMP Thread"<<omp_get_thread_num()<<" Neuron:"<<neuron->name<<" pos"<<index_neuron<<endl;
		fired_value=input_values[index_neuron];
		neuron->setFired_output(fired_value);
		//cout<<neuron->name<<"="<<training_pattern->data[training_pattern_data_index]<<endl;			 
	}
}

inline void FireParalellLayer(NeuralNet *net,Layer *layer)
{

	vector<Neuron*> process_vector=layer->getPure_Neuron_list();
	int index_neuron=0,n;
	Neuron *neuron;
	//omp_set_num_threads(omp_get_max_threads());

	n=(int)process_vector.size();

#pragma omp parallel for  private(neuron,index_neuron)
	for(index_neuron=0;index_neuron<n;index_neuron++)
	{
		//printf("Procesando indices %d a %d\n",training_pattern_data_index,training_pattern_data_index+omp_get_max_threads());
		neuron=process_vector[index_neuron]; 
		net->transfer_function->calculate_output(neuron); 
	}
}

// Devuelve el error cuadratico medio
inline double CalculateParalellDeltas(NeuralNet *net,Layer *layer,double *target_data_values)
{

	vector<Neuron*> process_vector=layer->getPure_Neuron_list();
	int index_neuron=0,i=0;
	Neuron *neuron;
	double local_error=0.0,median_cuadratic_error=0.0;
	BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);
	int n=process_vector.size();

#pragma omp parallel for reduction(+:local_error) private(neuron,index_neuron)
	for(index_neuron=0;index_neuron<n;index_neuron++)
	{

		neuron=process_vector[index_neuron]; 
		//if (!(net->isBias(neuron)))
		//{
		double target=target_data_values[index_neuron];

#ifdef DO_LOGGIN
		net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
		net->logger.fout<<" target:"<<target<<endl;
		//cout<<" target:"<<target<<endl;
#endif
		// E=1/2*sum([tk-yk]^2)
		//median_cuadratic_error_in_this_epoch+=pow(target-neuron->getFired_output(),2.0);
		local_error=(target-neuron->getFired_output())*(target-neuron->getFired_output());

		BackPropagationlearning_function->calculate_error_delta(neuron,target);
		BackPropagationlearning_function->calculate_weight_updates(neuron);
		//cout<<"OUTPUT: OMP Thread"<<omp_get_thread_num()<<" Neuron:"<<neuron->name<<" pos"<<index_neuron<<endl;
		//}
	}

	//cout<<"END OMP FOR"<<endl;
	median_cuadratic_error+=local_error; // He solucionado una condicion de false sharing

	return   median_cuadratic_error;
}


inline void CalculateParalellDeltasNotOutputLayer(NeuralNet *net,Layer *layer)
{

	vector<Neuron*> process_vector=layer->getPure_Neuron_list();
	int index_neuron=0,i=0;
	Neuron *neuron;
	BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);
	int n=process_vector.size();

#pragma omp parallel for private(neuron,index_neuron)
	for(index_neuron=0;index_neuron<n;index_neuron++)
	{

		neuron=process_vector[index_neuron]; 

#ifdef DO_LOGGIN
		net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
		net->logger.fout<<" target:"<<target<<endl;
		//cout<<" target:"<<target<<endl;
#endif
		BackPropagationlearning_function->calculate_error_delta(neuron);;
		BackPropagationlearning_function->calculate_weight_updates(neuron);

	}

}

inline void ParalellUpdateWeights(NeuralNet *net,Layer *layer)
{

	vector<Neuron*> process_vector=layer->getNeuron_list(); // Con bias y sin bias
	int index_neuron=0,i=0;
	Neuron *neuron;
	BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);
	int n=process_vector.size();

#pragma omp parallel for private(neuron,index_neuron)
	for(index_neuron=0;index_neuron<n;index_neuron++)
	{

		neuron=process_vector[index_neuron]; 

		BackPropagationlearning_function->update_weight(neuron);	

	}

}


void BackPropagationTrainingAlgorithm::train_omp(int nthreads)
{
	BackPropagationLearningFunction *BackPropagationlearning_function=(BackPropagationLearningFunction*)(net->learning_function);

	omp_set_num_threads(nthreads); //omp_get_max_threads()

	current_epoch=1;
	//Inicializar todos los pesos
	//Previamente se debe haber ajustado el factor de aprendizaje
	//a un valor entre 0<alpha<=1
	if (init_weights_to_random_values==true)
	{
		//net->resetKnowledge();
		//srand((unsigned int)time(0)); 
		fill_weights_with_little_random_values_omp();
		// Simplificamos: eliminamos inicializacion NW
		//NW_weights_initialization();
	}


	//APLICAR TODOS LOS VECTORES DE ENTRENAMIENTO
#ifdef DO_LOGGIN
	this->net->logger.fout<<"BackPropagation TRAINING START:"<<endl;
	this->net->print();
#endif
	do
	{
#ifdef DO_LOGGIN
		this->net->logger.fout<<"\nEPOCA:"<<current_epoch<<"\n";
		//cout<<"\nEPOCA:"<<current_epoch<<endl;
#endif
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
			ParalellInputLayer(net,training_pattern->data);

			// PROPAGAR LAS ENTRADAS A CADA UNA DE LAS CAPAS OCULTAS
			//CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE LAS CAPAS OCULTAS

			// PROCESO DE LAS CAPAS OCULTAS
			list<Layer*>::iterator hidden_layer_iter=net->hidden_layers.begin();
			while(hidden_layer_iter!=net->hidden_layers.end())
			{
				Layer *layer=*hidden_layer_iter;

				//Recorremos todas las neuronas de la capa aplicando la funcion
				//de transferencia

				FireParalellLayer(net,layer);	   	
				/*WHILE SUBSTITUIDO POR VERSION OPENMP
				vector<Neuron*> neuronlist=layer->getNeuron_list();

				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
				#ifdef DO_LOGGIN
				net->logger.fout<<"||HIDDEN_LAYER NEURONS:"<<endl;
				#endif

				while (hidden_neuron_iter!=neuronlist.end())
				{
				Neuron *neuron=*hidden_neuron_iter;
				if (!(neuron->is_bias))
				{
				net->transfer_function->calculate_output(neuron);
				//net->logger.fout<<neuron->name<<": zin["<<neuron->getReceived_input()<<"] ";
				//net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]"<<endl;
				}
				hidden_neuron_iter++;
				} //*/

				/* OPENMP: SUBSTITUCION DE WHILE

				int i=0;
				int neuron_index=0;
				int neuron_list_length=neuronlist.size();
				omp_set_num_threads(omp_get_max_threads());
				//Neuron **arr_neuron= (Neuron**)paralell_channels; // (Neuron**)malloc(omp_get_max_threads()*sizeof(Neuron*));		
				while(neuron_index<neuron_list_length)
				{
				//printf("Procesando indices %d a %d\n",training_pattern_data_index,training_pattern_data_index+omp_get_max_threads());

				#pragma omp parallel 
				{
				int pos=neuron_index+omp_get_thread_num();
				if (pos<neuron_list_length)
				{
				Neuron *neuron=neuronlist[pos]; //arr_neuron[omp_get_thread_num()];
				// PROCESS NEURON
				//cout<<"OMP Thread"<<omp_get_thread_num()<<" Neuron:"<<neuron->name<<endl;
				if (!(neuron->is_bias))
				{
				net->transfer_function->calculate_output(neuron);
				#ifdef DO_LOGGIN
				net->logger.fout<<neuron->name<<": zin["<<neuron->getReceived_input()<<"] ";
				net->logger.fout<<"fzin["<<neuron->getFired_output()<<"]"<<endl;
				#endif
				}
				// END PROCESS NEURON 
				}
				}
				neuron_index+=omp_get_max_threads();
				}
				// Finalizado con esta capa intermedia
				// END OMP CONVERTED WHILE */

				hidden_layer_iter++;
			}


			//CALCULAR LAS RESPUESTAS DE LAS NEURONAS DE SALIDA

			FireParalellLayer(net,net->output_layer);
			/*	vector<Neuron*> neuronlist=net->output_layer->getNeuron_list();
			vector<Neuron*>::iterator output_neuron_iter = neuronlist.begin();
			#ifdef DO_LOGGIN
			net->logger.fout<<"||OUTPUT_LAYER NEURONS:"<<endl;
			#endif
			while (output_neuron_iter!=neuronlist.end())
			{
			Neuron *neuron=*output_neuron_iter;

			if (!(neuron->is_bias))
			{
			((BackPropagation*)net)->transfer_function->calculate_output(neuron);
			#ifdef DO_LOGGIN
			net->logger.fout<<neuron->name<<": yin["<<neuron->getReceived_input()<<"] ";
			net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]"<<endl;
			//net->logger.fout<<"F("<<neuron->getReceived_input()<<")="<<neuron->getFired_output()<<endl;
			#endif
			}
			output_neuron_iter++;
			}*/


			/**************************
			RETROPROPAGACION DEL ERROR
			***************************/
			/* Recorremos la capa de salida calculando los deltas de error y 
			acumulandolos en la neurona */

			median_cuadratic_error_in_this_epoch+=CalculateParalellDeltas(net,net->output_layer,(*target_patterns_iter)->data);
			/*


			Pattern *target_pattern=(*target_patterns_iter);
			int target_pattern_data_size=target_pattern->rows*training_pattern->cols;
			int target_pattern_data_index=0;
			vector<Neuron*> neuronlist=net->output_layer->getNeuron_list();
			vector<Neuron*>::iterator output_neuron_iter = neuronlist.begin();
			#ifdef DO_LOGGIN
			net->logger.fout<<"\nBACKPROPAGATION:"<<endl;
			#endif

			while (output_neuron_iter!=neuronlist.end())
			{
			Neuron *neuron=*output_neuron_iter;
			if (!(neuron->is_bias))
			{
			double target=target_pattern->data[target_pattern_data_index];

			#ifdef DO_LOGGIN
			net->logger.fout<<"fyin["<<neuron->getFired_output()<<"]:";
			net->logger.fout<<" target:"<<target<<endl;
			//cout<<" target:"<<target<<endl;
			#endif
			// E=1/2*sum([tk-yk]^2)
			//median_cuadratic_error_in_this_epoch+=pow(target-neuron->getFired_output(),2.0);
			median_cuadratic_error_in_this_epoch+=(target-neuron->getFired_output())*(target-neuron->getFired_output());

			BackPropagationlearning_function->calculate_error_delta(neuron,target);
			BackPropagationlearning_function->calculate_weight_updates(neuron);	 
			target_pattern_data_index++; 
			}

			output_neuron_iter++;
			}*/


			vector<Neuron*> neuronlist;
			/* Retropropagacion en las capas ocultas desde la ultima a la primera*/
			list<Layer*>::reverse_iterator hidden_layer_reverse_iter=net->hidden_layers.rbegin();
			hidden_layer_iter=net->hidden_layers.end();
			while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
			{
				Layer *layer=*hidden_layer_reverse_iter++;
				CalculateParalellDeltasNotOutputLayer(net,layer);
				/*neuronlist=layer->getNeuron_list();
				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
				#ifdef DO_LOGGIN
				//net->logger.fout<<"||HIDEN_LAYER NEURONS:"<<endl;
				#endif
				while (hidden_neuron_iter!=neuronlist.end())
				{
				Neuron *neuron=*hidden_neuron_iter;
				if (!(net->isBias(neuron)))
				{
				BackPropagationlearning_function->calculate_error_delta(neuron);;
				BackPropagationlearning_function->calculate_weight_updates(neuron);	
				}

				hidden_neuron_iter++;
				}
				#ifdef DO_LOGGIN
				// this->net->logger.fout<<endl;
				#endif*/
			}


			/** ACTUALIZACION DE PESOS **/
			/* Actualizacion pesos capa de salida */
			ParalellUpdateWeights(net,net->output_layer);

			/*
			neuronlist=net->output_layer->getNeuron_list();
			vector<Neuron*>::iterator output_neuron_iter = neuronlist.begin();	
			while (output_neuron_iter!=neuronlist.end())
			{
			Neuron *neuron=*output_neuron_iter;

			BackPropagationlearning_function->update_weight(neuron);	 

			output_neuron_iter++;
			}*/

			/* Actualizacion pesos de las capas ocultas */
			hidden_layer_reverse_iter=net->hidden_layers.rbegin();
			while(hidden_layer_reverse_iter!=net->hidden_layers.rend())
			{
				Layer *layer=*hidden_layer_reverse_iter++;

				ParalellUpdateWeights(net,layer);

				/*neuronlist=layer->getNeuron_list();
				vector<Neuron*>::iterator hidden_neuron_iter = neuronlist.begin();
				while (hidden_neuron_iter!=neuronlist.end())
				{
				Neuron *neuron=*hidden_neuron_iter;

				BackPropagationlearning_function->update_weight(neuron);	


				hidden_neuron_iter++;
				}*/
#ifdef DO_LOGGIN
				// this->net->logger.fout<<endl;
#endif
			}


#ifdef DO_LOGGIN
			//this->net->logger.fout<<endl<<"ESTADO DE LA RED:"<<endl;
			//this->net->print();
			// Siguiente patrón
			//this->net->logger.fout<<"Siguiente Patron"<<endl;
#endif
			training_patterns_iter++;
			target_patterns_iter++;
		}
		// E=1/2*sum([tk-yk]^2), el sumatorio fue hecho durante el bucle
		median_cuadratic_error_in_this_epoch*=0.5;
		if (current_epoch%100==0)
		{
			cout<<"\nEPOCH:"<<current_epoch<<":";
#ifdef DO_LOGGIN
			this->net->logger.fout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
#endif
			cout<<"Commited median error:"<<median_cuadratic_error_in_this_epoch<<endl;
		}
	}while(stop_condition()==false);

#ifdef DO_LOGGIN
	this->net->logger.fout<<"*********************"<<endl;
	this->net->logger.fout<<"BackPropagation training finished."<<endl;
	//this->net->print();
#endif

	return;
}