#pragma once

#include "../TextureEditorBusiness/Draft.h"
#include "../TextureEditorBusiness/Operator.h"
#include <list>

class DraftManager;
class LoadOperators;
class SaveOperators;
class PerlinOperators;

class TextureEditorDataStore
{
	DraftManager* m_draftManager;

	LoadOperators* m_loadOperators;
	SaveOperators* m_saveOperators;
	PerlinOperators* m_perlinOperators;

public:
	TextureEditorDataStore();

	void Save(Draft draft, std::list<Operator> operators);
};

