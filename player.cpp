#include "ConsoleLib.h"
#include "map.h"
#include "player.h"
#include "game_manager.h"
#include "define.h"

///extern int g_FrontMineBoard[16][16];
///extern int g_BackMineBoard[16][16];

Player::Player(LHCGLib* pCGEngine, Map* pMap)
{
	m_pCGEngine = pCGEngine;
	m_pMap = pMap;
}

Player::~Player()
{

}


void Player::SetCursor()
{
	m_pCGEngine->LHLocateCursor(PlayerPosX * 2, PlayerPosY);
}

int Player::Move()
{
	// �� ������ ���������� �̵�
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		return KEY_RIGHTMOVE;
	}

	// �� ������ �������� �̵� 
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		return KEY_LEFTMOVE;
	}

	// �� ������ �������� �̵�
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		return KEY_UPMOVE;
	}

	// �� ������ �Ʒ������� �̵�
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		return KEY_DOWNMOVE;
	}

	// �����̽��� ������ �� ����
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		return KEY_SPACEOPEN;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		return KEY_FLAG;
	}

	if (GetAsyncKeyState(VK_BACK) & 0x8000)
	{
		return KEY_CHEAT;
	}

	return KEY_NONE;
}

// �� ������ PlayerPosX +1��ŭ �̵�
void Player::Cursor_Right()
{
	// Ŀ���� ��ġ�� �� �迭 ���� ���� ����� ����!
	if (15 <= PlayerPosX)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosX = PlayerPosX + 1;
}

// �� ������ PlayerPosX -1��ŭ �̵�
void Player::Cursor_Left()
{
	// Ŀ���� ��ġ�� �� �迭 ���� ���� ����� ����!
	if (PlayerPosX <= 0)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosX = PlayerPosX - 1;
}

// �� ������ PlayerPosY -1��ŭ �̵�
void Player::Cursor_Up()
{
	// Ŀ���� ��ġ�� �� �迭 ���� ���� ����� ����!
	if (PlayerPosY <= 0)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosY = PlayerPosY - 1;
}

// �� ������ PlayerPosY +1��ŭ �̵�
void Player::Cursor_Down()
{
	// Ŀ���� ��ġ�� �� �迭 ���� ���� ����� ����!
	if (15 <= PlayerPosY)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosY = PlayerPosY + 1;
}

// �����̽��� ������ Ŀ���� ����Ű�� �� �� ����
void Player::Cursor_Open()
{
	// back board : empty, number, mine
	if (m_pMap->GetBackMineBoard(PlayerPosX, PlayerPosY) == CELL_MINE)
	{
		PlaySound("../Sound/Mine_explosion.wav", NULL, SND_ASYNC);
		
		//g_FrontMineBoard[PlayerPosY][PlayerPosX] = g_BackMineBoard[PlayerPosY][PlayerPosX];
		//m_pMap->SetFrontMineBoard(PlayerPosX, PlayerPosY, m_pMap->GetBackMineBoard(PlayerPosX, PlayerPosY));
		m_pMap->CopyBackBoardToFrontBoard(PlayerPosX, PlayerPosY);
	}
	
	// ����
	if (m_pMap->GetBackMineBoard(PlayerPosX, PlayerPosY) != CELL_EMPTY)
	{
		//g_FrontMineBoard[PlayerPosY][PlayerPosX] = g_BackMineBoard[PlayerPosY][PlayerPosX];
		m_pMap->CopyBackBoardToFrontBoard(PlayerPosX, PlayerPosY);
	}

	// �� ĭ
	m_pMap->CheckMineState(PlayerPosX, PlayerPosY);
}

void Player::Cursor_Flag()
{
	// ������ �϶� ����� �����
	if (m_pMap->GetFrontMineBoard(PlayerPosX, PlayerPosY) == CELL_HIDE)
	{
		m_pMap->SetFrontMineBoard(PlayerPosX, PlayerPosY ,CELL_FLAG);
	}
	// ����Ű�� Ŀ���� ���� �̹� ����϶��� ����� �����ش�
	else if (m_pMap->GetFrontMineBoard(PlayerPosX, PlayerPosY) == CELL_FLAG)
	{
		m_pMap->SetFrontMineBoard(PlayerPosX, PlayerPosY, CELL_HIDE);
	}
	//���ڳ� ��ĭ�̸� ����� ������ ���Ѵ�
	else
	{
		return;
	}
}