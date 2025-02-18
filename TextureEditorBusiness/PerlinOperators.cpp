#include "PerlinOperators.h"

PerlinOperator PerlinOperators::RegisterOperator(int octave, float frequence)
{
	//Creates a new Perlin Operator
	PerlinOperator perlin = PerlinOperator();

	//Inserts all operator data in maps
	{
		//Lock mutex for the scope;
		std::unique_lock<std::mutex> lock(operatorMutex);
		octaves.insert(std::pair(perlin.GetId(), octave));
		frequences.insert(std::pair(perlin.GetId(), frequence));
	}

	//Returns created Operator
	return perlin;
}

void PerlinOperators::DestroyOperator(PerlinOperator perlinOperator)
{
	//Lock mutex for the scope;
	std::unique_lock<std::mutex> lock(operatorMutex);
	//Removes data for the specified Perlin Operator
	octaves.erase(perlinOperator.GetId());
	frequences.erase(perlinOperator.GetId());
}

bool PerlinOperators::UpdateOperator(PerlinOperator perlinOperator, int octave, float frequence)
{
	//Updates octave and frequence for the specified Perlin Operator
	auto itOctave = octaves.find(perlinOperator.GetId());
	auto itFrequence = frequences.find(perlinOperator.GetId());
	if (itOctave != octaves.end() && itFrequence != frequences.end()) {
		{
			//Lock mutex for the scope;
			std::unique_lock<std::mutex> lock(operatorMutex);
			itOctave->second = octave;
			itFrequence->second = octave;
		}
	}
	else {
		//Returns failed update
		return false;
	}

	//Returns successful update
	return true;
}
