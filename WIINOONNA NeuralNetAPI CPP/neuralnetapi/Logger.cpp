/**
 Wonderfully Integrated Native Object Oriented Neural Network API.
 
 STANDARD DISCLAIMER

ScienceTechWorks is furnishing this item "as is". ScienceTechWorks does not provide any warranty of the item whatsoever, whether express, implied, or statutory, including, but not limited to, any warranty of merchantability or fitness for a particular purpose or any warranty that the contents of the item will be error-free.
In no respect shall ScienceTechWorks incur any liability for any damages, including, but limited to, direct, indirect, special, or consequential damages arising out of, resulting from, or any way connected to the use of the item, whether or not based upon warranty, contract, tort, or otherwise; whether or not injury was sustained by persons or property or otherwise; and whether or not loss was sustained from, or arose out of, the results of, the item, or any services that may be provided by ScienceTechWorks.

If a recognizable person appears in this video, use for commercial purposes may infringe a right of privacy or publicity. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead. Accordingly, it is requested that if this video is used in advertising and other commercial promotion, layout and copy be submitted to ScienceTechWorks prior to release. It may not be used to state or imply the endorsement by ScienceTechWorks employees of a commercial product, process or service, or used in any other manner that might mislead.
 
 ScienceTechworks@gmail.com
 Ramon.Talavera@gmail.com
**/

#include "Logger.h"

Logger::Logger(void)
{
}

Logger::~Logger(void)
{
}

void Logger::disable()
{
	fout.clear(ios::failbit); //DISABLE LOGGIN
}

bool Logger::init(const char *path)
{
	fout.open(path);
	fout.setf(ios::fixed, ios::floatfield);
	fout.precision(3);
	if (fout==NULL)
		return false;
	return true;
}

void Logger::log(string message)
{
	fout<<message;
	fout<<endl;
}

void Logger::close(void)
{
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

#include "Logger.h"

Logger::Logger(void)
{
}

Logger::~Logger(void)
{
}

void Logger::disable()
{
	fout.clear(ios::failbit); //DISABLE LOGGIN
}

bool Logger::init(const char *path)
{
	fout.open(path);
	fout.setf(ios::fixed, ios::floatfield);
	fout.precision(3);
	if (fout==NULL)
		return false;
	return true;
}

void Logger::log(string message)
{
	fout<<message;
	fout<<endl;
}

void Logger::close(void)
{
	fout.close();
}
