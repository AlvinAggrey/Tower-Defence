#pragma once
#include <vector>
#include <random>
#include "Individual.h"

struct Space
{
	Space();
	Space(Individual* indiv, float size);
	Individual* m_item;
	float m_size;
};

class Roulette
{
	float m_sum;
	std::vector<Space> m_wheel;

public:
	Roulette();

	void addSpace(Space space);
	void removeSpace(unsigned int index);
	float calcPercentage(float num);
	Space* find(Space space);
	Space spin();

	void clear();

	//get set
	std::vector<Space> getWheel();

};

