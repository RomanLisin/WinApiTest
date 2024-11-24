#include <windows.h>
#include <string>
#include <sstream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HFONT hFont = NULL;
    static int borderWidth = 5;
    static int titleHeight = 40;

    switch (uMsg) {
    case WM_CREATE: {
        // �������� ������ ROBOT ������� 30 ��������
        LOGFONT logFont = { 0 };
        logFont.lfHeight = 30;
        wcscpy_s(logFont.lfFaceName, L"Roboto");
        hFont = CreateFontIndirect(&logFont);
        return 0;
    }
    case WM_SIZE:
    case WM_MOVE: {
        // ��������� �������� ����
        RECT rect;
        GetWindowRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        // ���������� ���������
        std::wstringstream titleStream;
        titleStream << L"�������: " << width << L"x" << height
            << L", ����������: (" << rect.left << L", " << rect.top << L")";
        SetWindowText(hwnd, titleStream.str().c_str());
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // ��������� ���������
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        RECT titleRect = { 0, 0, clientRect.right, titleHeight };
        HBRUSH hBrush = CreateSolidBrush(RGB(211, 211, 211)); // ������-����� ����
        FillRect(hdc, &titleRect, hBrush);
        DeleteObject(hBrush);

        // ��������� ������ � ������
        SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT);
        DrawText(hdc, L"��������� ����", -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        DeleteObject(hFont);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"��������� ����",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // ��������� ������ �����
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_CAPTION);
    SetWindowPos(hwnd, NULL, 0, 0, 800, 600, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
