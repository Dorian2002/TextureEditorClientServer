#include "SaveOperators.h"
#include "DraftManager.h"

SaveOperators::SaveOperators(DraftManager* draftManager)
{
	m_draftManager = draftManager;
}

void SaveOperators::SaveDraft(Draft draft, std::list<Operator> operators)
{
	m_draftManager->TryInsertDraft(draft, operators);
}
