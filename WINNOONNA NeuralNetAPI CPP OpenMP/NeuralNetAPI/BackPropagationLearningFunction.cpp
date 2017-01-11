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
#include "BackPropagationLearningFunction.h"
#include <cmath>

#include "Neuron.h"
#include "Sinapsis.h"

BackPropagationLearningFunction::BackPropagationLearningFunction(void)
{
}

BackPropagationLearningFunction::~BackPropagationLearningFunction(void)
{
}



void BackPropagationLearningFunction::setLearning_factor(double alpha)
{
	learning_factor=alpha;
}


/*bool BackPropagationLearningFunction::getWeights_have_changed()
{
	 return this->weights_have_changed;
}

void BackPropagationLearningFunction::setWeights_have_changed(bool value)
{
	 this->weights_have_changed=value;
}*/


static double derived_bipolar_sigmoidal(double fx)
{
	double value;
	value=0.5*(1+bipolar_sigmoidal_transfer_function(fx))*(1-bipolar_sigmoidal_transfer_function(fx));
	return value;

}

double BackPropagationLearningFunction::derived_bipolar_sigmoidal_cached(Neuron *neuron)
{
	double value;
	value=0.5*(1+neuron->getFired_output())*(1-neuron->getFired_output());
	return value;

}


void BackPropagationLearningFunction::calculate_error_delta(Neuron *neuron,double target)
{
  double delta;
  delta=(target-neuron->getFired_output());
  //delta*=derived_bipolar_sigmoidal(neuron->getReceived_input());
  //optimizacion:
  delta*=derived_bipolar_sigmoidal_cached(neuron);
  neuron->setCommited_error(delta);

  neuron->net->logger.fout<<neuron->name<<": delta="<<delta<<endl;
}

void BackPropagationLearningFunction::calculate_weight_updates(Neuron *neuron)
{
	/* Para todas las psinapsis que llegan a esta neurona calcula 
	la variacion de pesos dependiente del delta inmediatamente antes calculado */
   double lambda;
   list<Sinapsis*>::iterator iter=neuron->getInputs()->begin();
   while (iter!=neuron->getInputs()->end())
   {
	   Sinapsis *current=*iter++;
  
	   //alpha*deltak*zj
	   double alpha=learning_factor;
	   double delta=neuron->getCommited_error();

	   lambda=alpha*delta*
		   current->getStart()->getFired_output();

	   current->setWeight_update(lambda);
	   //neuron->net->logger.fout<<current->getStart()->name<<"->"<<neuron->name<<": lambda="<<lambda<<endl;
   }
   
}



void BackPropagationLearningFunction::calculate_error_delta(Neuron *neuron)
{
  // el delta de una neurona no de salida es la suma pesada de los deltas
  // de las neuronas que la suceden
  double delta=0;

   list<Sinapsis*>::iterator iter=neuron->getOutputs()->begin();
   while (iter!=neuron->getOutputs()->end())
   {
	   Sinapsis *current=*iter++;

	   delta+=current->getWeight()*current->getEnd()->getCommited_error();
   }
   // lo multiplica por la derivada de su función de activacion.
   delta*=derived_bipolar_sigmoidal(neuron->getReceived_input());
   neuron->setCommited_error(delta);

   neuron->net->logger.fout<<neuron->name<<": deltah="<<delta<<endl;
}


void BackPropagationLearningFunction::update_weight(Neuron *neuron)
{
	double fired=neuron->getFired_output();

	// Aplica la función de aprendizaje a todas las sinapsis de entrada de la neurona.
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current++;
		double oldweight=sinapsis->getWeight();

		double new_weight=oldweight+sinapsis->getWeight_update();
		sinapsis->setWeight(new_weight);

		/*if (sinapsis->getWeight()!=oldweight)
		{
			weights_have_changed=true;
		}*/
	 }
	
	
}