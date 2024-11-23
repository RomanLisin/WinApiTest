
#define _CRT_SECURE_NO_WARNINGS  // ��������� ��� ������ �4996
#include<Windows.h>
#include"resource.h"
#include<cstdio>



CONST CHAR* g_VALUES[] = { "This","is","my", "first","List","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//BOOL CALLBACK DlgProcAddItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
    /*
    ---------------------------
    WinMain
    hInstance - ��������� ������ ���������� � ������ (��������� *.exe-�����)
    hPrevInst - ���������� ���������� ��������� (Deprecated, ������������� � Windows 98).
    LPSTR lpCmdLine:
    LPSTR - LongPointer to String (��������� �� ������ ��������� const char*)
    lpCmdLine - ���������� ������ ������� ����������
    nCmdShow - ����� ����������� ����: �������� � ����, ���������� �� ���� �����, �������� � ����� �����......
    */
    DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
    return 0;

}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
       // HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
      //  SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
        HWND hListBox = GetDlgItem(hwnd, IDC_LIST);

        for (int i = 0; i < sizeof(g_VALUES) / sizeof(g_VALUES[0]); i++)
        {
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_VALUES[i]);
        }
        //HWND hButtonAdd = GetDlgItem(hwnd, IDC_BUTTON_ADD);
        //SetFocus(hButtonAdd);
        //SendMessage(hwnd, DM_SETDEFID, IDC_BUTTON_ADD, 0); // ����� ������������� '��������' �� ���������
    }
    break;
    case WM_COMMAND: {
        // ���������, ������ ������ ���������
        if (HIWORD(wParam) == LBN_SELCHANGE) {
            // ���� ��������� ����������, ����� �������� ���������
        }
        return 0;
    }
    case WM_KEYDOWN: {
        if (wParam == VK_DELETE) {
            // �������� ������ ����������� ��������
            int selIndex = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            if (selIndex != LB_ERR) {
                // ������� ���������� �������
                SendMessage(hListBox, LB_DELETESTRING, selIndex, 0);
            }
        }
        return 0;
    }
    case WM_KEYDOWN:
        switch (lParam)
        {
        case VK_DELETE:
            MessageBox(hwnd, "ListBox ������� Delete", "Info", MB_OK | MB_ICONINFORMATION);
            break;
        case VK_RETURN:
            MessageBox(hwnd, "ListBox ������� Return", "Info", MB_OK | MB_ICONINFORMATION);
            break;
        }
        break;
    case WM_COMMAND:
    {
        switch (HIWORD(wParam))
        {
       
        case LBN_SETFOCUS:
        {
            // MessageBox(hwnd, "ListBox ������� �����", "Info", MB_OK | MB_ICONINFORMATION);

         //HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
         //if ((HWND)lParam == hListBox)
         //{
         //    //OutputDebugString("ListBox ������� �����\n");
         //}
        }
        break;

        case LBN_DBLCLK:
        {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            if (i != LB_ERR)
            {
                CONST INT SIZE = 256;
                CHAR sz_buffer[SIZE]{};
                SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);

                CHAR sz_message[SIZE]{};
                sprintf(sz_message, "�� ������� �������: \"%s\".", sz_buffer);
                MessageBox(hwnd, sz_message, "Double Click", MB_OK | MB_ICONINFORMATION);
            }
        }
        break;

        /*case IDC_BUTTON_REMOVE:
        {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
            SendMessage(hListBox, LB_DELETESTRING, i, 0);
        }
        break;*/

        //case IDC_BUTTON_ADD:
        //    DialogBoxParam(GetModuleHandle(NULL) /*�������� hinstance*/
        //        , MAKEINTRESOURCE(IDD_DIALOG_ADD_ITEM), hwnd, DlgProcAddItem, 0);
        //    break;
        }
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            HWND hListBox = GetDlgItem(hwnd, IDC_LIST);
            CONST INT SIZE = 256;
            CHAR sz_buffer[SIZE]{};
            INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

            CHAR sz_message[SIZE]{};
            sprintf(sz_message, "�� ������� ������� N%i �� ��������� \"%s\".", i, sz_buffer);
            MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case IDCANCEL:
            EndDialog(hwnd, 0);
            break;
        }
    }
    break;

    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    }
    return FALSE;
}
