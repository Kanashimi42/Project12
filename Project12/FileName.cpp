#include <windows.h>
#include "windowsx.h"
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	static HWND hStatic1;
	static RECT rectButton;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG: {
		hStatic1 = GetDlgItem(hWnd, IDOK);
		GetWindowRect(hStatic1, &rectButton);
		ScreenToClient(hWnd, reinterpret_cast<LPPOINT>(&rectButton.left));
		ScreenToClient(hWnd, reinterpret_cast<LPPOINT>(&rectButton.right));
		InflateRect(&rectButton, 10, 10);

		return TRUE;
	}
	case WM_MOUSEMOVE: {
		POINT mousePos;
		mousePos.x = GET_X_LPARAM(lp);
		mousePos.y = GET_Y_LPARAM(lp);
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);
		BOOL cursorInButton = PtInRect(&rectButton, mousePos);
		if (cursorInButton) {
			SetWindowPos(hStatic1, nullptr, mousePos.x - rectButton.right / 2, mousePos.y - rectButton.bottom / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		}
	}
	}
	return FALSE;
}