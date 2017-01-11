/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "EjercicioBackPropagationLeeLetras.h"

EjercicioBackPropagationLeeLetras::EjercicioBackPropagationLeeLetras(void)
{
}

EjercicioBackPropagationLeeLetras::~EjercicioBackPropagationLeeLetras(void)
{
}



void EjercicioBackPropagationLeeLetras::ejecuta()
{
	//Creamos un backpropagation de 35 entradas 100 neuronas en capa oculta y 35 salidas
	BackPropagation backpropagation=BackPropagation(35,35,35);
	// Ajustamos umbral, factor de aprendizaje y 
	// máximo número de épocas a ejecutar.
	//backpropagation.setLearningFactor(1.0/100.0);
	backpropagation.setLearningFactor(0.2);
	backpropagation.logger.disable();

	backpropagation.training_algorithm->setMax_epochs(5000);
	((BackPropagationTrainingAlgorithm*)backpropagation.training_algorithm)->objective_min_cuadratic_error=0.05;
	

	//Cargamos fichero de patrones de letras:
	cout<<"Cargando patrones de letras"<<endl;
	backpropagation.training_algorithm->training_patterns.load("c:/alfabeto.dat");
	//backpropagation.training_algorithm->target_patterns.load("c:/asignacion_letras.dat");
	backpropagation.training_algorithm->target_patterns.load("c:/alfabeto.dat");
	backpropagation.training_algorithm->training_patterns.convert_all_patterns_to_bipolar();
	backpropagation.training_algorithm->target_patterns.convert_all_patterns_to_bipolar();

	//
	cout<<"Usaremos como target el mismo patron que la entrada"<<
		endl<<"es decir entrenaremos la red para que encuentre similitudes"<<
		endl<<"entre una letra y si misma."<<endl;

	cout<<"antes de entrenar cambiamos a codificacion bipolar los patrones de entrada."<<endl;

	cout<<"Lanzamos entrenamiento, ver log de salida."<<endl;
	//ENTRENAMIENTO
	//backpropagation.training_algorithm->train();

	//backpropagation.save("c:/BackPropagation_LeeletrasLimpias.xml");

	if (backpropagation.load("c:/BackPropagation_LeeletrasLimpias.xml")==false)
	{
		cout<<"No se pudo cargar el fichero de la red neural."<<endl;
		exit(-1);
	}

	cout<<"Para evitar tener que entrenar la red una y otra vez la guardamos"<<
	endl<<"en un archivo, la cargamos ahora."<<endl;
	

	cout<<"Vamos a ir subiendo el nivel de ruido de 0 a 30% y a apuntar el error cometido"<<
		endl<<"de esa manera veremos cómo reacciona el backpropagation a los patrones ruidosos"<<endl;

	ofstream fout;
	cout<<"Generando puntos RUIDO HITS"<<endl;
	fout.open("c:/GraficaBackPropagationRuido.dat");
	if (fout==NULL)
	{
		cout<<"error en creación de fichero, compruebe path"<<endl;
		return;
	}

	//fout<<"R	H"<<endl;
	for (int r=0;r<=30;r++)
	{
	double hitp=backpropagation.training_algorithm->calculate_hit_ratio_after_training(r,0.05);
	cout<<r<<"	"<<(hitp*100.0)<<"	"<<endl;
	fout<<r<<"	"<<(hitp*100.0)<<"	"<<endl;
	}

	fout.close();

}
