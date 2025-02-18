#include "PerlinOperators.h"

PerlinOperator PerlinOperators::RegisterOperator(int octave, float frequence)
{
	//Creates a new Perlin Operator
	PerlinOperator perlin = PerlinOperator();

	//Inserts all operator data in maps
	{
		//Lock mutex for the scope;
		std::unique_lock<std::mutex> lock(m_operatorMutex);
		m_octaves.insert(std::pair(perlin.GetId(), octave));
		m_frequences.insert(std::pair(perlin.GetId(), frequence));
	}

	//Returns created Operator
	return perlin;
}

void PerlinOperators::DestroyOperator(PerlinOperator perlinOperator)
{
	//Lock mutex for the scope;
	std::unique_lock<std::mutex> lock(m_operatorMutex);
	//Removes data for the specified Perlin Operator
	m_octaves.erase(perlinOperator.GetId());
	m_frequences.erase(perlinOperator.GetId());
}

bool PerlinOperators::UpdateOperator(PerlinOperator perlinOperator, int octave, float frequence)
{
	//Updates octave and frequence for the specified Perlin Operator
	auto itOctave = m_octaves.find(perlinOperator.GetId());
	auto itFrequence = m_frequences.find(perlinOperator.GetId());
	if (itOctave != m_octaves.end() && itFrequence != m_frequences.end()) {
		{
			//Lock mutex for the scope;
			std::unique_lock<std::mutex> lock(m_operatorMutex);
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
