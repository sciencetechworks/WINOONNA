/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "ejemplos_perceptron.h"

void perceptron_example_1output()
{
	cout<<"PERCEPTRON EXAMPLE"<<endl;
	Perceptron perceptron(2,1);

	perceptron.setThreshold(0.2);
	perceptron.setLearning_factor(1);
	perceptron.training_algorithm->setMax_epochs(20);


	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	/* 1 1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 0 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=0.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 0 1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=0.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 0 0 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=0.0;
	train_pattern_data[1]=0.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	//ENTRENAMIENTO
	perceptron.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=perceptron.training_algorithm->calculate_hit_ratio_after_training(0,0.0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;

}


void perceptron_example_2outputs()
{
	cout<<"MULTIOUTPUT PERCEPTRON EXAMPLE"<<endl;
	Perceptron perceptron(2,2);
	perceptron.setThreshold(0.2);
	perceptron.setLearning_factor(1);
	
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
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=-1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 -1 -> -1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 -1 -> 1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);


	//ENTRENAMIENTO
	perceptron.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=perceptron.training_algorithm->calculate_hit_ratio_after_training(0,0.0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
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

#include "ejemplos_perceptron.h"

void perceptron_example_1output()
{
	cout<<"PERCEPTRON EXAMPLE"<<endl;
	Perceptron perceptron(2,1);

	perceptron.setThreshold(0.2);
	perceptron.setLearning_factor(1);
	perceptron.training_algorithm->setMax_epochs(20);


	//PREPARAMOS LOS VECTORES DE ENTRENAMIENTO
	//AND ENTRADAS BINARIAS OBJETIVOS BIPOLARES
    Pattern *train_pattern,*target_pattern;
	double *train_pattern_data,*target_pattern_data;
	/* 1 1 -> 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 0 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=0.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 0 1 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=0.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 0 0 -> -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=false;
    train_pattern_data=new double[2];
	train_pattern_data[0]=0.0;
	train_pattern_data[1]=0.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[1];
	target_pattern_data[0]=-1.0;
	target_pattern->set(target_pattern_data,1);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	//ENTRENAMIENTO
	perceptron.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=perceptron.training_algorithm->calculate_hit_ratio_after_training(0,0.0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;

}


void perceptron_example_2outputs()
{
	cout<<"MULTIOUTPUT PERCEPTRON EXAMPLE"<<endl;
	Perceptron perceptron(2,2);
	perceptron.setThreshold(0.2);
	perceptron.setLearning_factor(1);
	
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
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=-1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 1 -> 1 -1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* 1 -1 -> -1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=-1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);

	/* -1 -1 -> 1 1*/
    train_pattern=new Pattern();
	train_pattern->is_bipolar=true;
    train_pattern_data=new double[2];
	train_pattern_data[0]=-1.0;
	train_pattern_data[1]=-1.0;
	train_pattern->set(train_pattern_data,2);
	perceptron.training_algorithm->training_patterns.add_pattern(train_pattern);
	
	target_pattern=new Pattern();
	target_pattern->is_bipolar=true;
    target_pattern_data=new double[2];
	target_pattern_data[0]=1.0;
	target_pattern_data[1]=1.0;
	target_pattern->set(target_pattern_data,2);	
	perceptron.training_algorithm->target_patterns.add_pattern(target_pattern);


	//ENTRENAMIENTO
	perceptron.training_algorithm->train();

	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=perceptron.training_algorithm->calculate_hit_ratio_after_training(0,0.0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;
}
