#pragma once
#include "define.h"

class LHCGLib;
class Map;
class GameManager;
class Player;

class GameApp
{
public:
	GameApp();
	~GameApp();

private:
	LHCGLib* m_pCGEngine;
	Map* m_pMap;
	GameManager* m_pGameManager;
	Player* m_pPlayer;

	// Key�Է��� ���� ����
	int KeyInput = 0;
	bool IsFirstMove = true;

	//extern int PlayerPosX;
	//extern int PlayerPosY;
	//extern int g_FrontMineBoard[16][16];

	// ���� ������ FSM�� State
	eGameState g_GameState = eGameState::TitleScene;

public:
	void Initialize();
	void Loop();

private:
	void MineSweeperFSM();
};