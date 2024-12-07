#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ShowNumber(HWND, int);
int CalcIt(int, char, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "Calc";
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass;

    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = DLGWINDOWEXTRA;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = (LPCWSTR)szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndclass);

    hwnd = CreateDialogA((DWORD)hInstance, (LPCWSTR)szAppName, 0, NULL);
    ShowWindow(hwnd, iCmdShow);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void ShowNumber(HWND hwnd, int number)
{
    char szBuffer[20];
    _itoa_s(number, szBuffer, 10);
    SetDlgItemText(hwnd, IDC_EDIT1,(LPCWSTR)szBuffer);
}

int CalcIt(int firstNum, char operation, int secondNum)
{
    switch (operation)
    {
    case '+': return firstNum + secondNum;
    case '-': return firstNum - secondNum;
    case '*': return firstNum * secondNum;
    case '/': return secondNum ? firstNum / secondNum : 0;
    default: return 0;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static int firstNum = 0, secondNum = 0;
    static char operation = 0;
    static BOOL newNumber = TRUE;

    switch (iMsg)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) >= IDC_BUTTON0 && LOWORD(wParam) <= IDC_BUTTON9)
        {
            if (newNumber)
            {
                firstNum = 0;
                newNumber = FALSE;
            }
            firstNum = firstNum * 10 + (LOWORD(wParam) - IDC_BUTTON0);
            ShowNumber(hwnd, firstNum);
        }
        else if (LOWORD(wParam) == IDC_BUTTONPLUS || LOWORD(wParam) == IDC_BUTTONMINUS ||
            LOWORD(wParam) == IDC_BUTTONMULT || LOWORD(wParam) == IDC_BUTTONDIV)
        {
            if (!newNumber)
            {
                secondNum = firstNum;
                firstNum = 0;
                newNumber = TRUE;
            }
            operation = LOWORD(wParam);
        }
        else if (LOWORD(wParam) == IDC_BUTTONEQUAL)
        {
            if (operation)
            {
                firstNum = CalcIt(secondNum, operation, firstNum);
                ShowNumber(hwnd, firstNum);
                operation = 0;
            }
        }
        else if (LOWORD(wParam) == IDC_BUTTONCLEAR)
        {
            firstNum = 0;
            secondNum = 0;
            operation = 0;
            ShowNumber(hwnd, 0);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
