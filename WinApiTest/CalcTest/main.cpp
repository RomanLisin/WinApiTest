#include <windows.h>
#include <commctrl.h>
#include <math.h>
#pragma comment(lib, "comctl32.lib")

#define IDC_BUTTON1 101
#define IDC_BUTTON2 102
#define TIMER_ID 1

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC OriginalButtonProc;
COLORREF buttonHoverColor = RGB(0, 102, 204); // Голубой цвет
COLORREF buttonNormalColor = RGB(0, 153, 255);
COLORREF buttonPressedColor = RGB(0, 51, 153);

void DrawButton(HWND hwnd, HDC hdc, COLORREF color, int depth);

struct ButtonState {
    bool isPressed;
    int depth; 

};

ButtonState buttonStates[2] = { {false, 0}, {false, 0} }; // Для кнопок

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    WNDCLASSEX wc = {};
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("FloatingCalculator");
    wc.hIcon = (HICON)LoadImage(NULL, "ICO\\calcExFox.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hIconSm = (HICON)LoadImage(NULL, "ICO\\calcExFox.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowEx(NULL, wc.lpszClassName, TEXT("Calculator"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200, 200, 300, 400,
        NULL, NULL, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    static HWND btn1, btn2;
    switch (msg) 
    {
         case WM_CREATE: 
         {
             btn1 = CreateWindow(TEXT("BUTTON"), TEXT("1"),
                 WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                 50, 50, 80, 40,
                 hwnd, (HMENU)IDC_BUTTON1, NULL, NULL);

             btn2 = CreateWindow(TEXT("BUTTON"), TEXT("2"),
                 WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                 150, 50, 80, 40,
                 hwnd, (HMENU)IDC_BUTTON2, NULL, NULL);

             // Подмена оконной процедуры кнопки
             OriginalButtonProc = (WNDPROC)SetWindowLongPtr(btn1, GWLP_WNDPROC, (LONG_PTR)ButtonProc);
             SetWindowLongPtr(btn2, GWLP_WNDPROC, (LONG_PTR)ButtonProc);

             // запуск таймера для анимации
             SetTimer(hwnd, TIMER_ID, 16, NULL); // 16 mc для ~60 FPS
         }
         break;
         case WM_TIMER:
         {
             if (wParam == TIMER_ID)
             {
                 bool needRedraw = false;
                 for (int i = 0; i < 2; i++)
                 {
                     if (buttonStates[i].depth > 0)
                     {
                         buttonStates[i].depth--;
                         needRedraw = true;
                     }
                 }
                 if (needRedraw)
                 {
                     InvalidateRect(hwnd, NULL, TRUE);
                 }
             }
         }
         break;

         case WM_COMMAND: 
         {
             int wmId = LOWORD(wParam);
             if (wmId == IDC_BUTTON1) 
             {
                 MessageBox(hwnd, TEXT("Button 1 Pressed"), TEXT("Info"), MB_OK);
             }
             else if (wmId == IDC_BUTTON2) 
             {
                 MessageBox(hwnd, TEXT("Button 2 Pressed"), TEXT("Info"), MB_OK);
             }
         }
         break;

         case WM_DESTROY:
         {
             KillTimer(hwnd, TIMER_ID);
             PostQuitMessage(0);
         }
         break;

         default:
         return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    //static BOOL isPressed = FALSE;
    //static int depth = 0; // Глубина утопания

    int buttonIndex = (GetDlgCtrlID(hwnd) == IDC_BUTTON1) ? 0 : 1;

    switch (msg) 
    {
       /* case WM_MOUSEMOVE:
             InvalidateRect(hwnd, NULL, TRUE);
        break;*/

        case WM_LBUTTONDOWN:
          {
         //isPressed = TRUE;
         buttonStates[buttonIndex].isPressed = true;
         buttonStates[buttonIndex].depth = 10; // Глубина утопания
         InvalidateRect(hwnd, NULL, TRUE);
          }
        break;

        case WM_LBUTTONUP:
         {
          //isPressed = FALSE;
          buttonStates[buttonIndex].isPressed = false;

          // Анимация возврата
         // SetTimer(hwnd, 1, 10, NULL);
          InvalidateRect(hwnd, NULL, TRUE);
         }
         break;

         /* case WM_TIMER:
        if (buttonStates[buttonIndex].depth > 0) {
            buttonStates[buttonIndex].depth--;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else {
            KillTimer(hwnd, 1);
        }
        break;*/

        case WM_DRAWITEM: 
        {
             LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
             HDC hdc = dis->hDC;
             COLORREF color = buttonNormalColor;

             if (buttonStates[buttonIndex].isPressed) 
             {
                 color = buttonPressedColor;
             }
             else if (dis->itemState & ODS_HOTLIGHT) 
             {
                 color = buttonHoverColor;
             }

             DrawButton(hwnd, hdc, color, buttonStates[buttonIndex].depth);
        }
           return TRUE;
    }

    return CallWindowProc(OriginalButtonProc, hwnd, msg, wParam, lParam);
}

void DrawButton(HWND hwnd, HDC hdc, COLORREF color, int depth)
{
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Смещение кнопки вниз
    OffsetRect(&rect, 0, depth);

    HBRUSH brush = CreateSolidBrush(color);
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

    CHAR text[256];
    GetWindowText(hwnd, text, 256);

    DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}