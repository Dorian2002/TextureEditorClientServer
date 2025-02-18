#pragma once
#include <unordered_map>
#include "Operator.h"
#include "Draft.h"
#include <mutex>
class DraftManager
{
	std::mutex m_draftsMutex;
	std::unordered_map<_GUID*, std::list<Operator>> m_drafts;
public:
	bool TryGetDraft(Draft draft, std::list<Operator>& operators);
	bool TryInsertDraft(Draft draft, std::list<Operator> operators);
};

