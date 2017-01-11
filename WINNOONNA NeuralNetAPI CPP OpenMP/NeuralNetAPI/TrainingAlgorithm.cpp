/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "TrainingAlgorithm.h"


#include "Utils.h"
#include <cmath>
#include <limits>

TrainingAlgorithm::TrainingAlgorithm(void)
{
}

TrainingAlgorithm::~TrainingAlgorithm(void)
{
}


TrainingAlgorithm::TrainingAlgorithm(NeuralNet *the_net)
{
	max_epochs=20;
	this->net=the_net;
}



/*void TrainingAlgorithm::addTraining_pattern(Pattern *pattern)
{
	this->training_patterns.push_back(input_pattern);
	this->target_patterns.push_back(target_patter);
	return;
}

void TrainingAlgorithm::empty_training_patterns()
{
	while (!training_patterns.empty())
		training_patterns.pop_back();
	while (!target_patterns.empty())
		target_patterns.pop_back();
}*/

void TrainingAlgorithm::setMax_epochs(int n)
{
	max_epochs=n;
}


bool TrainingAlgorithm::stop_condition()
{
	// Si no se han actualizado pesos entonces
	// se ha alcanzado la condicion de finalizacion
	// de entrenamiento.
	return weights_updated==false;
}



void TrainingAlgorithm::train(void)
{
	
 return;
}

double TrainingAlgorithm::calculate_hit_ratio_after_training(int noise_percent,double max_allowed_dist_to_target)
{
	list<Pattern *>::iterator training_patterns_iter;
	list<Pattern *>::iterator target_patterns_iter;

	double hits=0.0;
	double total_patterns=training_patterns.patterns_list.size();

	training_patterns_iter=training_patterns.patterns_list.begin();
	target_patterns_iter=target_patterns.patterns_list.begin();

	while(training_patterns_iter!=training_patterns.patterns_list.end())
	{
		/*Recorremos la capa de entrada asignando valores de entrenamiento*/
		vector<Neuron*> input_neuron_list=this->net->input_layer->getNeuron_list();
		vector<Neuron*>::iterator input_neuron_iter=input_neuron_list.begin();

		Pattern *pattern=*training_patterns_iter;
		double *pattern_data=pattern->data;
		int pattern_data_index=0;

		/* insertamos ruido en la prueba (a las entradas de la neurona)
		 creamos una copia del patron para no sumar ruidos de pruebas
		 sucesivas, la copia solo se usa para el mostrado en el log.
		 */
		 Pattern *input_copy_pattern=new Pattern(pattern);

		while(input_neuron_iter!=input_neuron_list.end())
		{
		 Neuron *Xi=*input_neuron_iter;
		 if (net->isBias(Xi))
		 {
			 input_neuron_iter++;
			 continue;
		 }
		 double input;

		 input=pattern_data[pattern_data_index];

		 
		 if (true_only_an_x_percent_of_times(noise_percent/100.0))
		 {
			 if (pattern->is_bipolar==true)
			 {
			  if (input==-1) input=1;
				else
			  if (input==1) input=-1;
			 
			 } else
			 {
			  if (input==0) input=1;
				else
			  if (input==1) input=0;
			 }
			 input_copy_pattern->data[pattern_data_index]=input;
		 }
		 

		 Xi->setFired_output(input);
		 /*
		 cout<<Xi->name<<"="<<input;
		 cout<<" ("<<(input*training_patterns.applied_normalization_factor)<<") "<<endl;
		 */

		 //net->logger.fout<<Xi->name<<"="<<input<<endl;
		 input_neuron_iter++;
		 pattern_data_index++;
		}

		//Hemos cargado la entrada, mira la salida de la red:
		//cout<<"Probando con patron ruidoso"<<endl;
		//input_copy_pattern->print(net->logger.fout);
		net->logger.fout<<"Le preguntamos a la red:";
		input_copy_pattern->print(net->logger.fout);
		net->logger.fout<<endl;

		delete input_copy_pattern;
		/**
		LANZAMOS LA RED PARA QUE PREDIGA LA SALIDA
		**/
		net->predict();
		list<double> results;
		// Cargamos en resultados la capa de salida de la red
		// saltandonos los bias
		vector<Neuron*> output_neurons_list=net->output_layer->getNeuron_list();
		vector<Neuron*>::iterator output_neurons_iter=output_neurons_list.begin();

		while(output_neurons_iter!=output_neurons_list.end())
		{
			Neuron* Y=*output_neurons_iter;
			if (!net->isBias(Y))
			{
				//net->logger.fout<<Y->name<<"="<<Y->getFired_output()<<endl;
				/*
				cout<<Y->name<<"="<<Y->getFired_output();
				cout<<" ("<<(Y->getFired_output()*target_patterns.applied_normalization_factor)<<") ";
				cout<<" ("<<(round(Y->getFired_output()*target_patterns.applied_normalization_factor))<<") "<<endl;
				*/
				results.push_back(Y->getFired_output());
			}
			output_neurons_iter++;
		}

	
		//Comparamos el vector resultado con el vector objetivo:		
		Pattern *target=*target_patterns_iter;
		double *target_data=target->data;
		int target_data_index=0;

		double *results_data=new double[results.size()];
		int i=0;
		list<double>::iterator iter=results.begin();
		while (iter!=results.end())
		{
		 results_data[i++]=(*iter);
		 iter++;
		}
		Pattern *predicted_pattern=new Pattern();
		predicted_pattern->rows=target->rows;
		predicted_pattern->cols=target->cols;
		predicted_pattern->data=results_data;
		net->logger.fout<<"La red responde:";
		predicted_pattern->print(net->logger.fout);
		net->logger.fout<<endl;

		list<double>::iterator results_iter=results.begin();
		bool right_prediction=true;

		double distance_to_target=std::numeric_limits<double>::max();;
		while(results_iter!=results.end())
		{
		 double target=target_data[target_data_index];
		 double predict=*results_iter;
		 // cout<<" prediction is: "<<predict<<" target is: "<<target<<endl;
		 distance_to_target=fabs(target-predict);
		 if (distance_to_target>max_allowed_dist_to_target)
		 {
		  right_prediction=false;
		  break;
		 }
		 target_data_index++;
		 results_iter++;
		}

		if (right_prediction==true)
		{
		   hits+=1.0;
		   net->logger.fout<<"prediction Hit"<<endl;
		   /*
		   cout<<"prediction Hit ";
		   cout<<"distance to target:"<<distance_to_target<<endl;
		   */
		} else
		{
			net->logger.fout<<"prediction Failed"<<endl;
			/*
		   cout<<"prediction Failed ";
		   cout<<"distance to target:"<<distance_to_target<<endl;
		   */
		}

		training_patterns_iter++;
		target_patterns_iter++;
	}

	double success_ratio=hits/total_patterns;
	net->logger.fout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	net->logger.fout<<success_ratio;
	net->logger.fout<<"("<<success_ratio*100.0<<"%)"<<endl;

	return success_ratio;
}