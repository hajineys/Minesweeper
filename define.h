#pragma once

// 초급 9 * 9 / 중급 16 * 16 / 고급 30 * 16
// (나중에 맵 사이즈를 동적할당으로 커스터마이징 가능하도록 설정 필요)
//#define BOARD_WIDTH 16
//#define BOARD_HEIGHT 16

// 셀의 정보를 담고 있는 define
#define CELL_HIDE -1
#define CELL_EMPTY 0
#define CELL_CHECKMINE1 1
#define CELL_CHECKMINE2 2
#define CELL_CHECKMINE3 3
#define CELL_CHECKMINE4 4
#define CELL_CHECKMINE5 5
#define CELL_CHECKMINE6 6
#define CELL_CHECKMINE7 7
#define CELL_CHECKMINE8 8
#define CELL_MINE 9
#define CELL_FLAG 10

#define KEY_RIGHTMOVE 100
#define KEY_LEFTMOVE 101
#define KEY_UPMOVE 102
#define KEY_DOWNMOVE 103
#define KEY_SPACEOPEN 104
#define KEY_FLAG 105
#define KEY_NONE 106

#define KEY_CHEAT 999

#define KEY_SELEC 107

#define RESTART_GAME 0
#define EXIT_GAME 1

enum class eGameState
{
	TitleScene,
	InGame,
	GameOver,
	Win,
};