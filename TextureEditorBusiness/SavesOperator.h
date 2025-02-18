#pragma once
#include <unordered_map>
#include "Operator.h"
#include <mutex>
#include <list>

//From Operator.h
CREATE_OPERATOR_CLASS(SaveOperator);

class SavesOperator
{
	std::mutex operatorMutex;
	std::unordered_map<_GUID*, std::list<Operator*>> saves;
};

