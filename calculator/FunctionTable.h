/*********************************************************************************
*FileName: Node.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:21:26
*Description :
��Ҫ���ܣ����庯������
��ع������ࣺSymbolTable
**********************************************************************************/

#ifndef _FUNCTIONTABLE_H_
#define _FUNCTIONTABLE_H_

#include <vector>
#include <map>

class SymbolTable;

typedef double(*PtrFun)(double);  //��������һ�ֺ���ָ����

class FunctionTable
{
private:                
	std::map<unsigned int, PtrFun> funsMap_;     //�洢���ű��е�id���Ӧ����ѧ����ָ��
public:
	FunctionTable(SymbolTable& tbl);
	void Init(SymbolTable& tbl);                 //�洢�Ǻ�����
	PtrFun GetFunction(unsigned int id) const;   //����id��ȡ�������ж�Ӧ�ĺ���
	unsigned int GetSize() const;                //��ú��������ж��ٸ�����
   ~FunctionTable();                             

};

#endif //_FUNCTIONTABLE_H_