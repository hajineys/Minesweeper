#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <windows.h>
#include "new_conio.h"

class LHCGLib
{
public:
	LHCGLib();
	~LHCGLib();

private:
	// �ڵ��� �������� �� ���̴�. �� ���� ������ ����� �ʴ´�.
	HANDLE g_hConsole;

public:
	BOOL Initialize();

	void LHFillScreen(int ch);
	void LHFillScreenEx(const char* pStr);
	void LHLocateCursor(int x, int y);
	void LHPutChar(int x, int y, char ch);
	void LHPutAttrChar(int x, int y, char ch, WORD bg, WORD fg);
	void LHPutAttrCharEx(int x, int y, const char* pStr, WORD bg, WORD fg);
	void LHSetAttrChar(WORD bg, WORD fg);
	void LHSetCursor(DWORD dwSize, BOOL bVisible);
};
#endif // __CONSOLE_H__