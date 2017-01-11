/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Neuron.h"


int neuron_count=0;
Neuron::Neuron(void)
{
	this->received_input=0.0;
	this->fired_output=0.0;
	this->commited_error=0.0;
	int i = neuron_count++;
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	this->name="N"+s;
	is_bias=false;
}

Neuron::~Neuron(void)
{
	//cout<<"Neuron destructor called\n";
}


list<Sinapsis*> *Neuron::getInputs()
{
	return &inputs;
}
list<Sinapsis*> *Neuron::getOutputs()
{
	return &outputs;
}

void Neuron::print()
{
	net->logger.fout<<"Neuron ["<<name<<":"<<this->net->getNeuronIndex(this)<<"]("<<this->received_input<<","<<fired_output<<")"<<endl;
}

double Neuron::getFired_output()
{
	return fired_output;
}

void Neuron::setFired_output(double value)
{
	fired_output=value;
}

Layer *Neuron::getLayer()
{
	return layer;
}

void Neuron::setLayer(Layer *layer)
{
	this->layer=layer;
}

double Neuron::getReceived_input()
{
	return received_input;
}

void Neuron::setReceived_input(double value)
{
	received_input=value;
}


void Neuron::setCommited_error(double value)
{
	commited_error=value;
}

double Neuron::getCommited_error()
{
	return commited_error;
}
