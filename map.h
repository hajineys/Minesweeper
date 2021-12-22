#pragma once

class LHCGLib;

class Map
{
public:
	Map(LHCGLib* pCGEngine);
	~Map();

private:
	LHCGLib* m_pCGEngine;

	/// 1. �� �ʱ�ȭ
	// 1-a �������� ����ִ� �ʰ� ������ ������ �� �ΰ� ����
	int g_FrontMineBoard[16][16] = {};	// ������
	int g_BackMineBoard[16][16] = {};	// ������
	bool g_CheckMineBoard[16][16] = {};	// ���� üũ ��

	// ����ã�� 2���� �迭���� ���� X, Y ��ǥ
	int MapX = 0;
	int MapY = 0;

	// �ʱ� ����ã�⿡ ��ġ�� ���� ���� 
	int SetMineCount = 40;

public:
	// ���� �ʱ�ȭ �������� ��� ������ �ִ� �Լ�
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

	/// ���� ���� �Լ�
	int GetBackMineBoard(int playerPosX, int playerPosY);
	int GetFrontMineBoard(int playerPosX, int playerPosY);

	void SetBackMineBoard(int playerPosX, int playerPosY, int value);
	void SetFrontMineBoard(int playerPosX, int playerPosY, int value);

	int GetSetMineCount() const { return SetMineCount; }
	void SetSetMineCount(int val) { SetMineCount = val; }

	/// ĸ��ȭ
	// �麸�忡�� ����Ʈ����� �����Ѵ�.
	void CopyBackBoardToFrontBoard(int playerPosX, int playerPosY);
};