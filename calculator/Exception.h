/*********************************************************************************
*FileName: SymbolTable.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:26:44
*Description :
��Ҫ���ܣ������˸ù���������Ҫ���쳣������
	�﷨�쳣---->SyntaxError��
		��ֵʱ����������Ǳ�����1 = 2;
		ȱ�����ţ�1 + (2*2
		����ʶ�ĺ�����
		����ȱ�����ţ�sin(20
		���ű��в����ڵķ��ţ�
		����һ��������û����������ֵ��a �س�
		���Ǳ��ʽ��)1-2
	�ļ���д�쳣---->FileStreamError��
		�ļ����쳣
		�ļ�д�쳣
	�����쳣--->DevisorZero��
	����ʱ��洢�İ汾�Ų�һ��--->VersionUnMatch��
**********************************************************************************/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
	std::string message_;                         //�쳣��Ϣ
	//std::string stackTrace_;
	//void FillStackTrace();

public:
	explicit Exception(const char* message)        //char *���͸�ֵ��string���ͣ�printf(%s)������⣬����cout����
		: message_(message) 
	{
		//FillStackTrace();
	}
	explicit Exception(const std::string& message)  //char *���͸�ֵ��string���ͣ�printf(%s)������⣬����cout����
		: message_(message)
	{
		//FillStackTrace();
	}

	virtual ~Exception() throw() {}
	virtual const char * what() const throw(); //throw()�������׳��쳣��throw(int)������ܻ��׳�int���͵��쳣
	//const char * StackTrace() const throw();

};

class SyntaxError : public Exception
{
public:
	explicit SyntaxError(const char* message)
		: Exception(message) {}

	explicit SyntaxError(const std::string& message)
		: Exception(message) {}

	virtual ~SyntaxError() throw(){}
};

class FileStreamError : public Exception
{
public:
	explicit FileStreamError(const char* message)
		: Exception(message) {}

	explicit FileStreamError(const std::string& message)
		: Exception(message) {}

	virtual ~FileStreamError() throw() {}
};


class DevisorZero : public Exception
{
public:
	explicit DevisorZero(const char* message)
		: Exception(message) {}

	explicit DevisorZero(const std::string& message)
		: Exception(message) {}

	virtual ~DevisorZero() throw() {}
};


class VersionUnMatch : public Exception
{
public:
	explicit VersionUnMatch(const char* message)
		: Exception(message) {}

	explicit VersionUnMatch(const std::string& message)
		: Exception(message) {}

	virtual ~VersionUnMatch() throw() {}
};

#endif //_EXCEPTION_H_
