#include "LoadOperators.h"
#include "DraftManager.h"

LoadOperators::LoadOperators(DraftManager* draftManager)
{
	m_draftManager = draftManager;
}

bool LoadOperators::LoadDraft(Draft draft, std::list<Operator>& operators)
{
	m_draftManager->TryGetDraft(draft, operators);
}
