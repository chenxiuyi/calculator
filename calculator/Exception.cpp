#include "Exception.h"

//void Exception::FillStackTrace()
//{
//	//linux��
//
//	//window��
//}

const char * Exception::what() const throw()
{
	return message_.c_str(); //c_str()ת��Ϊchar *
}

//const char * Exception::StackTrace() const throw()
//{
//
//	return stackTrace_.c_str();
//}
