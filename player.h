#pragma once

class Player
{
public:
	Player(LHCGLib* pCGEngine, Map* pMap);
	~Player();

private:
	LHCGLib* m_pCGEngine;
	Map* m_pMap;

	// 플레이어가 가리키는 X, Y 좌표
	int PlayerPosX = 0;
	int PlayerPosY = 0;

public:
	void SetCursor();

	int Move();

	void Cursor_Right();
	void Cursor_Left();
	void Cursor_Up();
	void Cursor_Down();
	void Cursor_Open();
	void Cursor_Flag();

	/// 새로 만든 함수
	int GetPosX() const { return PlayerPosX; }
	int GetPosY() const { return PlayerPosY; }
};