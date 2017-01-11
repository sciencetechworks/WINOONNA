/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Utils.h"

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}



int aleat(int inf,int sup){
	return (int)(rand()/(((double)RAND_MAX+1)/(sup-inf+1))) + inf;
}



double generate_random(double lower_bound,double upper_bound)
{
	double length;
	if (lower_bound>upper_bound)
		return 0.0; // error

	if ((lower_bound<0)&&(upper_bound<0))
	{
	    length=-lower_bound-upper_bound;
	} else 
	if ((lower_bound<0)&&(upper_bound>0))
	{
		length=-lower_bound+upper_bound;
	} else 
	if ((lower_bound>0)&&(upper_bound>0))
	{
		length= lower_bound+upper_bound;
	} else if ((lower_bound>0)&&(upper_bound<0))
	{
		// Nunca debiera darse
		return 0.0;
	}

	double random = ((double)rand() / ((double)RAND_MAX));
	
	// esta entre 0.0 y 1.0
	double generated= lower_bound+length*random;
	return generated;
}

bool true_only_an_x_percent_of_times(double x)
{
 //un dado de x caras tiene una prob 1/x de ser la cara 0
 double ncaras_dado=1/x;
 int rnd=aleat(0,(int)ncaras_dado);
 if(rnd==0)
	 return true;
 return false;
}

void plot(double (*function)(double value),
		  double startx,double endx,double delta,char *savepath)
{
	ofstream fout;
	fout.open(savepath);
	//fout.setf(ios::fixed, ios::floatfield);
	//fout.precision(5);
	if (fout==NULL)
		return;
	double x,y;
	for (x=startx;x<endx;x+=delta)
	{
		y=function(x);
		fout<<x<<"\t"<<y<<endl;
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

#include "Utils.h"

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}



int aleat(int inf,int sup){
	return (int)(rand()/(((double)RAND_MAX+1)/(sup-inf+1))) + inf;
}



double generate_random(double lower_bound,double upper_bound)
{
	double length;
	if (lower_bound>upper_bound)
		return 0.0; // error

	if ((lower_bound<0)&&(upper_bound<0))
	{
	    length=-lower_bound-upper_bound;
	} else 
	if ((lower_bound<0)&&(upper_bound>0))
	{
		length=-lower_bound+upper_bound;
	} else 
	if ((lower_bound>0)&&(upper_bound>0))
	{
		length= lower_bound+upper_bound;
	} else if ((lower_bound>0)&&(upper_bound<0))
	{
		// Nunca debiera darse
		return 0.0;
	}

	double random = ((double)rand() / ((double)RAND_MAX));
	
	// esta entre 0.0 y 1.0
	double generated= lower_bound+length*random;
	return generated;
}

bool true_only_an_x_percent_of_times(double x)
{
 //un dado de x caras tiene una prob 1/x de ser la cara 0
 double ncaras_dado=1/x;
 int rnd=aleat(0,(int)ncaras_dado);
 if(rnd==0)
	 return true;
 return false;
}

void plot(double (*function)(double value),
		  double startx,double endx,double delta,char *savepath)
{
	ofstream fout;
	fout.open(savepath);
	//fout.setf(ios::fixed, ios::floatfield);
	//fout.precision(5);
	if (fout==NULL)
		return;
	double x,y;
	for (x=startx;x<endx;x+=delta)
	{
		y=function(x);
		fout<<x<<"\t"<<y<<endl;
	}
	fout.close();
}

