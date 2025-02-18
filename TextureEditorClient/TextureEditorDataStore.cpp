#include "TextureEditorDataStore.h"
#include "../TextureEditorBusiness/DraftManager.h"
#include "../TextureEditorBusiness/LoadOperators.h"
#include "../TextureEditorBusiness/SaveOperators.h"
#include "../TextureEditorBusiness/PerlinOperators.h"

TextureEditorDataStore::TextureEditorDataStore()
{
	m_draftManager = new DraftManager();

	m_loadOperators = new LoadOperators(m_draftManager);
	m_saveOperators = new SaveOperators(m_draftManager);
	m_perlinOperators = new PerlinOperators();
}

void TextureEditorDataStore::Save(Draft draft, std::list<Operator> operators)
{
	m_saveOperators->SaveDraft(draft, operators);
}
