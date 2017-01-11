/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "EjercicioAdalineLeeLetras.h"

EjercicioAdalineLeeLetras::EjercicioAdalineLeeLetras(void)
{
}

EjercicioAdalineLeeLetras::~EjercicioAdalineLeeLetras(void)
{
}



void EjercicioAdalineLeeLetras::ejecuta()
{
	//Creamos un adaline de 35 entradas y 5 salidas
	Adaline adaline=Adaline(35,35);
	// Ajustamos umbral, factor de aprendizaje y 
	// máximo número de épocas a ejecutar.
	adaline.setLearning_factor(0.1/100.0);
	adaline.training_algorithm->setMax_epochs(40000);
	((AdalineTrainingAlgorithm*)(adaline.training_algorithm))->setObjective_min_error(1);
	((AdalineTrainingAlgorithm*)(adaline.training_algorithm))->setObjective_min_weight_variation(1/100000.0);


	//Cargamos fichero de patrones de letras:
	cout<<"Cargando patrones de letras"<<endl;
	adaline.training_algorithm->training_patterns.load("c:/alfabeto.dat");
	//adaline.training_algorithm->target_patterns.load("c:/asignacion_letras.dat");
	adaline.training_algorithm->target_patterns.load("c:/alfabeto.dat");
	adaline.training_algorithm->training_patterns.convert_all_patterns_to_bipolar();
	adaline.training_algorithm->target_patterns.convert_all_patterns_to_bipolar();

	//
	cout<<"Usaremos como target el mismo patron que la entrada"<<
		endl<<"es decir entrenaremos la red para que encuentre similitudes"<<
		endl<<"entre una letra y si misma."<<endl;

	cout<<"antes de entrenar cambiamos a codificacion bipolar los patrones de entrada."<<endl;

	cout<<"Lanzamos entrenamiento, ver log de salida."<<endl;
	//ENTRENAMIENTO
	adaline.training_algorithm->train();

	adaline.save("c:/Adaline_LeeletrasLimpias.xml");

	/*if (adaline.load("c:/Adaline_LeeletrasLimpias.xml")==false)
	{
		cout<<"No se pudo cargar el fichero de la red neural."<<endl;
		exit(-1);
	}*/

	cout<<"Para evitar tener que entrenar la red una y otra vez la guardamos"<<
	endl<<"en un archivo, la cargamos ahora."<<endl;
/*
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=adaline.training_algorithm->calculate_hit_ratio_after_training(0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;*/

	cout<<"Vamos a ir subiendo el nivel de ruido de 0 a 30% y a apuntar el error cometido"<<
		endl<<"de esa manera veremos cómo reacciona el adaline a los patrones ruidosos"<<endl;

	ofstream fout;
	cout<<"Generando puntos RUIDO HITS"<<endl;
	fout.open("c:/GraficaAdalineRuido.dat");
	if (fout==NULL)
	{
		cout<<"error en creación de fichero, compruebe path"<<endl;
		return;
	}

	//fout<<"R	H"<<endl;
	for (int r=0;r<=30;r++)
	{
	double hitp=adaline.training_algorithm->calculate_hit_ratio_after_training(r,0.0);
	fout<<r<<"	"<<(hitp*100.0)<<"	"<<endl;
	}

	fout.close();

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

#include "EjercicioAdalineLeeLetras.h"

EjercicioAdalineLeeLetras::EjercicioAdalineLeeLetras(void)
{
}

EjercicioAdalineLeeLetras::~EjercicioAdalineLeeLetras(void)
{
}



void EjercicioAdalineLeeLetras::ejecuta()
{
	//Creamos un adaline de 35 entradas y 5 salidas
	Adaline adaline=Adaline(35,35);
	// Ajustamos umbral, factor de aprendizaje y 
	// máximo número de épocas a ejecutar.
	adaline.setLearning_factor(0.1/100.0);
	adaline.training_algorithm->setMax_epochs(40000);
	((AdalineTrainingAlgorithm*)(adaline.training_algorithm))->setObjective_min_error(1);
	((AdalineTrainingAlgorithm*)(adaline.training_algorithm))->setObjective_min_weight_variation(1/100000.0);


	//Cargamos fichero de patrones de letras:
	cout<<"Cargando patrones de letras"<<endl;
	adaline.training_algorithm->training_patterns.load("c:/alfabeto.dat");
	//adaline.training_algorithm->target_patterns.load("c:/asignacion_letras.dat");
	adaline.training_algorithm->target_patterns.load("c:/alfabeto.dat");
	adaline.training_algorithm->training_patterns.convert_all_patterns_to_bipolar();
	adaline.training_algorithm->target_patterns.convert_all_patterns_to_bipolar();

	//
	cout<<"Usaremos como target el mismo patron que la entrada"<<
		endl<<"es decir entrenaremos la red para que encuentre similitudes"<<
		endl<<"entre una letra y si misma."<<endl;

	cout<<"antes de entrenar cambiamos a codificacion bipolar los patrones de entrada."<<endl;

	cout<<"Lanzamos entrenamiento, ver log de salida."<<endl;
	//ENTRENAMIENTO
	adaline.training_algorithm->train();

	adaline.save("c:/Adaline_LeeletrasLimpias.xml");

	/*if (adaline.load("c:/Adaline_LeeletrasLimpias.xml")==false)
	{
		cout<<"No se pudo cargar el fichero de la red neural."<<endl;
		exit(-1);
	}*/

	cout<<"Para evitar tener que entrenar la red una y otra vez la guardamos"<<
	endl<<"en un archivo, la cargamos ahora."<<endl;
/*
	cout<<"HIT RATIO (0.0 To 1.0):"<<endl;
	double hitp=adaline.training_algorithm->calculate_hit_ratio_after_training(0);
	cout<<hitp<<endl;
	cout<<hitp*100<<"%"<<endl;*/

	cout<<"Vamos a ir subiendo el nivel de ruido de 0 a 30% y a apuntar el error cometido"<<
		endl<<"de esa manera veremos cómo reacciona el adaline a los patrones ruidosos"<<endl;

	ofstream fout;
	cout<<"Generando puntos RUIDO HITS"<<endl;
	fout.open("c:/GraficaAdalineRuido.dat");
	if (fout==NULL)
	{
		cout<<"error en creación de fichero, compruebe path"<<endl;
		return;
	}

	//fout<<"R	H"<<endl;
	for (int r=0;r<=30;r++)
	{
	double hitp=adaline.training_algorithm->calculate_hit_ratio_after_training(r,0.0);
	fout<<r<<"	"<<(hitp*100.0)<<"	"<<endl;
	}

	fout.close();

}
