/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Sinapsis.h"

int sinapsis_count=0;
Sinapsis::Sinapsis(void)
{
 	int i = sinapsis_count++;
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	this->name="S"+s;
	weight_update=0.0;
	weight=0.0;
}

Sinapsis::~Sinapsis(void)
{
	//cout<<"Sinapsis destructor called\n";
}


void Sinapsis::setStart(Neuron *n)
{
	start=n;
}

Neuron* Sinapsis::getStart()
{
	return start;
}


void Sinapsis::setEnd(Neuron *n)
{
	end=n;
}

Neuron* Sinapsis::getEnd()
{
	return end;
}

double Sinapsis::getWeight()
{
	return weight;
}

void Sinapsis::setWeight(double w)
{
	weight=w;
}

void Sinapsis::print()
{
	int start_index=this->getStart()->net->getNeuronIndex(this->getStart());
	int end_index=this->getEnd()->net->getNeuronIndex(this->getEnd());
	this->getStart()->net->logger.fout<<"Sinapsis("<<getStart()->name<<"->"<<
		getEnd()->name<<")["<<name<<":"<<start_index<<"->"<<end_index<<":w="<<this->getWeight()<<"]"<<endl;
}


void Sinapsis::setWeight_update(double value)
{
	weight_update=value;
}

double Sinapsis::getWeight_update()
{
	return weight_update;
}