#include "SavesOperator.h"
#include "DraftManager.h"

SavesOperator::SavesOperator(DraftManager* draftManager)
{
	m_draftManager = draftManager;
}

void SavesOperator::SaveDraft(Draft draft, std::list<Operator> operators)
{
	m_draftManager->TryInsertDraft(draft, operators);
}
