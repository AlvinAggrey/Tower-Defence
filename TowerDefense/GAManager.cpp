#include "GAManager.h"
#include <iostream>

#include <random>

GAManager::GAManager()
{
	m_chromSize = 20;
	m_geneSize = 3;

	m_curGenNum = 0;
	m_genSize = 4;
	m_totalIndiv = 0;
}

//generate chromosome
const std::vector<int> GAManager::GenChrom()
{
	std::vector<int> chrom;

	//dont forget parenthisis when using random_device
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> randUnit(1, 3);
	std::uniform_int_distribution<int> randX(0, 25);
	std::uniform_int_distribution<int> randY(0, 17);

	for (int i = 0; i < m_chromSize; i++)
	{
		//unit
		chrom.push_back(randUnit(gen));
		//coord x and y
		chrom.push_back(randX(gen));
		chrom.push_back(randY(gen));
	}

	return chrom;
}

std::string GAManager::GenName()
{
	std::string name = "Individual" + std::to_string(m_totalIndiv);
	return name;
}

//Generate and Indvidual in the population
Individual GAManager::GenIndiv()
{
	Individual indiv;
	indiv.m_chromosome = GenChrom();
	indiv.name = GenName();

	return indiv;
}

Individual GAManager::OnePointCrossOver(std::vector<int> parent1, std::vector<int> parent2)
{
	int crosspoint = ((m_chromSize/ 2) * m_geneSize);

	Individual child;
	child.name = GenName();
	child.m_chromosome = parent1;

	//add last half of parent2 chromosome to the child
	for (int i = crosspoint; i < m_chromSize * m_geneSize; i++)
	{
		child.m_chromosome[i] = parent2[i];
	}

	return child;
}


//create initial popluation
void GAManager::InitPop()
{
	for (int i = 0; i < m_genSize; i++)
	{
		m_curGen.push_back(GenIndiv());
		m_totalIndiv++;
	}
	printGen();
}

void GAManager::CalcFitness()
{
	for (int i = 0; i < (int)m_curGen.size(); i++)
	{
		m_curGen[i].m_fitness = 1;
	}
}

void GAManager::NextGen()
{
	int childNum = 2;
	
	m_curGen = rouletteSelection(2, m_curGen);
	m_curGenNum++;

	printGen();
}

void GAManager::printGen()
{
	std::cout << "---Population-" << m_curGenNum << "---" << std::endl;
	for (auto chromosome : m_curGen)
	{
		std::cout << chromosome.name << " ";
		for (auto geneSegment : chromosome.m_chromosome)
		{
			std::cout << geneSegment << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "---end---" << std::endl;
}
printChild
std::vector<Individual>* GAManager::GetCurGen()
{
	return &m_curGen;
}

std::vector<Individual> GAManager::rouletteSelection(int childNum, std::vector<Individual>& prevGen)
{
	std::vector<Individual> nextGen;
	Roulette roulette;

	
	//add to roulette wheel
	for (int i = 0; i < (int)prevGen.size(); i++)
	{
		Space space(&prevGen[i], prevGen[i].m_fitness);
		roulette.addSpace(space);
	}

	//add children to nextGen
	for (int i = 0; i < childNum; i++)
	{
		std::vector<int> parentChrom1 = roulette.spin().m_item->m_chromosome;
		std::vector<int> parentChrom2 = roulette.spin().m_item->m_chromosome;

		Individual child;// = OnePointCrossOver(parentChrom1, parentChrom2);
		child.name = GenName();

		nextGen.push_back(child);
		m_totalIndiv++;
	}
	//add randomly generated indivs to nextGen
	for (int i = childNum; i < m_genSize; i++)
	{
		nextGen.push_back(GenIndiv());
		m_totalIndiv++;
	}
	
	return nextGen;
}
