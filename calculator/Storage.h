/*********************************************************************************
*FileName: Storage.h
*Author :  Ljian
*Version : 1.0
*Date :  2015��2��8��14:17:11
*Description :
��Ҫ���ܣ������˴洢������
��ع������ࣺSymbolTable
**********************************************************************************/
#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include <map>
#include "Serial.h"

class SymbolTable;

class Storage : public Serializable
{
private:
	std::map<unsigned int, double> cells_;  //�洢���ű���id��ֵ���Ӧ�Ĺ�ϵ

public:
	Storage(SymbolTable& tbl);
	void Clear();                                 //�������
	void AddConstants(SymbolTable& tbl);          //���ӳ�����Ŀǰֻ֧��pi e
	double GetValue(unsigned int id) const;       //����id�������ڵ�ֵ
	unsigned int GetSize() const;                 //��ȡmap���ж��ٸ�����
	void SetValue(unsigned int id, double val);   //����map�е�ֵ
	//void Storage::AddValue(unsigned int id, double val��bool isInit);   //��map�����ֵ
	void AddValue(unsigned int id, double val);
	virtual void Serialize(Serializer& out) const;//��Storage���е�ֵ�����ļ��洢
	virtual void DeSerialize(DeSerializer& in);   //���ļ��е�ֵ���ص�Storage����
};

#endif //_STORAGE_H_