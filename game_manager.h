#pragma once

class LHCGLib;
class Map;

class GameManager
{
	// ������, �Ҹ���
public:
	GameManager(LHCGLib* pCGEngine, Map* pMap);
	~GameManager();

private:
	LHCGLib* m_pCGEngine;
	Map* m_pMap;

	// �ܺο� ���µ� �Լ���
public:
	void Title_v01();
	void Title_v02();

	void InfoController();

	bool CheckGameOver(int x, int y);
	bool CheckGameClear();
	int CheckGameState();

	void RestartGame();
	void ExitGame();
	void ClearGame();

	void ClearEndInfo();
	void ClearChar(int x, int y, int spaceCount);
};