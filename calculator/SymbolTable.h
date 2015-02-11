/*********************************************************************************
*FileName: SymbolTable.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:19:43
*Description :
��Ҫ���ܣ�������ű��࣬��������ʽ������صķ���
**********************************************************************************/
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <string>
#include <map>
#include "Serial.h"

class SymbolTable : public Serializable
{
private:
	std::map<const std::string, unsigned int> dictionary_;  //�洢������id���Ӧ�ù�ϵ
	unsigned int curId_;                                    //�洢��Ҫ������ű�ķ���id
public:
	enum { IDNOTFOUND = 0xFFFFFFFF };                       //IDNOTFOUND�����ڷ��ű����Ҳ�����Ӧ�ķ���
	SymbolTable() : curId_(0) {}                            
	unsigned int Add(const std::string& str);               //����ű��м������
	unsigned int Find(const std::string& str) const;        //���ݷ���Ѱ�ҷ��ű����Ƿ�洢�÷���
	unsigned int GetCurId()const;                           //��ȡ��һ���ļ�����ű�ķ���id
	void Clear();                                           //������ű�
	const std::string &GetSymbolName(unsigned int id) const;//����id���Ҳ���ȡ���ű��еķ���

	virtual void Serialize(Serializer& out) const;          //�����ű��е����ݴ洢���ļ���
	virtual void DeSerialize(DeSerializer& in);             //���ļ��е����ݼ��ص����ű���
};

#endif  //_SYMBOLTABLE_H_

