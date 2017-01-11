/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "BackPropagationTransferFunction.h"
#include <cmath>

BackPropagationTransferFunction::BackPropagationTransferFunction(void)
{
}

BackPropagationTransferFunction::~BackPropagationTransferFunction(void)
{
}






void BackPropagationTransferFunction::calculate_output(Neuron *neuron)
{

	double y_input=0.0;

	// Obtiene la suma pesada de las entradas multiplicadas por sus pesos
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	{
		Sinapsis *sinapsis=*current;
		double xi=sinapsis->getStart()->getFired_output();
		double wi=sinapsis->getWeight();
		y_input+=xi*wi;
		current++;
	}

	neuron->setReceived_input(y_input);

	// Decide  qué dispara:
	neuron->setFired_output(bipolar_sigmoidal_transfer_function(y_input));

	//neuron->net->logger.fout<<neuron->name<<"_in"<<"="<<neuron->getReceived_input()<<endl;
	//neuron->net->logger.fout<<"F("<<neuron->name<<")="<<neuron->getFired_output()<<endl;
}/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "BackPropagationTransferFunction.h"
#include <cmath>

BackPropagationTransferFunction::BackPropagationTransferFunction(void)
{
}

BackPropagationTransferFunction::~BackPropagationTransferFunction(void)
{
}






void BackPropagationTransferFunction::calculate_output(Neuron *neuron)
{

	double y_input=0.0;

	// Obtiene la suma pesada de las entradas multiplicadas por sus pesos
	list<Sinapsis*>::iterator current = neuron->getInputs()->begin();
	while (current != neuron->getInputs()->end())
	{
		Sinapsis *sinapsis=*current;
		double xi=sinapsis->getStart()->getFired_output();
		double wi=sinapsis->getWeight();
		y_input+=xi*wi;
		current++;
	}

	neuron->setReceived_input(y_input);

	// Decide  qué dispara:
	neuron->setFired_output(bipolar_sigmoidal_transfer_function(y_input));

	//neuron->net->logger.fout<<neuron->name<<"_in"<<"="<<neuron->getReceived_input()<<endl;
	//neuron->net->logger.fout<<"F("<<neuron->name<<")="<<neuron->getFired_output()<<endl;
}