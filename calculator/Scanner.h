/*********************************************************************************
*FileName: Scanner.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:21:59
*Description : 
��Ҫ���ܣ�����ɨ���࣬�ӱ�׼��������ɨ����ʽ��صķ���
**********************************************************************************/

#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>


enum EToken {
	TOKEN_COMMAND,
	TOKEN_ERROR,                 
	TOKEN_END,					 
	TOKEN_NUMBER,				
	TOKEN_IDENTIFIER,			 
	TOKEN_PLUS,				
	TOKEN_MINUS, 
	TOKEN_MUTIPLY,
	TOKEN_DIVIDE, 
	TOKEN_LPARENTHESIS, 
	TOKEN_RPARENTHESIS,
	TOKEN_ASSIGN,
};

class Scanner
{
private:
	std::istream& in_;                 //��׼������
	bool isEmpty_;                     //�Ƿ�Ϊ��
	EToken token_;                     //��¼ɨ����
	double number_;                    //ɨ�赽������
	std::string symbol_;               //ɨ�赽��ʶ��
	int look_;                         //ɨ�赽���ַ�
	void ReadChar();                   //�ӱ�׼�������ж�ȡ�ַ�

public:
	explicit Scanner(std::istream& in);
	void Accept();                     //ɨ��һ����ʶ��or������or������
	void AcceptCommand();              //ɨ������
	void CleanIstream();               //�����׼����������
	double Number() const;             //��ȡɨ�赽������
	bool IsEmpty()const;               //�ж��Ƿ�Ϊ��
	bool IsDone() const;               //�ж��Ƿ�ɨ�����
	bool IsCommand() const;            //�ж��Ƿ�������
	std::string GetSymbol() const;     //��ȡɨ�赽�ı�ʶ��
	EToken Token() const;              //��ȡɨ����
	
};

#endif //_SANNER_H_
