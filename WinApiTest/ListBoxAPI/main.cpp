/// в этом коде работает появление окна редактирования при двойном нажатии мыши и изменяет содержимое строки, но не работает ENTER

//#include <windows.h>
//#include <tchar.h>
//#include "resource.h"
//
//// Прототипы функций
//BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//void EditListBoxItem(HWND hwndDlg);
//
//HINSTANCE hInst;
//
//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
//    hInst = hInstance;
//    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
//}
//
//BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    static HWND hListBox;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        hListBox = GetDlgItem(hwndDlg, IDC_LIST);
//        // Добавляем элементы в список
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 1"));
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 2"));
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 3"));
//        return TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDC_LIST && HIWORD(wParam) == LBN_DBLCLK) {
//            EditListBoxItem(hwndDlg);
//        }
//        break;
//
//    case WM_KEYDOWN:
//        if (wParam == VK_RETURN) {
//            EditListBoxItem(hwndDlg);
//        }
//        break;
//
//    case WM_CLOSE:
//        EndDialog(hwndDlg, 0);
//        return TRUE;
//    }
//    return FALSE;
//}
//
//void EditListBoxItem(HWND hwndDlg) {
//    HWND hListBox = GetDlgItem(hwndDlg, IDC_LIST);
//    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
//
//    if (selectedIndex != LB_ERR) {
//        TCHAR buffer[256] = { 0 };
//        // Получаем текст выбранного элемента
//        SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)buffer);
//
//        // Показываем диалог редактирования
//        if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwndDlg,
//            [](HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) -> INT_PTR {
//                static TCHAR* editBuffer;
//                switch (uMsg) {
//                case WM_INITDIALOG:
//                    editBuffer = (TCHAR*)lParam;
//                    SetDlgItemText(hDlg, IDC_EDIT, editBuffer);
//                    return TRUE;
//
//                case WM_COMMAND:
//                    if (LOWORD(wParam) == IDOK) {
//                        GetDlgItemText(hDlg, IDC_EDIT, editBuffer, 256);
//                        EndDialog(hDlg, IDOK);
//                        return TRUE;
//                    }
//                    else if (LOWORD(wParam) == IDCANCEL) {
//                        EndDialog(hDlg, IDCANCEL);
//                        return TRUE;
//                    }
//                    break;
//                }
//                return FALSE;
//            }, (LPARAM)buffer) == IDOK) {
//
//            // Обновляем текст в списке
//            SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
//            SendMessage(hListBox, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer);
//        }
//    }
//}

//...................................................................................
//#include <windows.h>
//#include <tchar.h>
//#include "resource.h"
//
//// Прототипы функций
//BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//void EditListBoxItem(HWND hwndDlg);
//void DeleteListBoxItem(HWND hwndDlg);
//
//HINSTANCE hInst;
//
//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
//    hInst = hInstance;
//    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
//}
//
//BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    static HWND hListBox;
//
//    switch (uMsg) {
//    case WM_INITDIALOG:
//        hListBox = GetDlgItem(hwndDlg, IDC_LIST);
//        // Добавляем элементы в список
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 1"));
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 2"));
//        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 3"));
//        return TRUE;
//
//    case WM_COMMAND:
//        switch (LOWORD(wParam)) {
//        case IDC_LIST:
//            if (HIWORD(wParam) == LBN_DBLCLK) {
//                EditListBoxItem(hwndDlg);
//            }
//            break;
//        }
//        break;
//
//    case WM_KEYDOWN:
//        if (wParam == VK_RETURN) {
//            EditListBoxItem(hwndDlg);
//            return TRUE;
//        }
//        else if (wParam == VK_DELETE) {
//            DeleteListBoxItem(hwndDlg);
//            return TRUE;
//        }
//        break;
//
//    case WM_CLOSE:
//        EndDialog(hwndDlg, 0);
//        return TRUE;
//    }
//
//    // Обработка системных сообщений клавиатуры
//    MSG msg;
//    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
//        if (!IsDialogMessage(hwndDlg, &msg)) {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return FALSE;
//}
//
//void EditListBoxItem(HWND hwndDlg) {
//    HWND hListBox = GetDlgItem(hwndDlg, IDC_LIST);
//    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
//
//    if (selectedIndex != LB_ERR) {
//        TCHAR buffer[256] = { 0 };
//        // Получаем текст выбранного элемента
//        SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)buffer);
//
//        // Показываем диалог редактирования
//        if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwndDlg,
//            [](HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) -> INT_PTR 
//            {
//                static TCHAR* editBuffer;
//                switch (uMsg) {
//                case WM_INITDIALOG:
//                    editBuffer = (TCHAR*)lParam;
//                    SetDlgItemText(hDlg, IDC_EDIT, editBuffer);
//                    return TRUE;
//
//                case WM_COMMAND:
//                    if (LOWORD(wParam) == IDOK) {
//                        GetDlgItemText(hDlg, IDC_EDIT, editBuffer, 256);
//                        EndDialog(hDlg, IDOK);
//                        return TRUE;
//                    }
//                    else if (LOWORD(wParam) == IDCANCEL) {
//                        EndDialog(hDlg, IDCANCEL);
//                        return TRUE;
//                    }
//                    break;
//                }
//                return FALSE;
//            }, (LPARAM)buffer) == IDOK) {
//
//            // Обновляем текст в списке
//            SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
//            SendMessage(hListBox, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer);
//        }
//    }
//}
//
//void DeleteListBoxItem(HWND hwndDlg) {
//    HWND hListBox = GetDlgItem(hwndDlg, IDC_LIST);
//    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
//
//    if (selectedIndex != LB_ERR) {
//        // Удаляем выбранный элемент
//        SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
//    }
//}
//  ..................................................................................................................

#include <windows.h>
#include <tchar.h>
#include "resource.h"

// Прототипы функций
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void EditListBoxItem(HWND hwndDlg);
void DeleteListBoxItem(HWND hwndDlg);

HINSTANCE hInst;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hListBox;

    switch (uMsg) {
    case WM_INITDIALOG:
        hListBox = GetDlgItem(hwndDlg, IDC_LIST);
        // Добавляем элементы в список
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 1"));
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 2"));
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)_T("Элемент 3"));
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_LIST:
            if (HIWORD(wParam) == LBN_DBLCLK) {
                EditListBoxItem(hwndDlg);
            }
            break;
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_RETURN) {
            EditListBoxItem(hwndDlg);
            return TRUE;
        }
        else if (wParam == VK_DELETE) {
            DeleteListBoxItem(hwndDlg);
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    }

    return FALSE;
}

void EditListBoxItem(HWND hwndDlg) {
    HWND hListBox = GetDlgItem(hwndDlg, IDC_LIST);
    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

    if (selectedIndex != LB_ERR) {
        TCHAR buffer[256] = { 0 };
        // Получаем текст выбранного элемента
        SendMessage(hListBox, LB_GETTEXT, selectedIndex, (LPARAM)buffer);

        // Показываем диалог редактирования
        if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwndDlg, EditDialogProc, (LPARAM)buffer) == IDOK) {

            // Обновляем текст в списке
            SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
            SendMessage(hListBox, LB_INSERTSTRING, selectedIndex, (LPARAM)buffer);
        }
    }
}

void DeleteListBoxItem(HWND hwndDlg) {
    HWND hListBox = GetDlgItem(hwndDlg, IDC_LIST);
    int selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);

    if (selectedIndex != LB_ERR) {
        // Удаляем выбранный элемент
        SendMessage(hListBox, LB_DELETESTRING, selectedIndex, 0);
    }
}

BOOL CALLBACK EditDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static CHAR* editBuffer;

    switch (uMsg) {
    case WM_INITDIALOG:
        editBuffer = (CHAR*)lParam;
        SetDlgItemText(hDlg, IDC_EDIT, editBuffer);
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            GetDlgItemText(hDlg, IDC_EDIT, editBuffer, 256);
            EndDialog(hDlg, IDOK);
            return TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
