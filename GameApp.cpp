#include "GameApp.h"

// �ܼ� �׷��� ���̺귯��
#include "ConsoleLib.h"

// �ܼ� ���� API
#include "playsoundapi.h"

#include "map.h"
#include "player.h"
#include "game_manager.h"

GameApp::GameApp()
	:m_pCGEngine(nullptr),
	m_pMap(nullptr),
	m_pGameManager(nullptr),
	m_pPlayer(nullptr)
{

}

GameApp::~GameApp()
{

}

void GameApp::Initialize()
{
	// �׷��Ƚ� ������ ���� ���� �����Ѵ�.
	m_pCGEngine = new LHCGLib();

	m_pMap = new Map(m_pCGEngine);
	m_pGameManager = new GameManager(m_pCGEngine, m_pMap);

	m_pPlayer = new Player(m_pCGEngine, m_pMap);


	/// �ý��� �ʱ�ȭ
	// �׷��Ƚ� ���̺귯�� �ʱ�ȭ
	if (m_pCGEngine->Initialize() == FALSE)
	{
		return;
	}

	PlaySound("../Sound/BG_sound.wav", NULL, SND_ASYNC | SND_LOOP);

	/// �ܼ�â�� Ÿ��Ʋ ����
	SetConsoleTitle("�� ����ã�� ��");

	/// Ŀ�� ������ ����
	m_pCGEngine->LHSetCursor(100, TRUE);

	/// ��ũ�� ������ ����
	set_screen_size(300, 300);

	/// ��ü ���� �÷� �Ӽ� ����
	m_pCGEngine->LHSetAttrChar(BG_LGRAY, FG_BLACK);

	// Ŀ���� �̵�
	m_pCGEngine->LHLocateCursor(0, 0);

	// ����ã�� �ʱ�ȭ
	m_pMap->InitializeMineSweeper();
}

void GameApp::Loop()
{
	MineSweeperFSM();
}


void GameApp::MineSweeperFSM()
{
	switch (g_GameState)
	{
		case eGameState::TitleScene:
		{
			m_pGameManager->Title_v02();

			// �ƹ� Ű�� ������, ������ �����Ѵ�(�ΰ��� ������ ����)
			KeyInput = m_pPlayer->Move();

			if (KeyInput != KEY_NONE)
			{
				m_pCGEngine->LHSetAttrChar(BG_BLACK, FG_WHITE);
				system("cls");
				g_GameState = eGameState::InGame;
			}
		}
		break;

		case eGameState::InGame:
		{
			/// �Է�
			// Ű �Է�, �׿� ���� �̵� ���� ������ش�.
			KeyInput = m_pPlayer->Move();
			sleep(100);

			switch (KeyInput)
			{
				case KEY_RIGHTMOVE: { m_pPlayer->Cursor_Right(); }; break;
				case KEY_LEFTMOVE: { m_pPlayer->Cursor_Left(); }; break;
				case KEY_UPMOVE: { m_pPlayer->Cursor_Up(); }; break;
				case KEY_DOWNMOVE: { m_pPlayer->Cursor_Down(); }; break;
				case KEY_SPACEOPEN: {m_pPlayer->Cursor_Open(); IsFirstMove = false; }; break;
				case KEY_FLAG: { m_pPlayer->Cursor_Flag(); }; break;
				case KEY_CHEAT: { m_pMap->ClearAllCheat(); }; break;
			}

			m_pPlayer->SetCursor();

			/// ����
			// �����ΰ� �ƴѰ�?
			// ���ڸ� ���� �ƿ�
			// ���ڰ� �ƴϸ� ��� ����

			/// �׸���
			// ���� ��� �׸���
			m_pMap->DrawFrontMineBoard();
			m_pGameManager->InfoController();

			// UI�� �׸���(�ð�, ���� ���ڰ������)

			/// ���ӻ�Ȳ üũ
			// ���ڸ� ��� ã�� �迭�� �������� ���ٸ� ���� Ŭ����
			if (IsFirstMove == false && m_pGameManager->CheckGameClear() == true)
			{
				m_pGameManager->ClearGame();

				int IsGameClear = m_pGameManager->CheckGameState();

				if (IsGameClear == EXIT_GAME)
				{
					g_GameState = eGameState::GameOver;
				}
				else if (IsGameClear == RESTART_GAME)
				{
					g_GameState = eGameState::TitleScene;

					m_pMap->InitializeMineSweeper();
					PlaySound("../Sound/BG_sound.wav", NULL, SND_ASYNC | SND_LOOP);
				}
				else
				{
					//(0)�ٽý��� / (1)�������� �� �ٸ� Ű�� ������ ERROR
					break;
				}
			}

			// ���ڸ� ��Ҵٸ� ��������
			if (m_pGameManager->CheckGameOver(m_pPlayer->GetPosX(), m_pPlayer->GetPosY()))
			{
				int IsGameEnd = m_pGameManager->CheckGameState();

				if (IsGameEnd == EXIT_GAME)
				{
					g_GameState = eGameState::GameOver;
				}
				else if (IsGameEnd == RESTART_GAME)
				{
					g_GameState = eGameState::TitleScene;

					m_pMap->InitializeMineSweeper();
					PlaySound("../Sound/BG_sound.wav", NULL, SND_ASYNC | SND_LOOP);
				}
				else
				{
					//(0)�ٽý��� / (1)�������� �� �ٸ� Ű�� ������ ERROR
					break;
				}
			}
		}
		break;

		case eGameState::GameOver:
		{
			return;
		}
		break;

		case eGameState::Win:
		{
			return;
		}
		break;
	}
}