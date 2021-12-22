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
	// ▶ 누르면 오른쪽으로 이동
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		return KEY_RIGHTMOVE;
	}

	// ◀ 누르면 왼쪽으로 이동 
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		return KEY_LEFTMOVE;
	}

	// ▲ 누르면 위쪽으로 이동
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		return KEY_UPMOVE;
	}

	// ▼ 누르면 아래쪽으로 이동
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		return KEY_DOWNMOVE;
	}

	// 스페이스바 누르면 셀 열기
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

// ▶ 누르면 PlayerPosX +1만큼 이동
void Player::Cursor_Right()
{
	// 커서의 위치가 맵 배열 범위 밖을 벗어나면 리턴!
	if (15 <= PlayerPosX)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosX = PlayerPosX + 1;
}

// ▶ 누르면 PlayerPosX -1만큼 이동
void Player::Cursor_Left()
{
	// 커서의 위치가 맵 배열 범위 밖을 벗어나면 리턴!
	if (PlayerPosX <= 0)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosX = PlayerPosX - 1;
}

// ▶ 누르면 PlayerPosY -1만큼 이동
void Player::Cursor_Up()
{
	// 커서의 위치가 맵 배열 범위 밖을 벗어나면 리턴!
	if (PlayerPosY <= 0)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosY = PlayerPosY - 1;
}

// ▶ 누르면 PlayerPosY +1만큼 이동
void Player::Cursor_Down()
{
	// 커서의 위치가 맵 배열 범위 밖을 벗어나면 리턴!
	if (15 <= PlayerPosY)
	{
		return;
	}

	PlaySound("../Sound/Cursor_move.wav", NULL, SND_ASYNC);
	PlayerPosY = PlayerPosY + 1;
}

// 스페이스바 누르면 커서가 가리키는 셀 값 오픈
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
	
	// 숫자
	if (m_pMap->GetBackMineBoard(PlayerPosX, PlayerPosY) != CELL_EMPTY)
	{
		//g_FrontMineBoard[PlayerPosY][PlayerPosX] = g_BackMineBoard[PlayerPosY][PlayerPosX];
		m_pMap->CopyBackBoardToFrontBoard(PlayerPosX, PlayerPosY);
	}

	// 빈 칸
	m_pMap->CheckMineState(PlayerPosX, PlayerPosY);
}

void Player::Cursor_Flag()
{
	// 가림판 일때 깃발을 세운다
	if (m_pMap->GetFrontMineBoard(PlayerPosX, PlayerPosY) == CELL_HIDE)
	{
		m_pMap->SetFrontMineBoard(PlayerPosX, PlayerPosY ,CELL_FLAG);
	}
	// 가리키는 커서의 셀이 이미 깃발일때는 깃발을 없애준다
	else if (m_pMap->GetFrontMineBoard(PlayerPosX, PlayerPosY) == CELL_FLAG)
	{
		m_pMap->SetFrontMineBoard(PlayerPosX, PlayerPosY, CELL_HIDE);
	}
	//숫자나 빈칸이면 깃발을 세우지 못한다
	else
	{
		return;
	}
}