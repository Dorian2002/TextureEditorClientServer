#pragma once
#include <unordered_map>
#include "Operator.h"
#include <mutex>
#include <list>
#include "Draft.h"

class DraftManager;

//From Operator.h
CREATE_OPERATOR_CLASS(SaveOperator);

class SaveOperators
{
	DraftManager* m_draftManager;

	SaveOperators(DraftManager* draftManager);
public:
	void SaveDraft(Draft draft, std::list<Operator> operators);
};

