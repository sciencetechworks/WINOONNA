/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "ejemplos_BackPropagation.h"




void backpropagation_example_1output()
{
	cout<<"BackPropagation EXAMPLE"<<endl;
	BackPropagation backpropagation(2,10,1);

	backpropagation.setLearningFactor(0.001);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.map_results_to_0_1=true;
	backpropagation.training_algorithm->setMax_epochs(40000);
	backpropagation.logger.disable();
	//BackPropagationTrainingAlgorithm *algo=(BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm;
    //algo->init_weights_to_random_values=false;
	
    //backpropagation.save("c:/xor241net.txt");
	
	//backpropagation.load("c:/xor241net_libro.txt");


	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	// OJO BackPropagation FUNCIONA SOLO CON TARGETS BIPOLARES

	/* -1 -1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	/* 1 -1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	
	/* 1 1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	

	//ENTRENAMIENTO
	double hitp=0.0;
	int veces=0;

	while((hitp!=1.0)&&(veces++<1000))
	{
	backpropagation.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.05);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
	}

	if (hitp==1.0)
	{
		cout<<"Grabando red neural con indice de aciertos 100% en c:/xornet.txt"<<endl;
		backpropagation.save("c:/xornet.txt");
	} else
	{
		cout<<"No se consiguio una red con indice de aciertos 100%"<<endl;
	}
}


void backpropagation_example_2outputs()
{
	cout<<"MULTIOUTPUT BackPropagation EXAMPLE"<<endl;
	BackPropagation BackPropagation(2,4,2);

	BackPropagation.setLearningFactor(0.01);
	BackPropagation.training_algorithm->setMax_epochs(500);
	
	BackPropagation.map_results_to_0_1=true;
	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	/* 1 1 -> -1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=-1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 -1 -> -1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 -1 -> 1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	//ENTRENAMIENTO
	BackPropagation.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=BackPropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.05);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
}

/**********************************************
**  EJEMPLOS PRACTICA 4
**
***********************************************/
double seno(double x)
{
	return sin(x);
}

double secuencia(double x)
{
	return x+1;
}

/*
Código de ejemplo de una red neural 4,20,1 que predice la secuencia simple.
*/
void backpropagation_ejemplo_predice_secuencia_simple()
{
	plot (&secuencia,-1,5,1,"c:/secuencia.txt");
	plot (&secuencia,3,6,1,"c:/target.txt");


	//plot(&seno,
	//	-2.0*PI,2.0*PI,0.05,"c:/sin.txt");
	
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/secuencia.txt",4,1);
	pcollection.print();

	PatternCollection targetcollection;
	targetcollection.generate_from_data("c:/target.txt",1,1);
	targetcollection.print();


	double maxvalue=0;
	double maxvalue_patterns=pcollection.getMaxValueInPatterns();
	double maxvalue_targets=targetcollection.getMaxValueInPatterns();
	if (maxvalue_patterns>maxvalue_targets)
		maxvalue=maxvalue_patterns;
	else
		maxvalue=maxvalue_targets;

	double normalization_value=maxvalue;

	pcollection.normalize(normalization_value);
	targetcollection.normalize(normalization_value);

	cout<<"Max Value in Patterns:"<<maxvalue<<endl;

	cout<<"Normalized"<<endl;
	pcollection.print();
	targetcollection.print();

	cout<<"BackPropagation EXAMPLE"<<endl;
	int n_hidden=20;

	BackPropagation backpropagation(4,n_hidden,1);

	backpropagation.setLearningFactor(1.0/n_hidden);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(1000000/n_hidden);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=targetcollection;

	backpropagation.training_algorithm->train();


	backpropagation.save("c:/secuencia_simple_net.txt");
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.1);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;

}



void backpropagation_ejemplo_predice_seno()
{
	plot (&seno,0,2.0*PI-0.1,0.01,"c:/seno.txt");
	plot (&seno,0+0.1,2.0*PI,0.1,"c:/target_seno.txt");


	//plot(&seno,
	//	-2.0*PI,2.0*PI,0.05,"c:/sin.txt");
	
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/seno.txt",10,10);
	pcollection.print();

	PatternCollection targetcollection;
	targetcollection.generate_from_data("c:/target_seno.txt",1,1);
	targetcollection.print();


	double maxvalue=0;
	double maxvalue_patterns=pcollection.getMaxValueInPatterns();
	double maxvalue_targets=targetcollection.getMaxValueInPatterns();
	if (maxvalue_patterns>maxvalue_targets)
		maxvalue=maxvalue_patterns;
	else
		maxvalue=maxvalue_targets;

	double normalization_value=maxvalue;

	pcollection.normalize(normalization_value);
	targetcollection.normalize(normalization_value);

	cout<<"Max Value in Patterns:"<<maxvalue<<endl;

	cout<<"Normalized"<<endl;
	pcollection.print();
	targetcollection.print();

	cout<<"BackPropagation EXAMPLE SIN  RUNNING"<<endl;
	int n_hidden=50;

	BackPropagation backpropagation(10,n_hidden,1);

	backpropagation.setLearningFactor(1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.003;
	
	backpropagation.training_algorithm->setMax_epochs(100000/n_hidden);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=targetcollection;

	backpropagation.training_algorithm->train();


	backpropagation.save("c:/seno_net.txt");
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
}

void backpropagation_ejemplo_seno_genera_graficas()
{
	int n_hidden=50;
	BackPropagation backpropagation(10,n_hidden,10);

	backpropagation.setLearningFactor(1.0/n_hidden);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.003;
	
	backpropagation.training_algorithm->setMax_epochs(1000000/n_hidden);
	backpropagation.logger.disable();
	backpropagation.load("c:/seno_net.txt");
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/seno.txt",10,1);
	//pcollection.print();

	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout;
	fout.open("c:/prediccion_seno.txt");
	double x=0.1;
	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		for (int k=0;k<1;k++)
		{
			cout<<x<<"\t"<<output->get(k)<<endl;
			fout<<x<<"\t"<<output->get(k)<<endl;
			x+=0.01;
		}
		delete output;
	}
	fout.close();
}


void backpropagation_ejemplo_teoria()
{
 BackPropagation backpropagation(2,2,1);
 backpropagation.setLearningFactor(0.25);
 backpropagation.training_algorithm->setMax_epochs(1);
 BackPropagationTrainingAlgorithm *algo=(BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm;
 algo->init_weights_to_random_values=false;

 Neuron *x1= backpropagation.getNeuron("X1");
 Neuron *x2= backpropagation.getNeuron("X2");
 Neuron *z1= backpropagation.getNeuron("Z1");
 Neuron *z2= backpropagation.getNeuron("Z2");
 Neuron *y1= backpropagation.getNeuron("Y1");

 Neuron *by1= backpropagation.getBias(y1);
 Neuron *bz1= backpropagation.getBias(z1);
 Neuron *bz2= backpropagation.getBias(z2);

 backpropagation.getSinapsis(by1,y1)->setWeight(-0.3);
 backpropagation.getSinapsis(bz1,z1)->setWeight(0.4);
 backpropagation.getSinapsis(bz2,z2)->setWeight(0.6);

 backpropagation.getSinapsis(z1,y1)->setWeight(0.5);
 backpropagation.getSinapsis(z2,y1)->setWeight(0.1);

 backpropagation.getSinapsis(x1,z1)->setWeight(0.7);
 backpropagation.getSinapsis(x1,z2)->setWeight(-0.4);

 backpropagation.getSinapsis(x2,z1)->setWeight(-0.2);
 backpropagation.getSinapsis(x2,z2)->setWeight(0.3);

 backpropagation.save("c:/bpnet.txt");

 //PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
 //AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
   Pattern *train_pattern,*target_pattern;
   double *train_pattern_data,*target_pattern_data;
	/* -1 1 -> 1 */
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	algo->training_patterns.add_pattern(train_pattern);

	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	algo->target_patterns.add_pattern(target_pattern);



    algo->train();

}



/***********************************************
* ENTRENAMIENTO DE LA RED BACKPROPAGATION
* PARA LAS SECUENCIAS DE LA PRACTICA 4
************************************************/
void backpropagation_train_for_example_series()
{
	Pattern *pattern;
	PatternCollection pcollection1,pcollection2,pcollection3,pcollection4,
		target_collection1,target_collection2,pcollection,target_collection;

	double pcol_normalizer1,pcol_normalizer2,pcol_normalizer3,pcol_normalizer4,
		t_normalizer1,t_normalizer2;

	// Creamos la colección de patrones de entrada con los valores a b c d
	pcollection1.generate_from_data("C:/Neuro/Practica4/series/serie1.dat",1,1);
	pcollection2.generate_from_data("C:/Neuro/Practica4/series/serie2.dat",1,1);
	pcollection3.generate_from_data("C:/Neuro/Practica4/series/serie3.dat",1,1);
	pcollection4.generate_from_data("C:/Neuro/Practica4/series/serie4.dat",1,1);


	pcol_normalizer1=pcollection1.getMaxValueInPatterns();
	pcol_normalizer2=pcollection2.getMaxValueInPatterns();
	pcol_normalizer3=pcollection3.getMaxValueInPatterns();
	pcol_normalizer4=pcollection4.getMaxValueInPatterns();
	
	pcollection1.normalize(pcol_normalizer1);
	pcollection2.normalize(pcol_normalizer2);
	pcollection3.normalize(pcol_normalizer3);
	pcollection4.normalize(pcol_normalizer4);

	
	double valor1=0.0,valor2=0.0,valor3=0.0,valor4=0.0;
	int posicion=0;
	#define RANGO_MIN 7322
	#define RANGO_MAX 8430
	#define RANGO_STEP 25


	list<Pattern*>::iterator p_iter1=pcollection1.patterns_list.begin();
	list<Pattern*>::iterator p_iter2=pcollection2.patterns_list.begin();
	list<Pattern*>::iterator p_iter3=pcollection3.patterns_list.begin();
	list<Pattern*>::iterator p_iter4=pcollection4.patterns_list.begin();

	while (p_iter1!=pcollection1.patterns_list.end())
	{
		Pattern *p1=*p_iter1++;
		Pattern *p2=*p_iter2++;
		Pattern *p3=*p_iter3++;
		Pattern *p4=*p_iter4++;

		if ((posicion>RANGO_MIN)&&(posicion<RANGO_MAX)&&(posicion%RANGO_STEP==0))
		{
	
		/* Creamos un patron con los valores a b c d de las series 1,2,3,4*/
		pattern=new Pattern(1,4);
		pattern->is_bipolar=true;
		pattern->set(0,p1->get(0));
		pattern->set(1,p2->get(0));
		pattern->set(2,p3->get(0));
		pattern->set(3,p4->get(0));
		pcollection.add_pattern(pattern);
		}		
		posicion++;
	}
	




	
	

	
	
	// Creamos la colección de patrones objetivo con los valores x e y
	target_collection1.generate_from_data("C:/Neuro/Practica4/series/serie5.dat",1,1);
	target_collection2.generate_from_data("C:/Neuro/Practica4/series/serie6.dat",1,1);

	t_normalizer1=target_collection1.getMaxValueInPatterns();
	t_normalizer2=target_collection2.getMaxValueInPatterns();

	
	target_collection1.normalize(t_normalizer1);
	target_collection2.normalize(t_normalizer2);



	list<Pattern*>::iterator t_iter1=target_collection1.patterns_list.begin();
	list<Pattern*>::iterator t_iter2=target_collection2.patterns_list.begin();
	posicion=0;
	while (t_iter1!=target_collection1.patterns_list.end())
	{
		Pattern *p1=*t_iter1++;
		Pattern *p2=*t_iter2++;
	
		if ((posicion>RANGO_MIN)&&(posicion<RANGO_MAX)&&(posicion%RANGO_STEP==0))
		{
		/* Creamos un patron con los valores x y de las series 5,6*/
		pattern=new Pattern(1,2);
		pattern->is_bipolar=true;
		pattern->set(0,p1->get(0));
		pattern->set(1,p2->get(0));
		target_collection.add_pattern(pattern);
		}		
		posicion++;
	}


	cout<<"BackPropagation TRAINING"<<endl;
	int n_hidden=50;

	BackPropagation backpropagation(4,n_hidden,2);

	backpropagation.setLearningFactor(0.08); //1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(20000);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=target_collection;

	/* RELOAD TO KEEP ON TRAINING */
	backpropagation.load("C:/Neuro/Practica4/series/predictor_net.txt");
	((BackPropagationTrainingAlgorithm*)(backpropagation.training_algorithm))->init_weights_to_random_values=false;
    /** **/
	
	backpropagation.training_algorithm->train();


	backpropagation.save("C:/Neuro/Practica4/series/predictor_net.txt");
	

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;


	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout1,fout2,fnorm1,fnorm2;
	fout1.open("C:/Neuro/Practica4/series/prediccion_serie5.dat");
	//fnorm1.open("C:/Neuro/Practica4/series/serie5_normalizada.dat");
	fout2.open("C:/Neuro/Practica4/series/prediccion_serie6.dat");
	//fnorm2.open("C:/Neuro/Practica4/series/serie6_normalizada.dat");
	list<Pattern*>::iterator target_iter=target_collection.patterns_list.begin();

	posicion=0;
	for (int i=0;i<RANGO_MIN;i++)
	{
	//	fout1<<posicion<<"\t"<<0.0<<endl;
	//	fnorm1<<posicion<<"\t"<<0.0<<endl;

		posicion++;
	}

	//cout<<"Normalizado:"<<t_normalizer1<<endl;
	

	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;
		Pattern *target=*target_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		

		double valor=output->get(0,0);
		valor*=t_normalizer1;
		fout1<<posicion<<"\t"<<valor<<endl;

		
		valor=output->get(0,1);
		valor*=t_normalizer2;
		fout2<<posicion<<"\t"<<valor<<endl;
		//cout<<"\tx:"<<valor;
		//fout2<<"\t"<<output->get(1)<<endl;
		
		//valor=target->get(0,0);
		//valor*=t_normalizer1;
		//fnorm1<<posicion<<"\t"<<valor<<endl;
		//cout<<"\texpected x:"<<valor<<endl;
		
		//fnorm2<<"\t"<<target->get(1)<<endl;

		while (posicion%RANGO_STEP!=0)
		{
			//fout1<<posicion<<"\t"<<0.0<<endl;
			//fnorm1<<posicion<<"\t"<<0.0<<endl;
			posicion++;
		}
		posicion++;

		delete output;
	}
	cout<<"FINISHED"<<endl;
	fout1.close();
	fout2.close();
	//fnorm1.close();
	exit(0);

}


/***********************************************
* ENTRENAMIENTO DE LA RED BACKPROPAGATION
* PARA LAS SECUENCIAS DE LA PRACTICA 4
************************************************/
void backpropagation_train_for_example_series2()
{
	Pattern *pattern;
	PatternCollection pcollection1,pcollection2,pcollection3,pcollection4,
		target_collection1,target_collection2,pcollection,target_collection;

	double pcol_normalizer1,pcol_normalizer2,pcol_normalizer3,pcol_normalizer4,
		t_normalizer1,t_normalizer2;

	// Creamos la colección de patrones de entrada con los valores a b c d
	pcollection1.generate_from_data("C:/Neuro/Practica4/series/serie1.dat",1,1);
	pcollection2.generate_from_data("C:/Neuro/Practica4/series/serie2.dat",1,1);
	pcollection3.generate_from_data("C:/Neuro/Practica4/series/serie3.dat",1,1);
	pcollection4.generate_from_data("C:/Neuro/Practica4/series/serie4.dat",1,1);


	pcol_normalizer1=pcollection1.getMaxValueInPatterns();
	pcol_normalizer2=pcollection2.getMaxValueInPatterns();
	pcol_normalizer3=pcollection3.getMaxValueInPatterns();
	pcol_normalizer4=pcollection4.getMaxValueInPatterns();
	
	pcollection1.normalize(pcol_normalizer1);
	pcollection2.normalize(pcol_normalizer2);
	pcollection3.normalize(pcol_normalizer3);
	pcollection4.normalize(pcol_normalizer4);

	// Creamos la colección de patrones objetivo con los valores x e y
	target_collection1.generate_from_data("C:/Neuro/Practica4/series/serie5.dat",1,1);
	target_collection2.generate_from_data("C:/Neuro/Practica4/series/serie6.dat",1,1);

	t_normalizer1=target_collection1.getMaxValueInPatterns();
	t_normalizer2=target_collection2.getMaxValueInPatterns();

	
	target_collection1.normalize(t_normalizer1);
	target_collection2.normalize(t_normalizer2);


	
	double valor1=0.0,valor2=0.0,valor3=0.0,valor4=0.0;
	int posicion=0;
	//#define RANGO_MIN 7322
	//#define RANGO_MAX 8430
	//#define NUM_INPUTS 20 
	//numero de entradas (x1,x2,x3,x4) que se inyectan en la entrada
	//por ejemplo: (x1,x2,x3,x4)(x1,x2,x3,x4)...(x1,x2,x3,x4)
	//(20 primeros patrones deben ofrecer la salida de la posicion 21
	// de (x5,x6) )

	#define NRANGO_MIN 100
	#define NRANGO_MAX 7000
	#define NNUM_INPUTS 100 



	list<Pattern*>::iterator p_iter1=pcollection1.patterns_list.begin();
	list<Pattern*>::iterator p_iter2=pcollection2.patterns_list.begin();
	list<Pattern*>::iterator p_iter3=pcollection3.patterns_list.begin();
	list<Pattern*>::iterator p_iter4=pcollection4.patterns_list.begin();
	list<Pattern*>::iterator t_iter1=target_collection1.patterns_list.begin();
	list<Pattern*>::iterator t_iter2=target_collection2.patterns_list.begin();




	while (p_iter1!=pcollection1.patterns_list.end())
	{

		
		if ((posicion>NRANGO_MIN)&&(posicion<NRANGO_MAX))
		{
		pattern=new Pattern(1,4*NNUM_INPUTS);
		pattern->is_bipolar=true;
		for (int i=0;i<NNUM_INPUTS;i++)
		{
		Pattern *p1=*p_iter1++;
		Pattern *p2=*p_iter2++;
		Pattern *p3=*p_iter3++;
		Pattern *p4=*p_iter4++;
		t_iter1++;
		t_iter2++;
		posicion++;
		/* Creamos un patron con los valores a b c d de las series 1,2,3,4*/
		
		pattern->set(0+4*i,p1->get(0));
		pattern->set(1+4*i,p2->get(0));
		pattern->set(2+4*i,p3->get(0));
		pattern->set(3+4*i,p4->get(0));
		}
		pcollection.add_pattern(pattern);

		// Para esa entrada generamos el target de la posicion siguiente
		/* Creamos un patron con los valores x y de las series 5,6*/
		Pattern *t1=*t_iter1;
		Pattern *t2=*t_iter2;
		Pattern *t_pattern=new Pattern(1,2);
		t_pattern->is_bipolar=true;
		t_pattern->set(0,t1->get(0));
		t_pattern->set(1,t2->get(0));
		target_collection.add_pattern(pattern);

		} else
		{
			p_iter1++;
			p_iter2++;
			p_iter3++;
			p_iter4++;
			t_iter1++;
			t_iter2++;
			posicion++;
		}
		
	}
	

	cout<<"BackPropagation TRAINING"<<endl;
	int n_hidden=100;

	BackPropagation backpropagation(4*NNUM_INPUTS,n_hidden,2);

	backpropagation.setLearningFactor(0.01); //1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(10000);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=target_collection;

	/* RELOAD TO KEEP ON TRAINING */
	//backpropagation.load("C:/Neuro/Practica4/series/predictor_net.txt");
	//((BackPropagationTrainingAlgorithm*)(backpropagation.training_algorithm))->init_weights_to_random_values=false;
    /** **/
	
	backpropagation.training_algorithm->train();


	backpropagation.save("C:/Neuro/Practica4/series/predictor_net.txt");
	

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;


	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout1,fout2,fnorm1,fnorm2;
	fout1.open("C:/Neuro/Practica4/series/prediccion_serie5.dat");
	//fnorm1.open("C:/Neuro/Practica4/series/serie5_normalizada.dat");
	fout2.open("C:/Neuro/Practica4/series/prediccion_serie6.dat");
	//fnorm2.open("C:/Neuro/Practica4/series/serie6_normalizada.dat");
	list<Pattern*>::iterator target_iter=target_collection.patterns_list.begin();

	posicion=0;
	for (int i=0;i<NRANGO_MIN;i++)
	{
	//	fout1<<posicion<<"\t"<<0.0<<endl;
	//	fnorm1<<posicion<<"\t"<<0.0<<endl;

		posicion++;
	}

	//cout<<"Normalizado:"<<t_normalizer1<<endl;
	

	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;
		Pattern *target=*target_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		

		double valor=output->get(0,0);
		valor*=t_normalizer1;
		fout1<<posicion<<"\t"<<valor<<endl;

		
		valor=output->get(0,1);
		valor*=t_normalizer2;
		fout2<<posicion<<"\t"<<valor<<endl;
		
		posicion+=NNUM_INPUTS;

		delete output;
	}
	cout<<"FINISHED"<<endl;
	fout1.close();
	fout2.close();
	exit(0);

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

#include "ejemplos_BackPropagation.h"




void backpropagation_example_1output()
{
	cout<<"BackPropagation EXAMPLE"<<endl;
	BackPropagation backpropagation(2,10,1);

	backpropagation.setLearningFactor(0.001);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.map_results_to_0_1=true;
	backpropagation.training_algorithm->setMax_epochs(40000);
	backpropagation.logger.disable();
	//BackPropagationTrainingAlgorithm *algo=(BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm;
    //algo->init_weights_to_random_values=false;
	
    //backpropagation.save("c:/xor241net.txt");
	
	//backpropagation.load("c:/xor241net_libro.txt");


	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	// OJO BackPropagation FUNCIONA SOLO CON TARGETS BIPOLARES

	/* -1 -1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	/* 1 -1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	
	/* 1 1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	backpropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	backpropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	

	//ENTRENAMIENTO
	double hitp=0.0;
	int veces=0;

	while((hitp!=1.0)&&(veces++<1000))
	{
	backpropagation.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.05);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
	}

	if (hitp==1.0)
	{
		cout<<"Grabando red neural con indice de aciertos 100% en c:/xornet.txt"<<endl;
		backpropagation.save("c:/xornet.txt");
	} else
	{
		cout<<"No se consiguio una red con indice de aciertos 100%"<<endl;
	}
}


void backpropagation_example_2outputs()
{
	cout<<"MULTIOUTPUT BackPropagation EXAMPLE"<<endl;
	BackPropagation BackPropagation(2,4,2);

	BackPropagation.setLearningFactor(0.01);
	BackPropagation.training_algorithm->setMax_epochs(500);
	
	BackPropagation.map_results_to_0_1=true;
	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	/* 1 1 -> -1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=-1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 -1 -> -1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 -1 -> 1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	BackPropagation.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=1.0;
	target_pattern->set(target_pattern_data,2);	
	BackPropagation.training_algorithm->target_patterns.add_pattern(target_pattern);


	//ENTRENAMIENTO
	BackPropagation.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=BackPropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.05);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
}

/**********************************************
**  EJEMPLOS PRACTICA 4
**
***********************************************/
double seno(double x)
{
	return sin(x);
}

double secuencia(double x)
{
	return x+1;
}

/*
Código de ejemplo de una red neural 4,20,1 que predice la secuencia simple.
*/
void backpropagation_ejemplo_predice_secuencia_simple()
{
	plot (&secuencia,-1,5,1,"c:/secuencia.txt");
	plot (&secuencia,3,6,1,"c:/target.txt");


	//plot(&seno,
	//	-2.0*PI,2.0*PI,0.05,"c:/sin.txt");
	
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/secuencia.txt",4,1);
	pcollection.print();

	PatternCollection targetcollection;
	targetcollection.generate_from_data("c:/target.txt",1,1);
	targetcollection.print();


	double maxvalue=0;
	double maxvalue_patterns=pcollection.getMaxValueInPatterns();
	double maxvalue_targets=targetcollection.getMaxValueInPatterns();
	if (maxvalue_patterns>maxvalue_targets)
		maxvalue=maxvalue_patterns;
	else
		maxvalue=maxvalue_targets;

	double normalization_value=maxvalue;

	pcollection.normalize(normalization_value);
	targetcollection.normalize(normalization_value);

	cout<<"Max Value in Patterns:"<<maxvalue<<endl;

	cout<<"Normalized"<<endl;
	pcollection.print();
	targetcollection.print();

	cout<<"BackPropagation EXAMPLE"<<endl;
	int n_hidden=20;

	BackPropagation backpropagation(4,n_hidden,1);

	backpropagation.setLearningFactor(1.0/n_hidden);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(1000000/n_hidden);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=targetcollection;

	backpropagation.training_algorithm->train();


	backpropagation.save("c:/secuencia_simple_net.txt");
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.1);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;

}



void backpropagation_ejemplo_predice_seno()
{
	plot (&seno,0,2.0*PI-0.1,0.01,"c:/seno.txt");
	plot (&seno,0+0.1,2.0*PI,0.1,"c:/target_seno.txt");


	//plot(&seno,
	//	-2.0*PI,2.0*PI,0.05,"c:/sin.txt");
	
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/seno.txt",10,10);
	pcollection.print();

	PatternCollection targetcollection;
	targetcollection.generate_from_data("c:/target_seno.txt",1,1);
	targetcollection.print();


	double maxvalue=0;
	double maxvalue_patterns=pcollection.getMaxValueInPatterns();
	double maxvalue_targets=targetcollection.getMaxValueInPatterns();
	if (maxvalue_patterns>maxvalue_targets)
		maxvalue=maxvalue_patterns;
	else
		maxvalue=maxvalue_targets;

	double normalization_value=maxvalue;

	pcollection.normalize(normalization_value);
	targetcollection.normalize(normalization_value);

	cout<<"Max Value in Patterns:"<<maxvalue<<endl;

	cout<<"Normalized"<<endl;
	pcollection.print();
	targetcollection.print();

	cout<<"BackPropagation EXAMPLE SIN  RUNNING"<<endl;
	int n_hidden=50;

	BackPropagation backpropagation(10,n_hidden,1);

	backpropagation.setLearningFactor(1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.003;
	
	backpropagation.training_algorithm->setMax_epochs(100000/n_hidden);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=targetcollection;

	backpropagation.training_algorithm->train();


	backpropagation.save("c:/seno_net.txt");
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
}

void backpropagation_ejemplo_seno_genera_graficas()
{
	int n_hidden=50;
	BackPropagation backpropagation(10,n_hidden,10);

	backpropagation.setLearningFactor(1.0/n_hidden);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.003;
	
	backpropagation.training_algorithm->setMax_epochs(1000000/n_hidden);
	backpropagation.logger.disable();
	backpropagation.load("c:/seno_net.txt");
	PatternCollection pcollection;

	//pcollection.generate_from_data("c:/sin.txt",3,1);

	pcollection.generate_from_data("c:/seno.txt",10,1);
	//pcollection.print();

	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout;
	fout.open("c:/prediccion_seno.txt");
	double x=0.1;
	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		for (int k=0;k<1;k++)
		{
			cout<<x<<"\t"<<output->get(k)<<endl;
			fout<<x<<"\t"<<output->get(k)<<endl;
			x+=0.01;
		}
		delete output;
	}
	fout.close();
}


void backpropagation_ejemplo_teoria()
{
 BackPropagation backpropagation(2,2,1);
 backpropagation.setLearningFactor(0.25);
 backpropagation.training_algorithm->setMax_epochs(1);
 BackPropagationTrainingAlgorithm *algo=(BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm;
 algo->init_weights_to_random_values=false;

 Neuron *x1= backpropagation.getNeuron("X1");
 Neuron *x2= backpropagation.getNeuron("X2");
 Neuron *z1= backpropagation.getNeuron("Z1");
 Neuron *z2= backpropagation.getNeuron("Z2");
 Neuron *y1= backpropagation.getNeuron("Y1");

 Neuron *by1= backpropagation.getBias(y1);
 Neuron *bz1= backpropagation.getBias(z1);
 Neuron *bz2= backpropagation.getBias(z2);

 backpropagation.getSinapsis(by1,y1)->setWeight(-0.3);
 backpropagation.getSinapsis(bz1,z1)->setWeight(0.4);
 backpropagation.getSinapsis(bz2,z2)->setWeight(0.6);

 backpropagation.getSinapsis(z1,y1)->setWeight(0.5);
 backpropagation.getSinapsis(z2,y1)->setWeight(0.1);

 backpropagation.getSinapsis(x1,z1)->setWeight(0.7);
 backpropagation.getSinapsis(x1,z2)->setWeight(-0.4);

 backpropagation.getSinapsis(x2,z1)->setWeight(-0.2);
 backpropagation.getSinapsis(x2,z2)->setWeight(0.3);

 backpropagation.save("c:/bpnet.txt");

 //PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
 //AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
   Pattern *train_pattern,*target_pattern;
   double *train_pattern_data,*target_pattern_data;
	/* -1 1 -> 1 */
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	algo->training_patterns.add_pattern(train_pattern);

	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	algo->target_patterns.add_pattern(target_pattern);



    algo->train();

}



/***********************************************
* ENTRENAMIENTO DE LA RED BACKPROPAGATION
* PARA LAS SECUENCIAS DE LA PRACTICA 4
************************************************/
void backpropagation_train_for_example_series()
{
	Pattern *pattern;
	PatternCollection pcollection1,pcollection2,pcollection3,pcollection4,
		target_collection1,target_collection2,pcollection,target_collection;

	double pcol_normalizer1,pcol_normalizer2,pcol_normalizer3,pcol_normalizer4,
		t_normalizer1,t_normalizer2;

	// Creamos la colección de patrones de entrada con los valores a b c d
	pcollection1.generate_from_data("C:/Neuro/Practica4/series/serie1.dat",1,1);
	pcollection2.generate_from_data("C:/Neuro/Practica4/series/serie2.dat",1,1);
	pcollection3.generate_from_data("C:/Neuro/Practica4/series/serie3.dat",1,1);
	pcollection4.generate_from_data("C:/Neuro/Practica4/series/serie4.dat",1,1);


	pcol_normalizer1=pcollection1.getMaxValueInPatterns();
	pcol_normalizer2=pcollection2.getMaxValueInPatterns();
	pcol_normalizer3=pcollection3.getMaxValueInPatterns();
	pcol_normalizer4=pcollection4.getMaxValueInPatterns();
	
	pcollection1.normalize(pcol_normalizer1);
	pcollection2.normalize(pcol_normalizer2);
	pcollection3.normalize(pcol_normalizer3);
	pcollection4.normalize(pcol_normalizer4);

	
	double valor1=0.0,valor2=0.0,valor3=0.0,valor4=0.0;
	int posicion=0;
	#define RANGO_MIN 7322
	#define RANGO_MAX 8430
	#define RANGO_STEP 25


	list<Pattern*>::iterator p_iter1=pcollection1.patterns_list.begin();
	list<Pattern*>::iterator p_iter2=pcollection2.patterns_list.begin();
	list<Pattern*>::iterator p_iter3=pcollection3.patterns_list.begin();
	list<Pattern*>::iterator p_iter4=pcollection4.patterns_list.begin();

	while (p_iter1!=pcollection1.patterns_list.end())
	{
		Pattern *p1=*p_iter1++;
		Pattern *p2=*p_iter2++;
		Pattern *p3=*p_iter3++;
		Pattern *p4=*p_iter4++;

		if ((posicion>RANGO_MIN)&&(posicion<RANGO_MAX)&&(posicion%RANGO_STEP==0))
		{
	
		/* Creamos un patron con los valores a b c d de las series 1,2,3,4*/
		pattern=new Pattern(1,4);
		pattern->is_bipolar=true;
		pattern->set(0,p1->get(0));
		pattern->set(1,p2->get(0));
		pattern->set(2,p3->get(0));
		pattern->set(3,p4->get(0));
		pcollection.add_pattern(pattern);
		}		
		posicion++;
	}
	




	
	

	
	
	// Creamos la colección de patrones objetivo con los valores x e y
	target_collection1.generate_from_data("C:/Neuro/Practica4/series/serie5.dat",1,1);
	target_collection2.generate_from_data("C:/Neuro/Practica4/series/serie6.dat",1,1);

	t_normalizer1=target_collection1.getMaxValueInPatterns();
	t_normalizer2=target_collection2.getMaxValueInPatterns();

	
	target_collection1.normalize(t_normalizer1);
	target_collection2.normalize(t_normalizer2);



	list<Pattern*>::iterator t_iter1=target_collection1.patterns_list.begin();
	list<Pattern*>::iterator t_iter2=target_collection2.patterns_list.begin();
	posicion=0;
	while (t_iter1!=target_collection1.patterns_list.end())
	{
		Pattern *p1=*t_iter1++;
		Pattern *p2=*t_iter2++;
	
		if ((posicion>RANGO_MIN)&&(posicion<RANGO_MAX)&&(posicion%RANGO_STEP==0))
		{
		/* Creamos un patron con los valores x y de las series 5,6*/
		pattern=new Pattern(1,2);
		pattern->is_bipolar=true;
		pattern->set(0,p1->get(0));
		pattern->set(1,p2->get(0));
		target_collection.add_pattern(pattern);
		}		
		posicion++;
	}


	cout<<"BackPropagation TRAINING"<<endl;
	int n_hidden=50;

	BackPropagation backpropagation(4,n_hidden,2);

	backpropagation.setLearningFactor(0.08); //1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(20000);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=target_collection;

	/* RELOAD TO KEEP ON TRAINING */
	backpropagation.load("C:/Neuro/Practica4/series/predictor_net.txt");
	((BackPropagationTrainingAlgorithm*)(backpropagation.training_algorithm))->init_weights_to_random_values=false;
    /** **/
	
	backpropagation.training_algorithm->train();


	backpropagation.save("C:/Neuro/Practica4/series/predictor_net.txt");
	

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;


	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout1,fout2,fnorm1,fnorm2;
	fout1.open("C:/Neuro/Practica4/series/prediccion_serie5.dat");
	//fnorm1.open("C:/Neuro/Practica4/series/serie5_normalizada.dat");
	fout2.open("C:/Neuro/Practica4/series/prediccion_serie6.dat");
	//fnorm2.open("C:/Neuro/Practica4/series/serie6_normalizada.dat");
	list<Pattern*>::iterator target_iter=target_collection.patterns_list.begin();

	posicion=0;
	for (int i=0;i<RANGO_MIN;i++)
	{
	//	fout1<<posicion<<"\t"<<0.0<<endl;
	//	fnorm1<<posicion<<"\t"<<0.0<<endl;

		posicion++;
	}

	//cout<<"Normalizado:"<<t_normalizer1<<endl;
	

	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;
		Pattern *target=*target_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		

		double valor=output->get(0,0);
		valor*=t_normalizer1;
		fout1<<posicion<<"\t"<<valor<<endl;

		
		valor=output->get(0,1);
		valor*=t_normalizer2;
		fout2<<posicion<<"\t"<<valor<<endl;
		//cout<<"\tx:"<<valor;
		//fout2<<"\t"<<output->get(1)<<endl;
		
		//valor=target->get(0,0);
		//valor*=t_normalizer1;
		//fnorm1<<posicion<<"\t"<<valor<<endl;
		//cout<<"\texpected x:"<<valor<<endl;
		
		//fnorm2<<"\t"<<target->get(1)<<endl;

		while (posicion%RANGO_STEP!=0)
		{
			//fout1<<posicion<<"\t"<<0.0<<endl;
			//fnorm1<<posicion<<"\t"<<0.0<<endl;
			posicion++;
		}
		posicion++;

		delete output;
	}
	cout<<"FINISHED"<<endl;
	fout1.close();
	fout2.close();
	//fnorm1.close();
	exit(0);

}


/***********************************************
* ENTRENAMIENTO DE LA RED BACKPROPAGATION
* PARA LAS SECUENCIAS DE LA PRACTICA 4
************************************************/
void backpropagation_train_for_example_series2()
{
	Pattern *pattern;
	PatternCollection pcollection1,pcollection2,pcollection3,pcollection4,
		target_collection1,target_collection2,pcollection,target_collection;

	double pcol_normalizer1,pcol_normalizer2,pcol_normalizer3,pcol_normalizer4,
		t_normalizer1,t_normalizer2;

	// Creamos la colección de patrones de entrada con los valores a b c d
	pcollection1.generate_from_data("C:/Neuro/Practica4/series/serie1.dat",1,1);
	pcollection2.generate_from_data("C:/Neuro/Practica4/series/serie2.dat",1,1);
	pcollection3.generate_from_data("C:/Neuro/Practica4/series/serie3.dat",1,1);
	pcollection4.generate_from_data("C:/Neuro/Practica4/series/serie4.dat",1,1);


	pcol_normalizer1=pcollection1.getMaxValueInPatterns();
	pcol_normalizer2=pcollection2.getMaxValueInPatterns();
	pcol_normalizer3=pcollection3.getMaxValueInPatterns();
	pcol_normalizer4=pcollection4.getMaxValueInPatterns();
	
	pcollection1.normalize(pcol_normalizer1);
	pcollection2.normalize(pcol_normalizer2);
	pcollection3.normalize(pcol_normalizer3);
	pcollection4.normalize(pcol_normalizer4);

	// Creamos la colección de patrones objetivo con los valores x e y
	target_collection1.generate_from_data("C:/Neuro/Practica4/series/serie5.dat",1,1);
	target_collection2.generate_from_data("C:/Neuro/Practica4/series/serie6.dat",1,1);

	t_normalizer1=target_collection1.getMaxValueInPatterns();
	t_normalizer2=target_collection2.getMaxValueInPatterns();

	
	target_collection1.normalize(t_normalizer1);
	target_collection2.normalize(t_normalizer2);


	
	double valor1=0.0,valor2=0.0,valor3=0.0,valor4=0.0;
	int posicion=0;
	//#define RANGO_MIN 7322
	//#define RANGO_MAX 8430
	//#define NUM_INPUTS 20 
	//numero de entradas (x1,x2,x3,x4) que se inyectan en la entrada
	//por ejemplo: (x1,x2,x3,x4)(x1,x2,x3,x4)...(x1,x2,x3,x4)
	//(20 primeros patrones deben ofrecer la salida de la posicion 21
	// de (x5,x6) )

	#define NRANGO_MIN 100
	#define NRANGO_MAX 7000
	#define NNUM_INPUTS 100 



	list<Pattern*>::iterator p_iter1=pcollection1.patterns_list.begin();
	list<Pattern*>::iterator p_iter2=pcollection2.patterns_list.begin();
	list<Pattern*>::iterator p_iter3=pcollection3.patterns_list.begin();
	list<Pattern*>::iterator p_iter4=pcollection4.patterns_list.begin();
	list<Pattern*>::iterator t_iter1=target_collection1.patterns_list.begin();
	list<Pattern*>::iterator t_iter2=target_collection2.patterns_list.begin();




	while (p_iter1!=pcollection1.patterns_list.end())
	{

		
		if ((posicion>NRANGO_MIN)&&(posicion<NRANGO_MAX))
		{
		pattern=new Pattern(1,4*NNUM_INPUTS);
		pattern->is_bipolar=true;
		for (int i=0;i<NNUM_INPUTS;i++)
		{
		Pattern *p1=*p_iter1++;
		Pattern *p2=*p_iter2++;
		Pattern *p3=*p_iter3++;
		Pattern *p4=*p_iter4++;
		t_iter1++;
		t_iter2++;
		posicion++;
		/* Creamos un patron con los valores a b c d de las series 1,2,3,4*/
		
		pattern->set(0+4*i,p1->get(0));
		pattern->set(1+4*i,p2->get(0));
		pattern->set(2+4*i,p3->get(0));
		pattern->set(3+4*i,p4->get(0));
		}
		pcollection.add_pattern(pattern);

		// Para esa entrada generamos el target de la posicion siguiente
		/* Creamos un patron con los valores x y de las series 5,6*/
		Pattern *t1=*t_iter1;
		Pattern *t2=*t_iter2;
		Pattern *t_pattern=new Pattern(1,2);
		t_pattern->is_bipolar=true;
		t_pattern->set(0,t1->get(0));
		t_pattern->set(1,t2->get(0));
		target_collection.add_pattern(pattern);

		} else
		{
			p_iter1++;
			p_iter2++;
			p_iter3++;
			p_iter4++;
			t_iter1++;
			t_iter2++;
			posicion++;
		}
		
	}
	

	cout<<"BackPropagation TRAINING"<<endl;
	int n_hidden=100;

	BackPropagation backpropagation(4*NNUM_INPUTS,n_hidden,2);

	backpropagation.setLearningFactor(0.01); //1.0/(n_hidden));
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.0005;
	
	backpropagation.training_algorithm->setMax_epochs(10000);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->training_patterns=pcollection;
	backpropagation.training_algorithm->target_patterns=target_collection;

	/* RELOAD TO KEEP ON TRAINING */
	//backpropagation.load("C:/Neuro/Practica4/series/predictor_net.txt");
	//((BackPropagationTrainingAlgorithm*)(backpropagation.training_algorithm))->init_weights_to_random_values=false;
    /** **/
	
	backpropagation.training_algorithm->train();


	backpropagation.save("C:/Neuro/Practica4/series/predictor_net.txt");
	

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(0,0.08);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;


	list<Pattern*>::iterator input_iter=pcollection.patterns_list.begin();
	ofstream fout1,fout2,fnorm1,fnorm2;
	fout1.open("C:/Neuro/Practica4/series/prediccion_serie5.dat");
	//fnorm1.open("C:/Neuro/Practica4/series/serie5_normalizada.dat");
	fout2.open("C:/Neuro/Practica4/series/prediccion_serie6.dat");
	//fnorm2.open("C:/Neuro/Practica4/series/serie6_normalizada.dat");
	list<Pattern*>::iterator target_iter=target_collection.patterns_list.begin();

	posicion=0;
	for (int i=0;i<NRANGO_MIN;i++)
	{
	//	fout1<<posicion<<"\t"<<0.0<<endl;
	//	fnorm1<<posicion<<"\t"<<0.0<<endl;

		posicion++;
	}

	//cout<<"Normalizado:"<<t_normalizer1<<endl;
	

	while (input_iter!=pcollection.patterns_list.end())
	{
		Pattern *pattern=*input_iter++;
		Pattern *target=*target_iter++;

		backpropagation.setInput(pattern);

		backpropagation.predict();

		Pattern *output=backpropagation.getOutput(1,1);
		

		double valor=output->get(0,0);
		valor*=t_normalizer1;
		fout1<<posicion<<"\t"<<valor<<endl;

		
		valor=output->get(0,1);
		valor*=t_normalizer2;
		fout2<<posicion<<"\t"<<valor<<endl;
		
		posicion+=NNUM_INPUTS;

		delete output;
	}
	cout<<"FINISHED"<<endl;
	fout1.close();
	fout2.close();
	exit(0);

}


