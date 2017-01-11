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
#include "ProfileTimer.h"
#include "PatternCollection.h"


//#include "MadalineTransferFunction.h"
//#include "MadalineLearningFunction.h"
//#include "MadalineTrainingAlgorithm.h"
//#include "Madaline.h"



#include "ejemplos_backpropagation.h"
#include "BackPropagationTransferFunction.h"
#include "BackPropagationLearningFunction.h"
#include "BackPropagationTrainingAlgorithm.h"
#include "BackPropagation.h"

#include "EjercicioBackPropagationLeeLetras.h"
#include <cmath>
#include <omp.h>

/*
void show_outputs(Perceptron *perceptron)
{
vector<Neuron*> output_list=perceptron->output_layer->getNeuron_list();
vector<Neuron*>::iterator outputs=output_list.begin();
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
	ProfileTimer timer;
	char output_file_serie_filename[]="c:/omp_results/prediccion_seno_serie";
	char output_file_paralelo_filename[]="c:/omp_results/prediccion_seno_paralelo";


	char output_file_serie[255]="";
	char output_file_paralelo[255]="";

	double segundos_entrenamiento_serie=-1.0,segundos_entrenamiento_paralelo=-1.0;
	//backpropagation_example_1output();
	//backpropagation_example_2outputs();

	//backpropagation_ejemplo_teoria();
	//EjercicioBackPropagationLeeLetras ejercicio_letras_backpropagation;
	//ejercicio_letras_backpropagation.ejecuta();


	//backpropagation_ejemplo_predice_secuencia_simple();

	//backpropagation_train_for_example_series2();


	int n_hidden=100;
	int training_epochs=20;
	double precission_alpha=0.00000001;
	int nthreads=omp_get_max_threads();


	ofstream fout_serial,fout_paralell,fout_speedup,
		fout_gnuplot_script_graphs;
	fout_serial.open("c:/omp_time_results/omp_sin_serial_time.dat");
	fout_paralell.open("c:/omp_time_results/omp_sin_paralell_time.dat");
	fout_speedup.open("c:/omp_time_results/omp_sin_speedup.dat");
	fout_gnuplot_script_graphs.open("c:/omp_results/gnuplotscript.txt");

	fout_gnuplot_script_graphs<<"plot 0.8*sin(x) with lines"<<endl;

	for (n_hidden=1000;n_hidden<150000;n_hidden+=2500)
	{

		precission_alpha=0.0000000000000001;
		printf("OMP MAX THREADS: %d\n",omp_get_max_threads());
		cout<<"Lanzando Version Paralela"<<endl;

		segundos_entrenamiento_paralelo=
			backpropagation_ejemplo_predice_seno_omp(
			n_hidden,
			training_epochs,
			precission_alpha,
			nthreads);



		printf("Tiempo de entrenamiento VERSION PARALELA: %.4f s\n",segundos_entrenamiento_paralelo);

		sprintf(output_file_paralelo,"%s_%d_%d_%.10f_%d.dat",output_file_paralelo_filename,
			n_hidden,training_epochs,precission_alpha,nthreads);

		fout_gnuplot_script_graphs<<"replot '"<<output_file_paralelo<<"' with lines"<<endl;

		backpropagation_ejemplo_seno_genera_graficas(output_file_paralelo);

		// COMPARAMOS CON LA VERSION SERIE
		printf("Version Serie:");
		segundos_entrenamiento_serie=
			backpropagation_ejemplo_predice_seno(
			n_hidden,
			training_epochs,
			precission_alpha);

		printf("Tiempo de entrenamiento VERSION SERIE: %.4f s\n",segundos_entrenamiento_serie);

		//sprintf(output_file_serie,"%s_%d_%d_%.10f.dat",output_file_serie_filename,
		//	n_hidden,training_epochs,precission_alpha);

		/*backpropagation_ejemplo_seno_genera_graficas(output_file_serie);

		fout_gnuplot_script_graphs<<"replot '"<<output_file_serie<<"' with lines"<<endl;
		*/


		double speedup=(segundos_entrenamiento_serie/segundos_entrenamiento_paralelo);
		printf("Speed Up: %.6f\n",speedup);


		//printf("Generados archivos:\t%s \n \t%s\n",output_file_serie,output_file_paralelo);

		fout_serial<<n_hidden<<"\t"<<segundos_entrenamiento_serie<<endl;
		fout_serial.flush();
		fout_paralell.flush();
		fout_speedup<<n_hidden<<"\t"<<speedup<<endl;

		fout_paralell<<n_hidden<<"\t"<<segundos_entrenamiento_paralelo<<endl;

		fout_speedup.flush();

		fout_gnuplot_script_graphs.flush();
	}
	fout_serial.close();
	fout_paralell.close();
	fout_speedup.close();
	fout_gnuplot_script_graphs.close();
	return 0;
}

