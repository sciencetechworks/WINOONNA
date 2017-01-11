/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Pattern.h"
#include <limits>
Pattern::Pattern(void)
{
}

Pattern::~Pattern(void)
{
	delete data;
	//cout<<"Pattern deleted"<<endl;
}

double Pattern::getMaxValue()
{
  double maxval=std::numeric_limits<double>::min();
  for (int k=0;k<rows*cols;k++)
  {
	  if (data[k]>maxval)
		  maxval=data[k];
  }
  return maxval;
}

void Pattern::normalize(double factor)
{
  for (int k=0;k<rows*cols;k++)
  {
	  data[k]/=factor;
  }
}

void Pattern::print_data()
{
	//cout<<endl<<"Data:";
	for (int k=0;k<rows*cols;k++)
		cout<<data[k]<<"|";
	//cout<<endl;
}

Pattern::Pattern(int dimx,int dimy)
{
	is_bipolar=true;
	rows=dimx;
	cols=dimy;
	
	data=new double[dimx*dimy];

	for (int k=0;k<rows*cols;k++)
		data[k]=-1.0;
}


Pattern::Pattern(const Pattern &p)
{
	this->rows=p.rows;
	this->cols=p.cols;
	this->is_bipolar=p.is_bipolar;

	this->data=new double[rows*cols];

	for (int k=0;k<rows*cols;k++)
		data[k]=p.data[k];
}

Pattern::Pattern(Pattern *p)
{
	this->rows=p->rows;
	this->cols=p->cols;
	this->is_bipolar=p->is_bipolar;

	this->data=new double[rows*cols];

	for (int k=0;k<rows*cols;k++)
		data[k]=p->data[k];
}

double Pattern::get(int i,int j)
{
	return data[(i*cols)+j];
}

double Pattern::get(int pos)
{
	return data[pos];
}

void Pattern::set(int i,int j,double value)
{
  data[(i*cols)+j]=value;
}

void Pattern::set(int pos,double value)
{
	data[pos]=value;
}

void Pattern::tobipolar()
{
	int pos;
	for (pos=0;pos<rows*cols;pos++)
	{
		if (get(pos)==0.0) set(pos,-1.0);
	}
	is_bipolar=true;
}

void Pattern::tobinary()
{
	for (int pos=0;pos<rows*cols;pos++)
	{
		if (get(pos)==-1.0) set(pos,0.0);
	}
	is_bipolar=false;
}

double *Pattern::get()
{
	return data;
}


void Pattern::set(double *data,int dimx,int dimy)
{
	rows=dimx;
	cols=dimy;
	this->data=data;
}

void Pattern::set(double *data,int dim)
{
	rows=dim;
	cols=1;
	this->data=data;
}


void Pattern::print_data(ofstream &fout)
{
	//fout<<endl<<"Data:";
	for (int k=0;k<rows*cols;k++)
		fout<<data[k]<<"|";
	//fout<<endl;
}

void Pattern::print(ofstream &fout)
{

	//fout<<"en linea:";
	print_data(fout);
	/*fout<<"en cuadro:"<<endl;
	for (int i=0;i<rows;i++)
      {
	  for (int j=0;j<cols;j++)
	  {
	     double val=this->get(i,j);
		 //val=this->data[fila*dimx+columna];
		 //cout<<val<<" ";
	  	 if ((val==-1.0)||(val==0.0))
			fout<<" ";
		 else
		 if ((val==1.0))
			 fout<<"*";
		 else
			 fout<<"Non binary or bipolar value in pattern";
	  }
	 fout<<endl;
	}
	fout<<endl;*/
	
}

void Pattern::print(void)
{
	//cout<<"en linea:";
	print_data();
	/*cout<<"en cuadro:"<<endl;
	for (int i=0;i<rows;i++)
      {
	  for (int j=0;j<cols;j++)
	  {
	     double val=this->get(i,j);
		 //val=this->data[fila*dimx+columna];
		 //cout<<val<<" ";
	  	 if ((val==-1.0)||(val==0.0))
			cout<<" ";
		 else
		 if ((val==1.0))
			 cout<<"*";
		 else
			 cout<<"Non binary or bipolar value in pattern";
	  }
	 cout<<endl;
	}*/
}