#include "GameApp.h"

// 콘솔 그래픽 라이브러리
#include "ConsoleLib.h"

// 콘솔 사운드 API
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
	// 그래픽스 엔진을 가장 먼저 생성한다.
	m_pCGEngine = new LHCGLib();

	m_pMap = new Map(m_pCGEngine);
	m_pGameManager = new GameManager(m_pCGEngine, m_pMap);

	m_pPlayer = new Player(m_pCGEngine, m_pMap);


	/// 시스템 초기화
	// 그래픽스 라이브러리 초기화
	if (m_pCGEngine->Initialize() == FALSE)
	{
		return;
	}

	PlaySound("../Sound/BG_sound.wav", NULL, SND_ASYNC | SND_LOOP);

	/// 콘솔창의 타이틀 변경
	SetConsoleTitle("■ 지뢰찾기 ■");

	/// 커서 사이즈 변경
	m_pCGEngine->LHSetCursor(100, TRUE);

	/// 스크린 사이즈 변경
	set_screen_size(300, 300);

	/// 전체 문자 컬러 속성 설정
	m_pCGEngine->LHSetAttrChar(BG_LGRAY, FG_BLACK);

	// 커서만 이동
	m_pCGEngine->LHLocateCursor(0, 0);

	// 지뢰찾기 초기화
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

			// 아무 키나 누르면, 게임을 시작한다(인게임 씬으로 간다)
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
			/// 입력
			// 키 입력, 그에 따른 이동 값을 만들어준다.
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

			/// 연산
			// 지뢰인가 아닌가?
			// 지뢰면 게임 아웃
			// 지뢰가 아니면 계속 진행

			/// 그리기
			// 맵을 모두 그린다
			m_pMap->DrawFrontMineBoard();
			m_pGameManager->InfoController();

			// UI를 그린다(시간, 남은 지뢰갯수등등)

			/// 게임상황 체크
			// 지뢰를 모두 찾고 배열에 가림판이 없다면 게임 클리어
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
					//(0)다시시작 / (1)게임종료 외 다른 키를 누르면 ERROR
					break;
				}
			}

			// 지뢰를 밟았다면 게임종료
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
					//(0)다시시작 / (1)게임종료 외 다른 키를 누르면 ERROR
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