#pragma once

#include "PerlinOperators.h"

class DraftClient;

//struct PerlinOperator::Data
//{
//	std::vector<unsigned char> res;
//};

class PerlinOperatorClient : PerlinOperator
{
public:
	int octave;
	int width;
	int height;
	float frequence;
	std::vector<unsigned char> res;

	std::vector<unsigned char> MakePerlin();
	//void Activate(DraftClient* draft) override;

	
};

