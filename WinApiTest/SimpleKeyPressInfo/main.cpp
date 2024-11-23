#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
//#include <tchar.h>
#include<cstdio>
#include "resource.h"  // ���������, ��� � ��� ���� ���� �������� � IDD_DIALOG1 � IDC_LIST

// ��������� �������
BOOL CALLBACK WndProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, INT nCmdShow) 
{
    // ������ ����������� ����
    return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WndProc,0);
}

BOOL CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    CHAR szMessage[256];

    switch (uMsg) 
    {
        case WM_SYSKEYDOWN:
        {
            sprintf(szMessage, "Key pressed: %c", HIWORD(wParam));
            MessageBox(hWnd, szMessage, "Key Pressed", MB_OK);
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}