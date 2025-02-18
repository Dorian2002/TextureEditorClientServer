#pragma once

#include "Draft.h"
#include <list>
#include "Operator.h"
#include <queue>
#include <vector>
#include "Rgba.h"

class DraftClient : Draft
{
	std::queue<std::vector<Rgba>> images;
	std::list<Operator*> operators;
};

