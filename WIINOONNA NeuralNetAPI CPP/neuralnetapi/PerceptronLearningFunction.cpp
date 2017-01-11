/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "PerceptronLearningFunction.h"

PerceptronLearningFunction::PerceptronLearningFunction()
{
	
}

PerceptronLearningFunction::~PerceptronLearningFunction(void)
{
}

void PerceptronLearningFunction::setLearning_factor(double alpha)
{
	learning_factor=alpha;
}


bool PerceptronLearningFunction::getWeights_have_changed()
{
	 return this->weights_have_changed;
}

void PerceptronLearningFunction::setWeights_have_changed(bool value)
{
	 this->weights_have_changed=value;
}



void PerceptronLearningFunction::update_weights(Neuron *neuron,double target)
{
	//double fired=neuron->getFired_output();

	if (neuron->net->isBias(neuron))
	{
		cout<<"warning: updating weights of a BIAS";
		if (neuron->getFired_output()!=1)
		 cout<<"warning: BIAS not firing 1!";
	}

	/*if (fired!=target)
	{*/
	//cout<<"[UNDESIRED]";
	// Aplica la función de aprendizaje a todas las sinapsis de entrada de la neurona.
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current;
		double inputed=sinapsis->getStart()->getFired_output();
		double oldweight=sinapsis->getWeight();
		
		sinapsis->setWeight(oldweight+(this->learning_factor)*target*inputed);
		net->logger.fout<<sinapsis->name<<" new weight->["<<sinapsis->getWeight()<<"]"<<endl;
		if (sinapsis->getWeight()!=oldweight)
		{
			weights_have_changed=true;
		}
		current++;
	 }
	/*} else //just output it
	{
     list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	 while (current != neuron->getInputs()->end())
	 {
	  Sinapsis *sinapsis=*current;
	  //this->net->logger.fout<<"["<<sinapsis->getWeight()<<"]";
	  //cout<<"[target]";
	  current++;
	 }
	}*/
}/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "PerceptronLearningFunction.h"

PerceptronLearningFunction::PerceptronLearningFunction()
{
	
}

PerceptronLearningFunction::~PerceptronLearningFunction(void)
{
}

void PerceptronLearningFunction::setLearning_factor(double alpha)
{
	learning_factor=alpha;
}


bool PerceptronLearningFunction::getWeights_have_changed()
{
	 return this->weights_have_changed;
}

void PerceptronLearningFunction::setWeights_have_changed(bool value)
{
	 this->weights_have_changed=value;
}



void PerceptronLearningFunction::update_weights(Neuron *neuron,double target)
{
	//double fired=neuron->getFired_output();

	if (neuron->net->isBias(neuron))
	{
		cout<<"warning: updating weights of a BIAS";
		if (neuron->getFired_output()!=1)
		 cout<<"warning: BIAS not firing 1!";
	}

	/*if (fired!=target)
	{*/
	//cout<<"[UNDESIRED]";
	// Aplica la función de aprendizaje a todas las sinapsis de entrada de la neurona.
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	 {
	   	Sinapsis *sinapsis=*current;
		double inputed=sinapsis->getStart()->getFired_output();
		double oldweight=sinapsis->getWeight();
		
		sinapsis->setWeight(oldweight+(this->learning_factor)*target*inputed);
		net->logger.fout<<sinapsis->name<<" new weight->["<<sinapsis->getWeight()<<"]"<<endl;
		if (sinapsis->getWeight()!=oldweight)
		{
			weights_have_changed=true;
		}
		current++;
	 }
	/*} else //just output it
	{
     list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	 while (current != neuron->getInputs()->end())
	 {
	  Sinapsis *sinapsis=*current;
	  //this->net->logger.fout<<"["<<sinapsis->getWeight()<<"]";
	  //cout<<"[target]";
	  current++;
	 }
	}*/
}