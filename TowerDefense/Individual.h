#pragma once
#include <vector>
#include <string>

struct Individual
{
public:
	Individual() {};
	std::vector<int> m_chromosome;
	float m_fitness = 0;
	std::string name;
};