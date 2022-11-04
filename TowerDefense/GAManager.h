#pragma once
#include <vector>
#include <string>
#include "Roulette.h"
#include "Individual.h"

class GAManager
{
public:

	std::vector<Individual> m_curGen;
	std::vector<Individual> m_nextGen;

	int m_chromSize;
	int m_geneSize;
	int m_genSize;

	int m_totalIndiv;
	int m_curGenNum;

	GAManager();

	const std::vector<int> GenChrom();
	std::string GenName();
	Individual GenIndiv();

	void InitPop();
	void CalcFitness();
	void NextGen();
	void printGen();

	int GetGenNum();
	std::vector<Individual>* GetCurGen();

	//create next gen using roulette selection
	std::vector<Individual> rouletteSelection(int childNum, std::vector<Individual>& prevGen);

	Individual OnePointCrossOver(std::vector<int> parent1, std::vector<int> parent2);
};
