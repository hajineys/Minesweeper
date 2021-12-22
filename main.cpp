#include <conio.h>
#include <windows.h>
#include <time.h>

// 지뢰찾기 관련 내부 헤더파일
#include "main.h"
#include "define.h"
#include "GameApp.h"

/// <summary>
/// 메인 함수 시작
/// </summary>
int main()
{
	GameApp MineSweeper;
	MineSweeper.Initialize();

	/// 여기서부터 게임 루프 시작
	while (true)
	{
		MineSweeper.Loop();
	}

	return 0;
}