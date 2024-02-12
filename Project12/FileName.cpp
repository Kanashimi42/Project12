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

		return TRUE;
	}
	case WM_MOUSEMOVE: {
		POINT mousePos;
		mousePos.x = GET_X_LPARAM(lp);
		mousePos.y = GET_Y_LPARAM(lp);
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		GetWindowRect(hStatic1, &rectButton);
		ScreenToClient(hWnd, reinterpret_cast<LPPOINT>(&rectButton.left));
		ScreenToClient(hWnd, reinterpret_cast<LPPOINT>(&rectButton.right));
		InflateRect(&rectButton, 10, 10);

		//get away from mouse 
		int newX = rectButton.left;
		int newY = rectButton.top;
		if (mousePos.x == rectButton.right)
		{
			newX = mousePos.x - rectButton.right / 2;
		}
		else if (mousePos.x == rectButton.left)
		{
			newX = mousePos.x + rectButton.left / 2;
		}

		if (mousePos.y == rectButton.bottom)
		{
			newY = mousePos.y - rectButton.bottom / 2;
		}
		else if (mousePos.y == rectButton.top)
		{
			newY = mousePos.y + rectButton.top / 2;
		}

		//dont go out of dialogbox
		RECT rectDialog;
		GetClientRect(hWnd, &rectDialog);

		if (newX < rectDialog.left)
			newX = rectDialog.left;
		if (newX + rectButton.right - rectButton.left > rectDialog.right)
			newX = rectDialog.right - (rectButton.right - rectButton.left);
		if (newY < rectDialog.top)
			newY = rectDialog.top;
		if (newY + rectButton.bottom - rectButton.top > rectDialog.bottom)
			newY = rectDialog.bottom - (rectButton.bottom - rectButton.top);

		BOOL cursorInButton = PtInRect(&rectButton, mousePos);
		if (cursorInButton) {
			SetWindowPos(hStatic1, nullptr, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		}
	}
	}
	return FALSE;
}