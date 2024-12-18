#include <Windows.h>
#include<cstdio>
#include<string>
#include"resource.h"
#define TIMER_ID 1
int faillingStep = 0;
int wWidth{}, wHeight{}, x{}, y{};
	HDC hdc{};
	CHAR sz_buff[256] = {};
	HWND hwnd{};
	HCURSOR hCursor = NULL;
	MSG msg{};
BOOL WINAPI /*������� � ���, ��� ���������� ������ ����� ��� �� ����� ������� ����*/
wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass{ sizeof(WNDCLASSEX) };//<-� ������� ���������� ������������� ���a��//* ������ ������, ��� ������ �����������, ����� ����� ������ � ����
	wClass.cbClsExtra = 0;  // ��� ��� ���� �������� �� �������������� ��������� ������  // CountBytes
	wClass.cbWndExtra = 0;  // ����� ����� ���� �������� ���������� � ����� ����, ����� ����� ����� ���� ��������������� ���� �����������, �������� ������ � ������
	wClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));	     //* �����  �������� reinterpret_cast ->  https://learn.microsoft.com/ru-ru/cpp/cpp/reinterpret-cast-operator?view=msvc-170
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);										 //* ������
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);										 //* ������ �������
	wClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);									 //* ������ ���������
	wClass.hInstance = hInstance;															 //* ����������
	wClass.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT	 //* ���������     // ��� �������� [] (������-�������)? https://docs.google.com/document/d/1_THS_7VJuPY20n1fowRICpFB0hsZYURYKrG0dG4Z3uc/edit?usp=sharing
		{
			switch (uMsg)
			{
			case WM_INITDIALOG:
			{

				HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
				SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
				break;
			}
			case WM_CREATE:
			{
				hCursor = LoadCursorFromFile("ANI\\3work.ani");
				if (!hCursor)
				{
					MessageBox(hwnd, "�� ������� ��������� ������", "������", MB_ICONERROR);
				}
				//������������������� ����
				// Set WS_EX_LAYERED on this window 
				SetWindowLong(hWnd,
					GWL_EXSTYLE,
					GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

				// Make this window 95% alpha
				int alfaChanel = 95; 
				SetLayeredWindowAttributes(hWnd, 0, (255 * alfaChanel) / 100, LWA_ALPHA);

				RECT rc;
				GetWindowRect(hWnd, &rc);

				int screenWidth = GetSystemMetrics(SM_CXSCREEN);
				int screenHeight = GetSystemMetrics(SM_CYSCREEN);
				
				wWidth = screenWidth * 75 / 100;
				wHeight = screenHeight * 75 / 100;
				int xPos = (screenWidth - wWidth)/2;//(rc.right - rc.left)/* ���_������*/ ) / 2;               ���_������ = SM_CXSCREEN * 75 / 100
				int yPos = (screenHeight - wHeight)/2; //(rc.bottom - rc.top)) / 2;

				SetWindowPos(hWnd, NULL, xPos, yPos, wWidth, wHeight, SWP_NOZORDER); // | SWP_NOSIZE);
			}
			return 0;
			case WM_SIZE:
			{
				wWidth = LOWORD(lParam);
				wHeight = HIWORD(lParam);
				//CHAR title[100];
				snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight);
				SetWindowText(hWnd, sz_buff);
				break;
			}
			case WM_MOVE:
			{
				x = LOWORD(lParam);
				y = HIWORD(lParam);
				//CHAR title[200];
				snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight);
				SetWindowText(hWnd, sz_buff);
				break;
			}
			case WM_MOVING: {
				// ������������ ���������� ��������� �� ����� ��������������
				RECT* rect = reinterpret_cast<RECT*>(lParam);
				x = rect->left;
				y = rect->top;

				//wchar_t title[200];
				snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight);
				SetWindowText(hwnd, sz_buff);
				break;
			}
			case WM_SETCURSOR:
			{
				if (LOWORD(lParam) == HTCLIENT && hCursor)
				{
					SetCursor(hCursor);
					return TRUE;
				}
				break;
			}
			return 0;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				
				// ��������� ���������
				RECT rect = { 50,0, wWidth, 150 };
				SetBkColor(hdc, RGB(30, 30, 30));
				SetTextColor(hdc, RGB(255, 255, 255));
				//TextOut(hdc, 50, 0, sz_buff, snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight));
				DrawText(hdc, sz_buff, -1, &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				//hdc = GetDC(hWnd);
				//DrawCaption(hWnd, hdc, NULL, snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight));
				//hdc->unused
				EndPaint(hwnd, &ps);
				break;
			}
			//return 0;
			//case WM_TIMER:
			//{
			//	if (wParam == TIMER_ID)
			//	{
			//		RECT rect;
			//		GetWindowRect(hWnd, &rect);

			//		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

			//		// ������� ����
			//		int newY = rect.top + 20;
			//		if (newY >= screenHeight)
			//		{
			//			KillTimer(hWnd, TIMER_ID);
			//			DestroyWindow(hWnd); // �������� ���� ����� ���������� ��������
			//		}
			//		else
			//		{
			//			// ���������� ������, �������� "����������"
			//			int newHeight = max((rect.bottom - rect.top) - 10, 50);

			//			MoveWindow(hWnd, rect.left, newY, rect.right - rect.left, newHeight, TRUE);
			//		}
			//	}
			//}
			//break;
			//case WM_CLOSE:
			//{
			//	SetTimer(hWnd, TIMER_ID, 30, NULL); // ������������� ������ ��� ��������
			//	return 0; // ��������� ����������� ��������
			//}
			case WM_NCLBUTTONDOWN: {
				if (wParam == HTCAPTION) {
					// ��������� ��������� ����� ������� ��������������
					RECT rect;
					GetWindowRect(hwnd, &rect);
					x = rect.left;
					y = rect.top;

					//wchar_t title[200];
					snprintf(sz_buff, sizeof(sz_buff), " X %d x Y %d : W %d x H %d", x, y, wWidth, wHeight);
					SetWindowText(hwnd,sz_buff);
				}
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
			case WM_LBUTTONDOWN:
			{
				//�������������� ����
				PostMessage(hwnd, WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
				break;
			}

			case WM_DESTROY:
			{
				if (hCursor)
				{
					DestroyCursor(hCursor);
				}
				PostQuitMessage(EXIT_SUCCESS);
				break;
			}
			default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
			return 0;
		};

	wClass.lpszClassName = "AppClassName";													  //* ��� ������
	wClass.lpszMenuName = NULL;															  //* ����
	wClass.style = CS_VREDRAW | CS_HREDRAW;													  //* �����                   90% ����� ����������

	if (!RegisterClassEx(&wClass))                                                            //* ����������� ������ ����
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindowEx(NULL,    //  Ex-style
		wClass.lpszClassName, "",  // ������ ��������� ����� ����������� �����������
		//WS_POPUP /*��������� ����*/, CW_USEDEFAULT, CW_USEDEFAULT,
		WS_OVERLAPPEDWINDOW /*������� ����*/, 0, 0,
		wWidth /*�����*/, wHeight /*������*/, NULL, NULL, wClass.hInstance, NULL); // ==      //* �������� ����
		//INVALID_HANDLE_VALUE)
		if(!hwnd)
	{
		MessageBox(NULL, "Window criaton failed", "", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nCmdShow);															  //* ����� ����
	UpdateWindow(hwnd);																	  //* �����������
	// ������ �������� ��� ����: 
	// 1) ������� �������� �� ����� ����� �����: INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, INT nCmdShow) 
	// � ������ ��������� ���������� ���������
	// 2) ��������� ���� ��������� ���������
	// 3) � ��������������� ������� ��������� ���� ��������� (���������)

	while (GetMessage(&msg, NULL /*��� ��� ���� ����, ��������� 0*/, 0, 0 /*������� ������������ ������ �����*/))												  //* ���� ��������� ���������
	{
		TranslateMessage(&msg); // �������������� ��������� ���������, � ����������� ������� ����� �� ������, �� ��� ������������� ����� ��������
		DispatchMessage(&msg);  // �������� ��������� � ������� ��������� �� ���������
	}

	return static_cast<int>(msg.wParam);  // ������������ �������� ����� ��������� � ��������� msg � ����  wParam ,  
	//static_cast<int> - �������� � ���� int ,  ����� ������ �������� EXIT_SUCCESS 

}