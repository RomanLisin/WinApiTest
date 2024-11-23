#define _CRT_SECURE_NO_WARNINGS  // ��������� ��� ������ �4996
#include <windows.h>
#include <stdio.h>
#include "resource.h"

INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG: {
        HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"������� 1");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"������� 2");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"������� 3");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"������� 4");
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)"������� 5");
        return TRUE;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case IDCANCEL:
            EndDialog(hwnd, 0);
            return TRUE;
        }
        return FALSE;
    }
    case WM_KEYDOWN: { // �������� ������� ��������� WM_KEYDOWN
        char debugMsg[100];
        sprintf(debugMsg, "WM_KEYDOWN received: wParam = %d\n", wParam);
        OutputDebugString(debugMsg); // �������� � ���������� �����

        if (wParam == VK_DELETE) {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            int selIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            if (selIndex != LB_ERR) {
                SendMessage(hListBox, LB_DELETESTRING, selIndex, 0);
            }
            MessageBox(hwnd, "Delete pressed!", "Info", MB_OK);
        }
        return TRUE;
    }
    default:
        char debugMsg[100];
        sprintf(debugMsg, "Unhandled message: uMsg = %d\n", uMsg);
        OutputDebugString(debugMsg);
    }
    return FALSE;
}
