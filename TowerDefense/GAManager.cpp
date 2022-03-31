#include "GAManager.h"
#include <random>

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

Individual GAManager::OnePointCrossOver(int indiv1, int indiv2)
{
	int crosspoint = ((m_chromSize/ 2) * m_geneSize);

	std::vector<int> parent1;
	std::vector<int> parent2;

	parent1 = m_population[indiv1].m_chromosome;
	parent2 = m_population[indiv2].m_chromosome;



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


GAManager::GAManager()
{
	m_population = {};

	m_chromSize = 20;
	m_geneSize = 3;
	m_popSize = 4;
	m_digitsPerGene = 3;
	
	m_totalIndiv = 0;
}

//create initial popluation
void GAManager::InitPop()
{
	for (int i = 0; i < m_popSize; i++)
	{
		m_population.push_back(GenIndiv());
		m_totalIndiv++;
	}
}

void GAManager::CalcFitness()
{
}