#include <algorithm>
#include <iostream>
#include "SymbolTable.h"
#include "Storage.h"
#include "Exception.h"

unsigned int SymbolTable::Add(const std::string & str)
{
	dictionary_[str] = curId_;

	return curId_++;   //���ص�ǰ���ŵ�ID,�����ó���һ�����ŵ�ID
}

unsigned int SymbolTable::Find(const std::string & str) const
{
	std::map<const std::string, unsigned int>::const_iterator it = dictionary_.begin();
	it = dictionary_.find(str);

	if (it != dictionary_.end())
	{
		return it->second;
	}

	return IDNOTFOUND;
}

unsigned int SymbolTable::GetCurId() const { return curId_; }


void SymbolTable::Clear()
{
	dictionary_.clear();
	curId_ = 0;
}


/*function boject, functor
�������ʹ��������һ������---->����()�����
STL �������֮һ*/
class IsEqualId
{
protected:
	unsigned int id_;
public:
	IsEqualId(unsigned int id) :id_(id) {}
	bool operator() (const std::pair<const std::string, unsigned int>& it) const
	{
		return id_ == it.second;
	}
};

const std::string & SymbolTable::GetSymbolName(unsigned int id) const
{

	std::map<const std::string, unsigned>::const_iterator it;
	it = find_if(dictionary_.begin(), dictionary_.end(), IsEqualId(id));

	if (dictionary_.end() == it)
	{
		throw Exception("Internal error: missing entry in symbol table.");
	}

	return it->first;
}

void SymbolTable::Serialize(Serializer & out) const
{
	//д�볤��
	out << dictionary_.size();
	
	std::map<const std::string, unsigned int>::const_iterator it;

	for (it = dictionary_.begin(); it != dictionary_.end(); ++it)
	{
		out << it->first << it->second;
	}
	out << curId_;
}

void SymbolTable::DeSerialize(DeSerializer & in)
{
	dictionary_.clear();
	
	unsigned int size;
	in >> size;

	for (unsigned int i = 0; i < size; ++i)
	{
		std::string str;
		unsigned int id;
		
		in >> str >> id;
		dictionary_[str] = id;
	}
	in >> curId_;
	
}

