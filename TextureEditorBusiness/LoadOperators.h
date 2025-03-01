#pragma once
#include <unordered_map>
#include "Operator.h"
#include <mutex>
#include <list>
#include "Draft.h"

class DraftManager;

//From Operator.h
CREATE_OPERATOR_CLASS(LoadOperator);

class LoadOperators
{
	DraftManager* m_draftManager;
public:
	LoadOperators(DraftManager* draftManager);
	bool LoadDraft(Draft draft, std::list<Operator>& operators);
};

