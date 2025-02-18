#include "DraftManager.h"

DraftManager::DraftManager()
{
}

/// <summary>
/// Returns, in the passed list, all Operators used by the specified draft 
/// </summary>
/// <param name="draft">The draft to retrieve</param>
/// <param name="operators">The list to put the operators into</param>
/// <returns>True if success, false if failed</returns>
bool DraftManager::TryGetDraft(Draft draft, std::list<Operator>& operators)
{
	auto it = m_drafts.find(draft.GetId());
	if (it != m_drafts.end()) {
		{
			//Lock mutex for the scope;
			std::unique_lock<std::mutex> lock(m_draftsMutex);
			operators = it->second;
			return true;
		}
	}
	return false;
}

/// <summary>
/// Insert the passed draft into the manager
/// </summary>
/// <param name="draft">The draft to insert</param>
/// <param name="operators">The Operators used by the specified draft</param>
/// <returns>True if success, False if failed</returns>
bool DraftManager::TryInsertDraft(Draft draft, std::list<Operator> operators)
{
	//Lock mutex for the scope;
	std::unique_lock<std::mutex> lock(m_draftsMutex);
	m_drafts.insert(std::pair(draft.GetId(), operators));
	return true;
}
