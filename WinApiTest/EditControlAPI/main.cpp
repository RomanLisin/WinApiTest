#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST WCHAR* init_values[] = { L" опируемый текс", L"должен быть таким" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hEditCtrl1 = GetDlgItem(hwnd, IDC_EDIT2);
		CONST INT SIZE = 512;
		WCHAR sz_buffer[SIZE] = L"";
		for (int i = 0; i < sizeof(init_values) / sizeof(init_values[0]); i++)
		{
			//SendMessage(hEditCtrl1, LB_ADDSTRING, 0, (LPARAM)init_values[i]);
			wcscat_s(sz_buffer, SIZE, init_values[i]);
			wcscat_s(sz_buffer, SIZE, L"\r\n");  // переход на новую строку
		
		}
			SetWindowText(hEditCtrl1, sz_buffer);
	break;
	}
	//return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT2);
			CONST INT SIZE = 256;
			WCHAR sz_buffer[SIZE]{};
			//CHAR sz_message[SIZE]{};
			//INT i = SendMessage(hEdit, LB_GETCURSEL, 0, 0); // return index of select item
			//SendMessage(hEdit, LB_GETTEXT, i, (LPARAM)sz_buffer);
			//sprintf(sz_message, "¬ы выбрали пункт N%i со значением \"%s\".", i, sz_buffer);
			GetWindowText(hEdit,sz_buffer, SIZE);
			MessageBox(hwnd, sz_buffer, L"Select value", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case IDCANCEL: EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
	{
		EndDialog(hwnd, 0); // button x work
		break;
	}
	}
	return FALSE;
}