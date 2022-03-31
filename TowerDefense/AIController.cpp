#include "AIController.h"
#include "Timer.h"
#include "GameState.h"
#include <iostream>
#include <Windows.h>

#include "GameController.h"

using namespace std;

AIController::AIController()
{
	m_gameController = nullptr;
	m_gameBoard = nullptr;
	m_Timer = nullptr;
	m_gameState = nullptr;
	m_step = 0;
	m_GAManager.InitPop();

	std::cout << "---Population---" << std::endl;
	for (auto chromosome : m_GAManager.m_population)
	{
		std::cout << chromosome.name << " ";
		for (auto geneSegment: chromosome.m_chromosome)
		{
			std::cout << geneSegment << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "---end---"<< std::endl;

	Individual child = m_GAManager.OnePointCrossOver(0, 1);

	std::cout << child.name << " ";
	for (auto geneSegment : child.m_chromosome)
	{
		std::cout << geneSegment << " ";
	}
	std::cout << "---end---" << std::endl;

}

AIController::~AIController()
{

}

void AIController::gameOver()
{
}
void AIController::Decision()
{
	vector<int> chromosome = m_GAManager.m_population[1].m_chromosome;

	if (m_step != (int)chromosome.size())
	{
		TowerType Tower = (TowerType)chromosome[m_step];

		int x = chromosome[m_step + 1];
		int y = chromosome[m_step + 2];

	
		int tamsRequired = m_gameState->getTowerProps(Tower)["tam"];

		if (m_gameState->getTams()>= tamsRequired)
		{
			addTower(Tower, x, y);
			m_step += 3;
		}
	}

}
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

void AIController::update()
{
	if (m_Timer == nullptr)
		return;

	// HINT
	// a second has elapsed - your GA manager (GA Code) may decide to do something at this time...
	static double elapsedSeconds = 0;
	double seconds = floor(m_Timer->elapsedSeconds());
	if (seconds > elapsedSeconds)
	{
		elapsedSeconds = seconds;

	}

	//GAManager::Instance()->Update(m_Timer->elapsedSeconds());

	// this might be useful? Monsters killed
	static int monstersKilled = 0;

	if (m_gameState->getMonsterEliminated() > monstersKilled)
	{
		monstersKilled = m_gameState->getMonsterEliminated();
	}

	std::cout << "Balls" << endl;

	Decision();

	recordScore();
}

//used to be void
bool AIController::addTower(TowerType type, int gridx, int gridy)
{
	// grid position can be from 0,0 to 25,17
	/*
	enum class TowerType {
	empty, slammer, swinger, thrower };
	*/

	bool towerAdded = m_gameBoard->addTower(type, gridx, gridy);

	// NOTE towerAdded might be false if the tower can't be placed in that position, is there isn't enough funds
	return towerAdded;
}

void AIController::setupBoard()
{
	m_Timer->start();
}

int AIController::recordScore()
{
	int currentWave = m_gameState->getCurrentWave();
	int killCount = m_gameState->getMonsterEliminated();
	currentWave *= 10; // living longer is good
	int score = currentWave + killCount;

	static int iteration = 0;

	if (iteration == 0)
		cout << "iteration" << "," << "wave" << "," << "kills" << "," << "score" << endl;

	cout << iteration << "," << m_gameState->getCurrentWave() << "," << m_gameState->getMonsterEliminated() << "," << score << endl;
	iteration++;

	m_gameState->setScore(score);

	return score;
}