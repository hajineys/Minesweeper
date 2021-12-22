#pragma once

class LHCGLib;

class Map
{
public:
	Map(LHCGLib* pCGEngine);
	~Map();

private:
	LHCGLib* m_pCGEngine;

	/// 1. 맵 초기화
	// 1-a 정보들이 담겨있는 맵과 정보를 가리는 맵 두개 생성
	int g_FrontMineBoard[16][16] = {};	// 가림판
	int g_BackMineBoard[16][16] = {};	// 정보판
	bool g_CheckMineBoard[16][16] = {};	// 오픈 체크 판

	// 지뢰찾기 2차원 배열에서 사용될 X, Y 좌표
	int MapX = 0;
	int MapY = 0;

	// 초급 지뢰찾기에 배치될 지뢰 갯수 
	int SetMineCount = 40;

public:
	// 게임 초기화 관련정보 모두 가지고 있는 함수
	void InitializeMineSweeper();

	void InitGameBoard();
	void ResetOpenCheck();
	void RandomSetMine();

	void DrawFrontMineBoard();
	void DrawOneBlock(int CellPosX, int CellPosY, int CellType);

	void CheckMyAreaMine(int PosX, int PosY);
	void CheckMineState(int CurPosX, int CurPosY);

	bool IsOpenCell(int x, int y);

	void ClearAllCheat();

	/// 새로 만든 함수
	int GetBackMineBoard(int playerPosX, int playerPosY);
	int GetFrontMineBoard(int playerPosX, int playerPosY);

	void SetBackMineBoard(int playerPosX, int playerPosY, int value);
	void SetFrontMineBoard(int playerPosX, int playerPosY, int value);

	int GetSetMineCount() const { return SetMineCount; }
	void SetSetMineCount(int val) { SetMineCount = val; }

	/// 캡슐화
	// 백보드에서 프론트보드로 복사한다.
	void CopyBackBoardToFrontBoard(int playerPosX, int playerPosY);
};