#ifndef _CALC_H_
#define _CALC_H_

#include <string>
#include "SymbolTable.h"
#include "FunctionTable.h"
#include "Storage.h"
#include "Serial.h"


class Parser;

class Calc : public Serializable
{
	friend class Parser;  //ʹ��Parser�෽��ķ���Calc��˽�г�Ա
private:
	//-->���ڶ�����SymbolTable�࣬�����Ҫ������ͷ�ļ����������� Calc�ฺ��symTbl_���������ڣ����������֮������Ϲ�ϵ,
	//����Storage�Ĺ��캯����Ҫ�õ�SymbolTable�����ã�������˳��SymbolTable��Storage��ǰ��
	SymbolTable symTbl_;  
	FunctionTable functionTbl_;   //���ں������еĺ����ǹ̶��ģ���˰Ѻ�����Ĺ�����ڷ��ű��ǰ��
	Storage storage_;             //�����ĸ����ǲ��̶���
	unsigned int FindSymbol(const std::string& str) const;  //�ڷ��ű��в���str����
	unsigned int AddSymbol(const std::string& str);         //�����ű�����ӷ���
	Storage& GetStorage();                                  //��ȡstroage_������
	bool IsFunction(unsigned int id) const;                 //�ж��Ƿ��Ǻ���
	PtrFun GetFunction(unsigned int id) const;              //��ȡ����ָ��
	double GetVariableValue(unsigned int id) const;         //��ȡ������ֵ
public:
	Calc() : symTbl_(), functionTbl_(symTbl_), storage_(symTbl_) {}
	void ListFun() const;                                   //��ӡ������
	void ListVariable() const;                              //��ӡ������

	virtual void Serialize(Serializer& out) const;          //��������ͱ������е����ݴ洢���ļ���
	virtual void DeSerialize(DeSerializer& in);             //���ļ��м������ݵ����ű�ͱ�������

};
#endif //_CALC_H_

