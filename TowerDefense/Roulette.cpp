#include "Roulette.h"

Space::Space()
{
	m_item = nullptr;
	m_size = 0;
}

Space::Space(Individual* indiv, float size)
{
	m_item = indiv;
	m_size = size;
}

Roulette::Roulette()
{
	m_wheel = {};
	m_sum = 0;
}

//add space to roulette
void Roulette::addSpace(Space space)
{
	m_wheel.push_back(space);
	m_sum += space.m_size;
}
//remove remove to roulette
void Roulette::removeSpace(unsigned int index)
{
	if (index != 0)
	{
		index -= 1;
	}

	m_wheel.erase(m_wheel.begin() + index);
	m_sum -= m_wheel[index].m_size;
}

//calculate how large a number is in ratio % to the sum 
float Roulette::calcPercentage(float num)
{
	return (num/m_sum);
}

Space* Roulette::find(Space space)
{
	for (int i = 0; i < (int)m_wheel.size(); i++)
	{
		//if they match
		if (m_wheel[i].m_item == space.m_item && m_wheel[i].m_size == space.m_size)
		{
			return &m_wheel[i];
		}
	}
	return nullptr;
}

//select chromosome
Space Roulette::spin()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0, 1);

	bool complete = false;
	Space result ;

	//keep spinning until a chromosome is picked
	if ((int)m_wheel.size() <= 0)
	{
		return result;
	}
	do
	{
		for (int i = 0; i < (int)m_wheel.size(); i++)
		{
			float randNum = dist(mt);
			float percentage = calcPercentage(m_wheel[i].m_size);

			if (randNum <= percentage)
			{
				complete = true;
				result = m_wheel[i];
				
				//remove space from wheel
				m_wheel.erase(m_wheel.begin() + i);
				break;
				//removeSpace(i);
			}
		}

	} while (complete == false);

	return result;

}

void Roulette::clear()
{
	m_wheel.clear();
}

std::vector<Space> Roulette::getWheel()
{
	return m_wheel;
}
