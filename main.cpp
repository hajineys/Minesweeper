#include <conio.h>
#include <windows.h>
#include <time.h>

// ����ã�� ���� ���� �������
#include "main.h"
#include "define.h"
#include "GameApp.h"

/// <summary>
/// ���� �Լ� ����
/// </summary>
int main()
{
	GameApp MineSweeper;
	MineSweeper.Initialize();

	/// ���⼭���� ���� ���� ����
	while (true)
	{
		MineSweeper.Loop();
	}

	return 0;
}