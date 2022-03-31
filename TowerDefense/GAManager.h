#pragma once
#include <vector>
#include <string>

struct Individual
{
	Individual() {};
	std::vector<int> m_chromosome;
	float m_fitness = 0;
	std::string name;
};

class GAManager
{
public:
	//typedef chromosone;
	std::vector<Individual> m_population;

	int m_chromSize;
	int m_geneSize;
	int m_popSize;
	int m_digitsPerGene;
	int m_totalIndiv;

	GAManager();

	const std::vector<int> GenChrom();
	std::string GenName();
	Individual GenIndiv();

	void InitPop();
	void Add();
	void Replace();
	void CalcFitness();
	Individual OnePointCrossOver(int indiv1, int indiv2);
};

//const int popSize = 6;
//const int genesPerChrom = 20;
//const int geneSize = 3;
//const int chromSize = genesPerChrom * geneSize;
//
////create chroms
//for (int i = 0; i < popSize; i++)
//{
//
//	int chromosome[chromSize];
//	for (int i = 0; i < chromSize; i += 3)
//	{
//		//unit
//		chromosome[i] = rand() % 3;
//		//screen Dimension 0,0 to 25,17
//		//pos x and y
//		chromosome[i + 1] = rand() % 25;
//		chromosome[i + 2] = rand() % 17;
//
//	}
//	std::cout << chromosome << "\n";
//}
