#include "Roulette.h"

Roulette::Roulette()
{
	m_wheel = {};
	m_sum = 0;
}
Roulette::Roulette(std::vector<float> wheel)
{
	m_wheel = wheel;
	m_sum = 0;

	//add to sum
	for (int i = 0; i < m_wheel.size(); i++)
	{
		m_sum += m_wheel[i];
	}
}

//add number to roulette
void Roulette::addSpace(float space)
{
	m_wheel.push_back(space);
	m_sum += space;
}
//calculate how large a number is in ratio % to the sum 
float Roulette::calcPercentage(float num)
{
	return (num/m_sum) * 100;
}

std::vector<float> Roulette::getWheel()
{
	return m_wheel;
}

//select chromosome
float Roulette::spin()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(1, 100);

	bool complete = false;
	float result;

	//keep spinning until a chromosome is picked
	do
	{
		for (int i = 0; i < m_wheel.size(); i++)
		{
			float randNum = dist(mt);
			float percentage = calcPercentage(m_wheel[i]);

			if (randNum <= percentage)
			{
				complete = true;
				result = m_wheel[i];
			}
		}

	} while (complete == false);

	return result;
}
