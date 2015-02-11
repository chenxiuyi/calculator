#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

#include "Parser.h"

class Scanner;   /*����Scanner������ǰ���ͷ�ļ�ͷ�ļ���С��Сһ��*/
class Calc;

class CommandParser
{
private:
	enum ECommand
	{
		CMD_HELP,
		CMD_QUIT,
		CMD_VAR,
		CMD_FUN,
		CMD_LOAD,
		CMD_SAVE,
		CMD_ERROR,
	};
private:
	Scanner& scanner_;
	Calc &calc_;
	ECommand cmd_;                           //������������
	std::string cmdName_;                    //������

	void Help() const;                       //��������
	void ListVar() const;                    //��ӡ��������
	void ListFun() const;                    //��ӡ��������
	STATUS Load(const std::string& fileName);//���ļ��м������ݵ�������ͺ�������
	STATUS Save(const std::string& fileName);//�洢������ͺ������ļ���

public:
	CommandParser(Scanner& scanner, Calc& calc_);   /*��scanner�������*/
	STATUS Execute();                         //���ݽ�����������ִ������   
 
};

#endif //_COMMAND_PARSER_H_

