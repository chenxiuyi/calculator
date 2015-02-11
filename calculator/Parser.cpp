#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdio>
#include "Parser.h"
#include  "scanner.h"
#include "Node.h"
#include "Calc.h"
#include "Exception.h"
#include "DebugNew.h"

Parser::Parser(Scanner& scanner, Calc& calc)
	: scanner_(scanner), calc_(calc), status_(STATUS_OK), tree_(NULL) {}

Parser::~Parser() { }

STATUS Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone()) //��ֹδ������ȫ 1+1=2--->ֻ������1+1 
	{
		status_ = STATUS_ERROR;
	}

	return status_;
}


std::auto_ptr<Node> Parser::Expr()
{
	std::auto_ptr<Node> node = Term();
	EToken token = scanner_.Token();


	if (TOKEN_PLUS == token || TOKEN_MINUS == token)  //Expr :��= Term{('+' | '-') Term }
	{
	
		std::auto_ptr<MultipleNode> multipleNode (new SumNode(node));
		do
		{
			scanner_.Accept();                          //������һ����ʶ��
			std::auto_ptr<Node> nextNode = Term();      //��������Term()
			multipleNode->AppendChild(nextNode, (TOKEN_PLUS == token)); //����multipleNode��
			token = scanner_.Token();
		} while (TOKEN_PLUS == token || TOKEN_MINUS == token);

		node = multipleNode;
	}
	else if (TOKEN_ASSIGN == token)                    //Expr :��= term = Expr 
	{ 
	
		scanner_.Accept();

		std::auto_ptr<Node> nodeRight = Expr();
		if (node->IsLvalue())
		{
			node = std::auto_ptr<Node> (new AssignNode(node, nodeRight));
		}
		else
		{
			status_ = STATUS_ERROR;
			//todo �׳��쳣
			throw SyntaxError("the left-hand side of an assignment must be a variavle");
		}
	}
	
	return node;
}

std::auto_ptr<Node> Parser::Term()
{

	std::auto_ptr<Node> node = Factor();
	EToken token = scanner_.Token();

	if (TOKEN_MUTIPLY == token || TOKEN_DIVIDE == token)   //Term ::= Factor {('*' | '/') Factor }
	{
	
		std::auto_ptr<MultipleNode> multipleNode (new ProductNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Factor();
			multipleNode->AppendChild(nextNode, (TOKEN_MUTIPLY == token));
			token = scanner_.Token();
		} while (TOKEN_MUTIPLY == token || TOKEN_DIVIDE == token);

		node = multipleNode;
	}

	return node;

}

std::auto_ptr<Node> Parser::Factor()
{
	
	std::auto_ptr<Node> node;
	EToken token = scanner_.Token();

	/*factor ::= Expr */
	if (TOKEN_LPARENTHESIS == token)  //'('
	{
		scanner_.Accept();
		node = Expr();
		if (TOKEN_RPARENTHESIS == scanner_.Token()) //')'
		{
			scanner_.Accept();/*ɨ����һ����ʶ��or������or������*/
		}
		else
		{
			status_ = STATUS_ERROR;

			//�׳��쳣
			throw SyntaxError("Missing parenthesis!");
		}
	}
	else if (TOKEN_NUMBER == token)  // factor ::= number
	{
		node = std::auto_ptr<Node>(new NumberNode(scanner_.Number()));
		scanner_.Accept();
	}
	else if (TOKEN_MINUS == token)  // factor :: = '-'Factor 
	{
		scanner_.Accept();
		node = std::auto_ptr<Node>(new UMinusNode(Factor()));
	}
	else if (TOKEN_IDENTIFIER == token)  //����or��������
	{
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);

		scanner_.Accept();
		token = scanner_.Token();

		if (TOKEN_LPARENTHESIS == token)   //factor :: = Function 
		{
			scanner_.Accept();     //����'('
			node = Expr();

			token = scanner_.Token();
			if (TOKEN_RPARENTHESIS == token) //����')'���Ǻ���
			{
				scanner_.Accept();
				if (SymbolTable::IDNOTFOUND != id && calc_.IsFunction (id))
				{
					node = std::auto_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				}
				else  //����ʶ�ĺ���
				{
					status_ = STATUS_ERROR;
					std::ostringstream oss;
					oss << "Unkown function: " << symbol;

					throw SyntaxError(oss.str());
				}

			}
			else
			{
				status_ = STATUS_ERROR;
				throw SyntaxError("Missing parenthesis in a Function call.");
			}
		}
		else    //factor :: = Variable
		{
			if (SymbolTable::IDNOTFOUND == id)
			{
				

				if (TOKEN_END == token)   //�����ʶ����û��ֵ���س�,���磺a �س�
				{
					std::ostringstream oss;
					oss << "did not set a varible: " << symbol <<std::endl
						<< "set a variable: variable = number";
					throw SyntaxError(oss.str());
				}
				else //���ű��в����ڵķ���
				{
					
					token = scanner_.Token();
					if (TOKEN_ASSIGN == token)  //�жϷ����Ƿ��Ǹ�ֵ���ţ�=
					{
						id = calc_.AddSymbol(symbol);
					}
					else
					{
						status_ = STATUS_ERROR;
						std::ostringstream oss;
						oss << "Unkown varible: " << symbol << std::endl
							<< "set a variable: VariableName = Number";
						throw SyntaxError(oss.str());
					}	
				}
				
			}
			node = std::auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
		}
	
		
	}
	else
	{
		status_ = STATUS_ERROR;
	
		//�׳��쳣
		throw SyntaxError("Not a valid expression.");
	}

	return node;
}



double Parser::Calculate() const
{
	assert(NULL != tree_.get());

	return tree_->Calc();
}
