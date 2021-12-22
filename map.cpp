#include "map.h"
#include "define.h"
#include "ConsoleLib.h"
#include <time.h>

/// ��𿡵� ���� ��¥ �ٺ����� ����
///extern int NotHideCount;

Map::Map(LHCGLib* pCGEngine)
{
	m_pCGEngine = pCGEngine;
}

Map::~Map()
{

}

/// ����ã�� ����
void Map::InitializeMineSweeper()
{
	/// �׷������� �ʱ�ȭ
	// ������ ȭ���� �����ش�.
	m_pCGEngine->LHSetAttrChar(BG_BLACK, FG_WHITE);
	system("cls");

	// �ʱ�ȭ (���� ���� ��, �� �ѹ��� �Ͼ�� �ϴ� ��)
	InitGameBoard();

	// ������ üũ �� �ʱ�ȭ
	ResetOpenCheck();

	// �����ǿ� ���ڸ� �������� ����
	srand((UINT)time(NULL));
	RandomSetMine();

	// �����ǿ� ��� �迭�� �ڱ� �ֺ� 8ĭ�� �˻��Ͽ� ���ڰ����� ����Ѵ�
	for (int y = 0; y <= 15; y++)
	{
		for (int x = 0; x <= 15; x++)
		{
			CheckMyAreaMine(x, y);
		}
	}
}

// 1-b �������� -1�� �ʱ�ȭ, �������� 0���� �ʱ�ȭ
void Map::InitGameBoard()
{
	for (MapY = 0; MapY <= 15; MapY++)
	{
		for (MapX = 0; MapX <= 15; MapX++)
		{
			g_FrontMineBoard[MapY][MapX] = CELL_HIDE;
			g_BackMineBoard[MapY][MapX] = CELL_EMPTY;
		}
	}
}

void Map::ResetOpenCheck()
{
	for (MapY = 0; MapY <= 15; MapY++)
	{
		for (MapX = 0; MapX <= 15; MapX++)
		{
			g_CheckMineBoard[MapY][MapX] = false;
		}
	}
}

// 1-c 10���� ���ڸ� 9x9ĭ�� �������� ��ġ
void Map::RandomSetMine()
{
	while (0 < GetSetMineCount())
	{
		// MapX�� MapY�� ��ǥ���� �������� �̾Ƽ�
		// ���� ������ ��ǥ�� ���� ���� 9�� continue;
		// 9�� �ƴ϶�� ���ڸ� �ڴ´�, SetMineCount--; �� ���ش�

		MapX = rand() % 16;
		MapY = rand() % 16;

		if (g_BackMineBoard[MapY][MapX] == CELL_MINE)
		{
			continue;
		}

		g_BackMineBoard[MapY][MapX] = CELL_MINE;
		SetSetMineCount(GetSetMineCount() - 1);
	}

	// ���� ���� �ʱ�ȭ
	SetSetMineCount(40);
}

// 1-d ��� �迭�� ���鼭 ������ ���� ���ڰ� ����� ���
void Map::CheckMyAreaMine(int PosX, int PosY)
{
	int CheckMineNum = 0;

	if (g_BackMineBoard[PosY][PosX] == CELL_MINE)
	{
		return;
	}

	// Ư�� ��ǥ �»�ܺ��� ���ϴܱ��� Offset ���� �˻�
	for (int OffsetX = -1; OffsetX <= 1; OffsetX++)
	{
		for (int OffsetY = -1; OffsetY <= 1; OffsetY++)
		{
			int CheckPosX = OffsetX + PosX;
			int CheckPosY = OffsetY + PosY;

			if (CheckPosX < 0 || CheckPosY < 0 || CheckPosX > 15 || CheckPosY > 15)
			{
				// �ƹ��͵� ���� �ʴ´�
				continue;
			}

			// üũ ��� ����
			if (g_BackMineBoard[CheckPosY][CheckPosX] == CELL_MINE)
			{
				CheckMineNum++;
			}
		}
	}

	g_BackMineBoard[PosY][PosX] = CheckMineNum;
}

/// 2. �ʿ� ������ ���
void Map::DrawFrontMineBoard()
{
	for (MapY = 0; MapY <= 15; MapY++)
	{
		for (MapX = 0; MapX <= 15; MapX++)
		{
			DrawOneBlock(MapY, MapX, g_FrontMineBoard[MapX][MapY]);
		}
	}
}

// 2-a ���� � ���� ������ �ֳĿ� ���� ����� �ٸ��� ���ش�
// 2-b ���ڰ� �ƴ϶�� '��ĭ', ������ ���ڰ� ������������ '����', ���ڸ� '��' ǥ��
// 2-c ����� 'F'
// 2-d Ȯ���� �Ұ����� ���� '?' �� ǥ���Ѵ�(���� ����)
void Map::DrawOneBlock(int CellPosX, int CellPosY, int CellType)
{
	switch (CellType)
	{
	case CELL_HIDE: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LGRAY); break;
	case CELL_EMPTY: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LGRAY); break;
	case CELL_CHECKMINE1: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LBLUE); break;
	case CELL_CHECKMINE2: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LGREEN); break;
	case CELL_CHECKMINE3: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LRED); break;
	case CELL_CHECKMINE4: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LPURPLE); break;
	case CELL_CHECKMINE5: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LAQUA); break;
	case CELL_CHECKMINE6: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_PINK); break;
	case CELL_CHECKMINE7: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LYELLOW); break;
	case CELL_CHECKMINE8: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLACK, FG_LGRAY); break;
	case CELL_MINE: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_RED, FG_YELLOW); break;
	case CELL_FLAG: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "��", BG_BLUE, FG_LAQUA); break;
	}
}

/// 3. �� ���� Ȯ��
// 3-a ���ڸ� ����
// 3-b ���ڰ� �ƴϸ� 0�� ��� �ֺ� 8ĭ�� ���� ����
// 3-c ���ڰ� �ƴϰ� 0�� �ƴ� ��� �� ���� ����
void Map::CheckMineState(int CurPosX, int CurPosY)
{
	int CheckType = g_BackMineBoard[CurPosY][CurPosX];

	// ���� �� ��ġ�� �������� �̷����� ������ ������ ��� ��͸� ����
	if (CurPosX < 0 || 15 < CurPosX || CurPosY < 0 || 15 < CurPosY)
	{
		return;
	}

	// �� ��ġ�� 'üũ'�Ǿ��ٸ� ��͸� ����
	if (g_CheckMineBoard[CurPosY][CurPosX] == true)
	{
		return;
	}

	// üũ�� ���� �ʾ����Ƿ� üũ�� �Ѵ�
	g_CheckMineBoard[CurPosY][CurPosX] = true;

	// ��ĭ�̸� �ֺ� ���ڸ� üũ�ؼ� ��� �� ����
	if (CheckType == CELL_EMPTY)
	{
		// ����
		g_FrontMineBoard[CurPosY][CurPosX] = g_BackMineBoard[CurPosY][CurPosX];

		for (int OffsetY = -1; OffsetY <= 1; OffsetY++)
		{
			for (int OffsetX = -1; OffsetX <= 1; OffsetX++)
			{
				// �ڱ� �ڽ��� ������ �����ϵ��� �ϸ� �ȵȴ�
				if (OffsetX == 0 && OffsetY == 0)
				{
					continue;
				}

				CheckMineState(CurPosX + OffsetX, CurPosY + OffsetY);
			}
		}
	}
	// �����̸� ���õ� ���� ����
	else
	{
		// ����
		g_FrontMineBoard[CurPosY][CurPosX] = g_BackMineBoard[CurPosY][CurPosX];
	}

}

bool Map::IsOpenCell(int x, int y)
{
	// FrontMineBoard�� -1�� �ƴ� ���� ������ Open �Ǿ��ٰ� �Ǵ�
	if (g_FrontMineBoard[y][x] != CELL_HIDE)
	{
		return true;
	}

	return false;
}

void Map::ClearAllCheat()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (g_BackMineBoard[y][x] == CELL_MINE)
			{
				g_FrontMineBoard[y][x] = CELL_FLAG;
			}
			else if (g_BackMineBoard[y][x] != CELL_MINE)
			{
				g_FrontMineBoard[y][x] = g_BackMineBoard[y][x];
			}
		}
	}
}

int Map::GetBackMineBoard(int playerPosX, int playerPosY)
{
	return g_BackMineBoard[playerPosY][playerPosX];
}

int Map::GetFrontMineBoard(int playerPosX, int playerPosY)
{
	return g_FrontMineBoard[playerPosY][playerPosX];
}

void Map::SetBackMineBoard(int playerPosX, int playerPosY, int value)
{
	g_BackMineBoard[playerPosY][playerPosX] = value;
}

void Map::SetFrontMineBoard(int playerPosX, int playerPosY, int value)
{
	g_FrontMineBoard[playerPosY][playerPosX] = value;
}

void Map::CopyBackBoardToFrontBoard(int playerPosX, int playerPosY)
{
	g_FrontMineBoard[playerPosY][playerPosX] = g_BackMineBoard[playerPosY][playerPosX];
}