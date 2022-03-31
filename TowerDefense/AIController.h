#pragma once

#include "Tower.h"
#include "GAManager.h"

class GameController;
class GameBoard;
class Timer;
class GameState;

class AIController
{
public:
	AIController();
	~AIController();

	void setupBoard();
	int  recordScore();

	void setGameController(GameController* gameController) { m_gameController = gameController; }
	void setGameBoard(GameBoard* gameBoard) { m_gameBoard = gameBoard; }
	void setTimer(Timer* timer) { m_Timer = timer; }
	void setGameState(GameState* gameState) { m_gameState = gameState; }
	void update();
	bool addTower(TowerType type, int gridx, int gridy);
	void gameOver();
	void Decision();
	int m_step;
private:
	GAManager m_GAManager;
	GameController* m_gameController;
	GameBoard*		m_gameBoard;
	Timer*			m_Timer;
	GameState*		m_gameState;
};

