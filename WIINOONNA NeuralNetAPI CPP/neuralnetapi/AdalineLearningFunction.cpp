/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Adaline.h"
#include "AdalineLearningFunction.h"
#include <cmath>

AdalineLearningFunction::AdalineLearningFunction()
{
	local_max_weight_variation=0.0;
}

AdalineLearningFunction::~AdalineLearningFunction(void)
{
}

void AdalineLearningFunction::setLearning_factor(double alpha)
{
	learning_factor=alpha;
}


bool AdalineLearningFunction::getWeights_have_changed()
{
	 return this->weights_have_changed;
}

void AdalineLearningFunction::setWeights_have_changed(bool value)
{
	 this->weights_have_changed=value;
}



void AdalineLearningFunction::update_weights(Neuron *neuron,double target)
{
	//double fired=neuron->getFired_output();

	if (neuron->net->isBias(neuron))
	{
		cout<<"warning: updating weights of a BIAS";
		if (neuron->getFired_output()!=1)
		 cout<<"warning: BIAS not firing 1!";
	}


	local_max_weight_variation=0;
	// Aplica la función de aprendizaje a todas las sinapsis de entrada de la neurona.
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current;
		double inputed=sinapsis->getStart()->getFired_output();
		double oldweight=sinapsis->getWeight();
		double y_in=neuron->getReceived_input();
		//REGLA DELTA: Ajustar el peso en proporción a la distancia al target
		double new_weight=oldweight+(learning_factor)*(target-y_in)*inputed;
		sinapsis->setWeight(new_weight);

		net->logger.fout<<sinapsis->name<<" new weight:"<<oldweight<<"+"<<
			learning_factor<<"*("<<target<<"-"<<y_in<<")*"<<inputed<<"="<<
			sinapsis->getWeight()<<endl;
		//net->logger.fout<<sinapsis->name<<" new weight->["<<sinapsis->getWeight()<<"]"<<endl;
		

		if (sinapsis->getWeight()!=oldweight)
		{
			weights_have_changed=true;
			double weight_variation=fabs(oldweight-new_weight);
			if (weight_variation>local_max_weight_variation)
				local_max_weight_variation=weight_variation;
		}
		current++;
	 }
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

#include "Adaline.h"
#include "AdalineLearningFunction.h"
#include <cmath>

AdalineLearningFunction::AdalineLearningFunction()
{
	local_max_weight_variation=0.0;
}

AdalineLearningFunction::~AdalineLearningFunction(void)
{
}

void AdalineLearningFunction::setLearning_factor(double alpha)
{
	learning_factor=alpha;
}


bool AdalineLearningFunction::getWeights_have_changed()
{
	 return this->weights_have_changed;
}

void AdalineLearningFunction::setWeights_have_changed(bool value)
{
	 this->weights_have_changed=value;
}



void AdalineLearningFunction::update_weights(Neuron *neuron,double target)
{
	//double fired=neuron->getFired_output();

	if (neuron->net->isBias(neuron))
	{
		cout<<"warning: updating weights of a BIAS";
		if (neuron->getFired_output()!=1)
		 cout<<"warning: BIAS not firing 1!";
	}


	local_max_weight_variation=0;
	// Aplica la función de aprendizaje a todas las sinapsis de entrada de la neurona.
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current;
		double inputed=sinapsis->getStart()->getFired_output();
		double oldweight=sinapsis->getWeight();
		double y_in=neuron->getReceived_input();
		//REGLA DELTA: Ajustar el peso en proporción a la distancia al target
		double new_weight=oldweight+(learning_factor)*(target-y_in)*inputed;
		sinapsis->setWeight(new_weight);

		net->logger.fout<<sinapsis->name<<" new weight:"<<oldweight<<"+"<<
			learning_factor<<"*("<<target<<"-"<<y_in<<")*"<<inputed<<"="<<
			sinapsis->getWeight()<<endl;
		//net->logger.fout<<sinapsis->name<<" new weight->["<<sinapsis->getWeight()<<"]"<<endl;
		

		if (sinapsis->getWeight()!=oldweight)
		{
			weights_have_changed=true;
			double weight_variation=fabs(oldweight-new_weight);
			if (weight_variation>local_max_weight_variation)
				local_max_weight_variation=weight_variation;
		}
		current++;
	 }
}
