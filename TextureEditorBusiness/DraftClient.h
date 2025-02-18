#pragma once

#include "Draft.h"
#include <list>
#include "Operator.h"
#include <queue>
#include <vector>
#include "Rgba.h"

class DraftClient : Draft
{

public :


	std::queue<std::vector<unsigned char>> images;
	std::list<Operator*> operators;

	void AddOperator(Operator* op);
};

