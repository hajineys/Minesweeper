#include "game_manager.h"
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "ConsoleLib.h"
#include "map.h"
#include "define.h"

///extern int g_FrontMineBoard[16][16];
///extern int SetMineCount;

GameManager::GameManager(LHCGLib* pCGEngine, Map* pMap)
{
	m_pCGEngine = pCGEngine;
	m_pMap = pMap;
}

GameManager::~GameManager()
{

}

// ���� Ÿ��Ʋ ����_01
void GameManager::Title_v01()
{
	printf("888b     d888 8888888 888b    888 8888888888      .d8888b.  888       888 8888888888 8888888888 8888888b.  8888888888 8888888b.\n");
	printf("8888b   d8888   888   8888b   888 888            d88P  Y88b 888   o   888 888        888        888   Y88b 888        888   Y88b\n");
	printf("88888b.d88888   888   88888b  888 888            Y88b.      888  d8b  888 888        888        888    888 888        888    888 \n");
	printf("888Y88888P888   888   888Y88b 888 8888888         'Y888b.   888 d888b 888 8888888    8888888    888   d88P 8888888    888   d88P \n");
	printf("888 Y888P 888   888   888 Y88b888 888                'Y88b. 888d88888b888 888        888        8888888P'  888        8888888P'\n");
	printf("888  Y8P  888   888   888  Y88888 888                  '888 88888P Y88888 888        888        888        888        888 T88b\n");
	printf("888   '   888   888   888   Y8888 888            Y88b  d88P 8888P   Y8888 888        888        888        888        888  T88b\n");
	printf("888       888 8888888 888    Y888 8888888888      'Y8888P'  888P     Y888 8888888888 8888888888 888        8888888888 888   T88b\n");
}

// ���� Ÿ��Ʋ ����_02
void GameManager::Title_v02()
{
	m_pCGEngine->LHPutAttrCharEx(0, 0, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 1, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 2, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 3, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 4, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 5, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 6, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 7, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 8, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 9, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 10, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 11, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 12, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 13, "�����������������", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 14, "�����������������", BG_LGRAY, FG_BLACK);

	m_pCGEngine->LHPutAttrCharEx(0, 15, "�ƹ� Ű�� ������ ������ ����˴ϴ�!", BG_LGRAY, FG_BLACK);
}

// ���� ���۹� �ȳ�
void GameManager::InfoController()
{
	m_pCGEngine->LHPutAttrCharEx(0, 16, "Ŀ�� ���� : �̵�Ű ����䢹", BG_LGRAY, FG_BLACK);
	m_pCGEngine->LHPutAttrCharEx(0, 17, "���� : SPACE / ���(��) : ENTER", BG_LGRAY, FG_BLACK);
}

// ���ڸ� Ŭ���ϸ� ���ӿ��� ���� ���
bool GameManager::CheckGameOver(int x, int y)
{
	// ���ڸ� ������ ���ӿ��� TURE
	// ���ڰ� �ƴϸ� ���� ��� ���� FALSE
	if (m_pMap->GetFrontMineBoard(x, y) == CELL_MINE)
	{
		m_pCGEngine->LHPutAttrCharEx(0, 19, "���ڸ� ��ҽ��ϴ�!", BG_LGRAY, FG_BLACK); sleep(500);
		m_pCGEngine->LHPutAttrCharEx(0, 20, "GAME OVER!", BG_LGRAY, FG_BLACK); sleep(500);
		return true;
	}

	return false;
}

bool GameManager::CheckGameClear()
{
	int CheckClearCellCount = 0;

	// ���ڸ� �����ϰ� ���� �迭�� ��� �����ߴٸ� ���� Ŭ����
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (m_pMap->GetFrontMineBoard(x, y) != CELL_HIDE)
			{
				CheckClearCellCount++;
			}
		}
	}

	if (CheckClearCellCount == ((16 * 16) - m_pMap->GetSetMineCount()))
	{
		return true;
	}

	return false;
}

int GameManager::CheckGameState()
{
	m_pCGEngine->LHPutAttrCharEx(0, 22, "(0)�ٽý��� / (1)��������", BG_LGRAY, FG_BLACK); sleep(500);

	// Ű�Է��� ���� �ٽý���, �������� ����
	int Key_Input = 0;
	
	m_pCGEngine->LHLocateCursor(0, 23);
	
	std::cin >> Key_Input;

	switch (Key_Input)
	{
		case RESTART_GAME:
		{
			RestartGame();
			return RESTART_GAME;
		}
		break;

		case EXIT_GAME:
		{
			ExitGame();
			return EXIT_GAME;
		}
		break;
	}

	// RESTART_GAME�� EXIT_GAME �ܿ� �ٸ� �Է°��� �Է��ϸ� ����
	return 999;
}

void GameManager::RestartGame()
{
	// ���� �ٽý���
	m_pCGEngine->LHPutAttrCharEx(0, 23, "������ �ٽ� �����մϴ�", BG_LGRAY, FG_BLACK); sleep(1000);
}

void GameManager::ExitGame()
{
	// ���� ����, â �ݱ�
	m_pCGEngine->LHPutAttrCharEx(0, 23, "������ �����մϴ�", BG_LGRAY, FG_BLACK); sleep(1000);
}

void GameManager::ClearGame()
{
	PlaySound("Game_clear.wav", NULL, SND_ASYNC);

	m_pCGEngine->LHPutAttrCharEx(0, 19, "������ Ŭ�����߽��ϴ�!", BG_LGRAY, FG_BLACK); sleep(1000);
	m_pCGEngine->LHPutAttrCharEx(0, 20, "GAME CLEAR!", BG_LGRAY, FG_BLACK); sleep(500);
}

void GameManager::ClearEndInfo()
{
	ClearChar(0, 19, 30);
	ClearChar(0, 20, 30);
	ClearChar(0, 22, 30);
	ClearChar(0, 23, 30);
	ClearChar(0, 24, 30);
}

void GameManager::ClearChar(int x, int y, int spaceCount)
{
	for (int index = x; index <= spaceCount; index++)
	{
		m_pCGEngine->LHPutAttrChar(index, y, ' ', BG_BLACK, FG_BLACK);
	}
}