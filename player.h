#pragma once

class Player
{
public:
	Player(LHCGLib* pCGEngine, Map* pMap);
	~Player();

private:
	LHCGLib* m_pCGEngine;
	Map* m_pMap;

	// �÷��̾ ����Ű�� X, Y ��ǥ
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

	/// ���� ���� �Լ�
	int GetPosX() const { return PlayerPosX; }
	int GetPosY() const { return PlayerPosY; }
};