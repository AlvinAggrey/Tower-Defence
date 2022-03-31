#pragma once
#include <vector>
#include <random>

class Roulette
{
	float m_sum;
	std::vector<float> m_wheel;

public:
	Roulette();
	Roulette(std::vector<float> wheel);

	void addSpace(float space);
	float spin();
	float calcPercentage(float num);

	//get set
	std::vector<float> getWheel();
};

