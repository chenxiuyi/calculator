/*********************************************************************************
*FileName: Parser.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:21:59
*Description :
��Ҫ���ܣ����������
����ࣺScanner��
���ʽ��BNF��ʾ��
	Expr ::= Term{('+' | '-') Term }                    ---->multipleNode
	Expr ::= Term = Expr                                ---->AssignNode

	Term ::= Factor {('*' | '/') Factor }               ---->multipleNode

	Factor ::=
	1.Number                                            ---->NumberNode
	2.Identifier
		2.1.Function                                    ---->FunctionNode
		2.2.Variable                                    ---->VariableNode
	3.'-'Factor                                         ---->UMinusNode
	4.'('Expr ')'
**********************************************************************************/


#ifndef _PARSER_H_
#define _PARSER_H_

#include <memory>

class Scanner;   /*����Scanner������ǰ���ͷ�ļ�ͷ�ļ���С��Сһ��*/
class Node;
class Calc;

enum STATUS
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT,
};


class Parser
{
private:
	Scanner& scanner_;                   //����������Parser�಻����scanner_���������ڣ�������������Ϊ��Ϲ�ϵ
	//std::string expression_;
	std::auto_ptr<Node> tree_;           //���ʽ�﷨��
	STATUS status_;                      //״̬
	Calc& calc_;                         //Ҫ����ķ�����Ϣ

public:
	Parser(Scanner& scanner, Calc& calc);   /*��scanner�������*/
	~Parser();
	STATUS Parse();				            //����һ�����ʽ���ɱ��ʽ��
	std::auto_ptr<Node> Expr();				//�������ʽ
	std::auto_ptr<Node> Term();				//������
	std::auto_ptr<Node> Factor();		    //��������
	//std::string& GetExpression_();
	double Calculate() const;              //��������ʽ��ֵ

};

#endif //_PARSER_H_

