#pragma once

class LHCGLib;
class Map;

class GameManager
{
	// 생성자, 소멸자
public:
	GameManager(LHCGLib* pCGEngine, Map* pMap);
	~GameManager();

private:
	LHCGLib* m_pCGEngine;
	Map* m_pMap;

	// 외부에 오픈된 함수들
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