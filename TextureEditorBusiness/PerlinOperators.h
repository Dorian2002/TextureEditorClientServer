#pragma once
#include <unordered_map>
#include "Operator.h"
#include <mutex>

//From Operator.h
CREATE_OPERATOR_CLASS(PerlinOperator);

class PerlinOperators
{
	std::mutex m_operatorMutex;
	std::unordered_map<_GUID*, int> m_octaves;
	std::unordered_map<_GUID*, float> m_frequences;

public:
	PerlinOperators();

	/// <summary>
	/// Register a new Perlin Operator
	/// </summary>
	/// <param name="octave">The octave to apply to the perlin algorithm</param>
	/// <param name="frequence">The frequence to apply to the perlin algorithm</param>
	/// <returns>The the created Operator</returns>
	PerlinOperator RegisterOperator(int octave, float frequence);

	/// <summary>
	/// Destroy the specified Operator
	/// </summary>
	/// <param name="perlinOperator">The Operator to destroy</param>
	void DestroyOperator(PerlinOperator perlinOperator);

	/// <summary>
	/// Update the the specified operator with the passed values
	/// </summary>
	/// <param name="perlinOperator">The Operator to update</param>
	/// <returns>true if succes, false if failed</returns>
	bool UpdateOperator(PerlinOperator perlinOperator, int octave, float frequence);
};
