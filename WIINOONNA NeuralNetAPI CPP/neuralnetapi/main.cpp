/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

// Perceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NeuralNet.h"

#include "PatternCollection.h"

#include "Perceptron.h"
#include "PerceptronTransferFunction.h"
#include "PerceptronLearningFunction.h"
#include "PerceptronTrainingAlgorithm.h"
//#include "MadalineTransferFunction.h"
//#include "MadalineLearningFunction.h"
//#include "MadalineTrainingAlgorithm.h"
//#include "Madaline.h"


#include "ejemplos_perceptron.h"
#include "EjercicioPerceptronLeeLetras.h"

#include "Adaline.h"
#include "AdalineTrainingAlgorithm.h"
#include "ejemplos_adaline.h"
#include "ejemplos_perceptron.h"

#include "EjercicioAdalineLeeLetras.h"

#include "ejemplos_backpropagation.h"
#include "BackPropagationTransferFunction.h"
#include "BackPropagationLearningFunction.h"
#include "BackPropagationTrainingAlgorithm.h"
#include "BackPropagation.h"

#include "EjercicioBackPropagationLeeLetras.h"
#include <cmath>

/*
void show_outputs(Perceptron *perceptron)
{
	list<Neuron*> output_list=perceptron->output_layer->getNeuron_list();
	list<Neuron*>::iterator outputs=output_list.begin();
	while(outputs!=output_list.end())
	{
	 Neuron *neout=*outputs;
	 cout<<neout->getFired_output()<<" ";
	 outputs++;
	}
	cout<<endl;
}


void test_patterns()
{
	PatternCollection pcollection;

	pcollection.load("c:/alfabeto.dat");
	cout<<"loaded";
}*/



int main(int argc, char* argv[])
{
	//test_patterns();
	//perceptron_example_1output();
	//perceptron_example_2outputs();
	//EjercicioPerceptronLeeLetras ejercicio_letras_perceptron;
	//ejercicio_letras_perceptron.ejecuta();

	//adaline_example_1output();
	//adaline_example_2outputs();
	//EjercicioAdalineLeeLetras ejercicio_letras_adaline;
	//ejercicio_letras_adaline.ejecuta();
	//madaline_example_1output();

	//backpropagation_example_1output();
	//backpropagation_example_2outputs();
	
	//backpropagation_ejemplo_teoria();
	//EjercicioBackPropagationLeeLetras ejercicio_letras_backpropagation;
	//ejercicio_letras_backpropagation.ejecuta();


	//backpropagation_ejemplo_predice_secuencia_simple();
	//backpropagation_ejemplo_predice_seno();
	//backpropagation_ejemplo_seno_genera_graficas();

	backpropagation_train_for_example_series2();
	return 0;
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

// Perceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NeuralNet.h"

#include "PatternCollection.h"

#include "Perceptron.h"
#include "PerceptronTransferFunction.h"
#include "PerceptronLearningFunction.h"
#include "PerceptronTrainingAlgorithm.h"
//#include "MadalineTransferFunction.h"
//#include "MadalineLearningFunction.h"
//#include "MadalineTrainingAlgorithm.h"
//#include "Madaline.h"


#include "ejemplos_perceptron.h"
#include "EjercicioPerceptronLeeLetras.h"

#include "Adaline.h"
#include "AdalineTrainingAlgorithm.h"
#include "ejemplos_adaline.h"
#include "ejemplos_perceptron.h"

#include "EjercicioAdalineLeeLetras.h"

#include "ejemplos_backpropagation.h"
#include "BackPropagationTransferFunction.h"
#include "BackPropagationLearningFunction.h"
#include "BackPropagationTrainingAlgorithm.h"
#include "BackPropagation.h"

#include "EjercicioBackPropagationLeeLetras.h"
#include <cmath>

/*
void show_outputs(Perceptron *perceptron)
{
	list<Neuron*> output_list=perceptron->output_layer->getNeuron_list();
	list<Neuron*>::iterator outputs=output_list.begin();
	while(outputs!=output_list.end())
	{
	 Neuron *neout=*outputs;
	 cout<<neout->getFired_output()<<" ";
	 outputs++;
	}
	cout<<endl;
}


void test_patterns()
{
	PatternCollection pcollection;

	pcollection.load("c:/alfabeto.dat");
	cout<<"loaded";
}*/



int main(int argc, char* argv[])
{
	//test_patterns();
	//perceptron_example_1output();
	//perceptron_example_2outputs();
	//EjercicioPerceptronLeeLetras ejercicio_letras_perceptron;
	//ejercicio_letras_perceptron.ejecuta();

	//adaline_example_1output();
	//adaline_example_2outputs();
	//EjercicioAdalineLeeLetras ejercicio_letras_adaline;
	//ejercicio_letras_adaline.ejecuta();
	//madaline_example_1output();

	//backpropagation_example_1output();
	//backpropagation_example_2outputs();
	
	//backpropagation_ejemplo_teoria();
	//EjercicioBackPropagationLeeLetras ejercicio_letras_backpropagation;
	//ejercicio_letras_backpropagation.ejecuta();


	//backpropagation_ejemplo_predice_secuencia_simple();
	//backpropagation_ejemplo_predice_seno();
	//backpropagation_ejemplo_seno_genera_graficas();

	backpropagation_train_for_example_series2();
	return 0;
}

