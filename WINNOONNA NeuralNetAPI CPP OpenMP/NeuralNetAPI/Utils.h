/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#pragma once


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 4.0*atan(1.0)
#define round(x) (x<0?ceil((x)-0.5):floor((x)+0.5))


template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}



template <class T>
inline std::string to_string (const T& t)
{
std::stringstream ss;
ss << t;
return ss.str();
}


/*******************************************************************
*                                   FUNCION:
*                      int aleat (int iP, int iU)
* RESUMEN:  Generador de n£meros aleatorios 'equiprobables' en
*      el rango [iP,iU].
* ENTRADAS: Indice del primer y £ltimo elemento del intervalo.
* SALIDA: N£mero aleatorio generado.
*******************************************************************/
/*
int aleat (int iP, int iU)
    {
    int Number;
    int Distancia;

    Distancia=abs(iU-iP)+1;
    if (iU<iP) iP=iU;
    Number=(int)(iP+((int)rand()*Distancia/(RAND_MAX+1)));
    return Number;
    }
*/

int aleat(int inf,int sup);
int aleat_r8(int inf,int sup,int *seed1,int *seed2,int *seed3);
bool true_only_an_x_percent_of_times(double x);
void plot(double (*function)(double value),
		  double startx,double endx,double delta,char *savepath);
double generate_random(double lower_bound,double upper_bound);
double generate_random_r8(double lower_bound,double upper_bound,int *seed1,int *seed2,int *seed3);
double r8_random ( int *s1, int *s2, int *s3 );

class Utils
{
public:
	Utils(void);
	~Utils(void);
};
