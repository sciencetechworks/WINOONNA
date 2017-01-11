/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "PatternCollection.h"
#include "Pattern.h"
#include "Utils.h"
#include <limits>

PatternCollection::PatternCollection(void)
{
	applied_normalization_factor=1.0;
}

PatternCollection::~PatternCollection(void)
{
	list<Pattern*>::iterator iter=patterns_list.begin();
	while(iter!=patterns_list.end())
	{
		delete (*iter);
		iter++;
	}

	while(!patterns_list.empty())
	{
		patterns_list.pop_back();
	}
}


void PatternCollection::add_pattern(Pattern *pattern)
{
	patterns_list.push_back(pattern);
}

bool PatternCollection::load(const char*path)
{
	ifstream fin;
	fin.open(path);
	if (fin==NULL)
		return false;

	string line;
	fin >> line;
	int columnas=0;
	from_string<int>(columnas, line, std::dec);
	fin >> line;
	int filas=0;
	from_string<int>(filas, line, std::dec);

	fin >> line;
	int number2=0;
	from_string<int>(number2, line, std::dec);

	fin >> line;
	int number3=0;
	from_string<int>(number3, line, std::dec);

	
	fin >> line;
	int patterns_in_file=0;
	from_string<int>(patterns_in_file, line, std::dec);


	for (int pattern_number=0;pattern_number<patterns_in_file;pattern_number++)
	{
	Pattern *pattern=new Pattern(filas,columnas);
	pattern->is_bipolar=false;
	 for (int i=0;i<filas;i++)
	 {
	  for (int j=0;j<columnas;j++)
      {
	  fin >> line;
	  double value=999;
	  from_string<double>(value, line, std::dec);
	  pattern->set(i,j,value);
	  }
	 }
	 //cout<<"Patron"<<pattern_number<<endl;
	 //pattern->print();
	 patterns_list.push_back(pattern);
	}
	fin.close();
	return true;
}


void PatternCollection::convert_all_patterns_to_bipolar()
{
	list<Pattern*>::iterator pattern_iter;

	pattern_iter=patterns_list.begin();
	while (pattern_iter!=patterns_list.end())
	{
	 Pattern *pattern=(*pattern_iter);
	 pattern->tobipolar();
	 pattern->print();
	 pattern_iter++;
	}
}

void PatternCollection::print()
{
	list<Pattern*>::iterator iter=patterns_list.begin();
	while(iter!=patterns_list.end())
	{
		Pattern *current=*iter++;
		current->print();
		cout<<endl;
	}
}

// Utilizada para localizar el elemento mayor dentro de los patrones
// de manera que se puede utilizar para normalizar.
double PatternCollection::getMaxValueInPatterns()
{
	double maxval=std::numeric_limits<double>::min();

	list<Pattern*>::iterator piter=patterns_list.begin();
 
	while(piter!=patterns_list.end())
	{
		Pattern *pattern=*piter++;
		double value=pattern->getMaxValue();
		if (value>maxval)
			maxval=value;
	}

	return maxval;
}

void PatternCollection::normalize(double factor)
{
	list<Pattern*>::iterator piter=patterns_list.begin();
 
	while(piter!=patterns_list.end())
	{
	 Pattern *pattern=*piter++;
	 pattern->normalize(factor);
	}
	applied_normalization_factor=factor;
}

/* Genera tantos patrones como pueda a partir de un archivo de datos
de manera que los coloca por grupos de patlength elementos, por ejemplo
si los datos son 100101110001 y patlength es 3 y step es 1 el resultado es
100,001,010,101 .. si step es 2 entoncces 100 010 .. 
Los fichero de datos vienen en formato x y. A la secuencia solo le interesa
la y, luego se salta los valores de x.
Esto permite, por ejemplo, generar un patron de 7 en 7 dias pasado dia a dia
de manera que la red generalice por semanas, de manera que le damos una secuencia 
de una semana y nos devuelva la predicción, por ejemplo, del dia siguiente.
Le hemos dado la evolución de 7 dias y ella intentará darnos la salida del día 8
*/
void PatternCollection::generate_from_data(char *datapath,int patlength,int step)
{
	ifstream fin;
	fin.open(datapath);
	if (fin==NULL)
		return;

	int i=0,j=0;
	double value;
	double *previous=new double[patlength];
	double *current=new double[patlength];


	for (int i=0;i<patlength;i++)
	{
		previous[i]=0.0;
		current[i]=0.0;
	}

	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(3);

	int count=0;
	int copied=0;
	bool finish=false;
	while (!fin.eof())
	{
		// copiamos el patron anterior al actual 
		// avanzando un paso
		if (count>0)
		for (int k=0,j=step;j<patlength;j++)
		{
		 current[k++]=previous[j];
		 copied=k;
		}
				
		for (i=copied;i<patlength;i++)
		{
		fin>>value; // tiramos el primer valor (ordenadas)
		fin>>value; // nos quedamos con el segundo (abcisas, el valor de la funcion)
		if (fin.eof())
		{
			finish=true;
			break;
		}
		current[i]=value;
		}
		if (finish==true)
			break;

		//Generamos el nuevo patron:		
		Pattern *pattern=new Pattern(1,patlength);
		pattern->is_bipolar=true;
		
		for (int k=0;k<patlength;k++)
		{
			//cout<<current[k]<<" ";
			pattern->set(0,k,current[k]);
		}
		//cout<<endl;

		patterns_list.push_back(pattern);
		//pattern->print();
		

		/* copiamos current a previous */
		for (int k=0;k<patlength;k++)
		{
			previous[k]=current[k];
		}
		count++;
		
	}
	
	delete [] previous;
	delete [] current;
	fin.close();

}