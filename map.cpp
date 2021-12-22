#include "map.h"
#include "define.h"
#include "ConsoleLib.h"
#include <time.h>

/// 어디에도 없는 진짜 근본없는 변수
///extern int NotHideCount;

Map::Map(LHCGLib* pCGEngine)
{
	m_pCGEngine = pCGEngine;
}

Map::~Map()
{

}

/// 지뢰찾기 시작
void Map::InitializeMineSweeper()
{
	/// 그래픽적인 초기화
	// 이전의 화면을 지워준다.
	m_pCGEngine->LHSetAttrChar(BG_BLACK, FG_WHITE);
	system("cls");

	// 초기화 (게임 시작 후, 단 한번만 일어나야 하는 것)
	InitGameBoard();

	// 셀오픈 체크 판 초기화
	ResetOpenCheck();

	// 정보판에 지뢰를 랜덤으로 생성
	srand((UINT)time(NULL));
	RandomSetMine();

	// 정보판에 모든 배열이 자기 주변 8칸을 검사하여 지뢰갯수를 출력한다
	for (int y = 0; y <= 15; y++)
	{
		for (int x = 0; x <= 15; x++)
		{
			CheckMyAreaMine(x, y);
		}
	}
}

// 1-b 가림판을 -1로 초기화, 정보판은 0으로 초기화
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

// 1-c 10개의 지뢰를 9x9칸에 랜덤으로 배치
void Map::RandomSetMine()
{
	while (0 < GetSetMineCount())
	{
		// MapX와 MapY의 좌표값을 랜덤으로 뽑아서
		// 뽑은 랜덤한 좌표가 가진 값이 9면 continue;
		// 9가 아니라면 지뢰를 박는다, SetMineCount--; 를 해준다

		MapX = rand() % 16;
		MapY = rand() % 16;

		if (g_BackMineBoard[MapY][MapX] == CELL_MINE)
		{
			continue;
		}

		g_BackMineBoard[MapY][MapX] = CELL_MINE;
		SetSetMineCount(GetSetMineCount() - 1);
	}

	// 지뢰 갯수 초기화
	SetSetMineCount(40);
}

// 1-d 모든 배열을 돌면서 인접한 셀에 지뢰가 몇개인지 기록
void Map::CheckMyAreaMine(int PosX, int PosY)
{
	int CheckMineNum = 0;

	if (g_BackMineBoard[PosY][PosX] == CELL_MINE)
	{
		return;
	}

	// 특정 좌표 좌상단부터 우하단까지 Offset 범위 검사
	for (int OffsetX = -1; OffsetX <= 1; OffsetX++)
	{
		for (int OffsetY = -1; OffsetY <= 1; OffsetY++)
		{
			int CheckPosX = OffsetX + PosX;
			int CheckPosY = OffsetY + PosY;

			if (CheckPosX < 0 || CheckPosY < 0 || CheckPosX > 15 || CheckPosY > 15)
			{
				// 아무것도 하지 않는다
				continue;
			}

			// 체크 계속 수행
			if (g_BackMineBoard[CheckPosY][CheckPosX] == CELL_MINE)
			{
				CheckMineNum++;
			}
		}
	}

	g_BackMineBoard[PosY][PosX] = CheckMineNum;
}

/// 2. 맵에 정보를 출력
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

// 2-a 셀이 어떤 값을 가지고 있냐에 따라 출력을 다르게 해준다
// 2-b 지뢰가 아니라면 '빈칸', 주위에 지뢰가 근접해있으면 '숫자', 지뢰면 '※' 표시
// 2-c 깃발은 'F'
// 2-d 확인이 불가능한 셀은 '?' 로 표시한다(구현 예정)
void Map::DrawOneBlock(int CellPosX, int CellPosY, int CellType)
{
	switch (CellType)
	{
	case CELL_HIDE: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "■", BG_BLACK, FG_LGRAY); break;
	case CELL_EMPTY: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "□", BG_BLACK, FG_LGRAY); break;
	case CELL_CHECKMINE1: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "①", BG_BLACK, FG_LBLUE); break;
	case CELL_CHECKMINE2: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "②", BG_BLACK, FG_LGREEN); break;
	case CELL_CHECKMINE3: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "③", BG_BLACK, FG_LRED); break;
	case CELL_CHECKMINE4: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "④", BG_BLACK, FG_LPURPLE); break;
	case CELL_CHECKMINE5: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "⑤", BG_BLACK, FG_LAQUA); break;
	case CELL_CHECKMINE6: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "⑥", BG_BLACK, FG_PINK); break;
	case CELL_CHECKMINE7: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "⑦", BG_BLACK, FG_LYELLOW); break;
	case CELL_CHECKMINE8: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "⑧", BG_BLACK, FG_LGRAY); break;
	case CELL_MINE: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "★", BG_RED, FG_YELLOW); break;
	case CELL_FLAG: m_pCGEngine->LHPutAttrCharEx(CellPosX * 2, CellPosY, "♠", BG_BLUE, FG_LAQUA); break;
	}
}

/// 3. 한 셀을 확인
// 3-a 지뢰면 죽음
// 3-b 지뢰가 아니면 0인 경우 주변 8칸에 대해 실행
// 3-c 지뢰가 아니고 0이 아닌 경우 그 셀을 연다
void Map::CheckMineState(int CurPosX, int CurPosY)
{
	int CheckType = g_BackMineBoard[CurPosY][CurPosX];

	// 조사 할 위치가 게임판의 이론적인 범위를 나갔을 경우 재귀를 종료
	if (CurPosX < 0 || 15 < CurPosX || CurPosY < 0 || 15 < CurPosY)
	{
		return;
	}

	// 이 위치가 '체크'되었다면 재귀를 종료
	if (g_CheckMineBoard[CurPosY][CurPosX] == true)
	{
		return;
	}

	// 체크가 되지 않았으므로 체크를 한다
	g_CheckMineBoard[CurPosY][CurPosX] = true;

	// 빈칸이면 주변 지뢰를 체크해서 계속 셀 오픈
	if (CheckType == CELL_EMPTY)
	{
		// 오픈
		g_FrontMineBoard[CurPosY][CurPosX] = g_BackMineBoard[CurPosY][CurPosX];

		for (int OffsetY = -1; OffsetY <= 1; OffsetY++)
		{
			for (int OffsetX = -1; OffsetX <= 1; OffsetX++)
			{
				// 자기 자신을 무한히 조사하도록 하면 안된다
				if (OffsetX == 0 && OffsetY == 0)
				{
					continue;
				}

				CheckMineState(CurPosX + OffsetX, CurPosY + OffsetY);
			}
		}
	}
	// 숫자이면 선택된 셀만 오픈
	else
	{
		// 오픈
		g_FrontMineBoard[CurPosY][CurPosX] = g_BackMineBoard[CurPosY][CurPosX];
	}

}

bool Map::IsOpenCell(int x, int y)
{
	// FrontMineBoard에 -1이 아닌 값이 들어오면 Open 되었다고 판단
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