#include <Windows.h>
#include<cstdio>
#include<string>
#define TIMER_ID 1
int faillingStep = 0;
int wWidth{}, wHeight{}, x{}, y{};
	HDC hdc{};
	CHAR sz_buff[256] = {};
	HWND hwnd{};
	HCURSOR hCursor = NULL;
	MSG msg{};
BOOL WINAPI /*говорит о том, что вызываемый объект будет сам за собой очищать стэк*/
wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass{ sizeof(WNDCLASSEX) };//<-с помощью агрегатной инициализации задaём//* Размер класса, это делать обязательно, можно через доступ к полю
	wClass.cbClsExtra = 0;  // эти два поля отвечают за дополнительное выделение памяти  // CountBytes
	wClass.cbWndExtra = 0;  // чтобы можно было передать информацию в класс окна, чтобы потом можно было воспользоваться этой информацией, задается размер в байтах
	wClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));	     //* Кисть  Оператор reinterpret_cast ->  https://learn.microsoft.com/ru-ru/cpp/cpp/reinterpret-cast-operator?view=msvc-170
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);										 //* Курсор
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);										 //* Иконка большая
	wClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);									 //* Иконка маленькая
	wClass.hInstance = hInstance;															 //* Приложение
	wClass.lpfnWndProc = [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)->LRESULT	 //* Процедура     // Что означает [] (лямбда-функция)? https://docs.google.com/document/d/1_THS_7VJuPY20n1fowRICpFB0hsZYURYKrG0dG4Z3uc/edit?usp=sharing
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
					MessageBox(hwnd, "Не удалось загрузить курсор", "Ошибка", MB_ICONERROR);
				}
				//процентнопрозрачное окно
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
				int xPos = (screenWidth - wWidth)/2;//(rc.right - rc.left)/* НАШ_РАЗМЕР*/ ) / 2;               НАШ_РАЗМЕР = SM_CXSCREEN * 75 / 100
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
				// Динамическое обновление заголовка во время перетаскивания
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
				
				// отрисовка заголовка
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

			//		// Падение вниз
			//		int newY = rect.top + 20;
			//		if (newY >= screenHeight)
			//		{
			//			KillTimer(hWnd, TIMER_ID);
			//			DestroyWindow(hWnd); // Закрытие окна после завершения анимации
			//		}
			//		else
			//		{
			//			// Уменьшение высоты, имитируя "разбивание"
			//			int newHeight = max((rect.bottom - rect.top) - 10, 50);

			//			MoveWindow(hWnd, rect.left, newY, rect.right - rect.left, newHeight, TRUE);
			//		}
			//	}
			//}
			//break;
			//case WM_CLOSE:
			//{
			//	SetTimer(hWnd, TIMER_ID, 30, NULL); // Устанавливаем таймер для анимации
			//	return 0; // Блокируем стандартное закрытие
			//}
			case WM_NCLBUTTONDOWN: {
				if (wParam == HTCAPTION) {
					// Обновляем положение перед началом перетаскивания
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
				//перетаскивание окна
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

	wClass.lpszClassName = "AppClassName";													  //* Имя класса
	wClass.lpszMenuName = NULL;															  //* Меню
	wClass.style = CS_VREDRAW | CS_HREDRAW;													  //* Стиль                   90% такая комбинация

	if (!RegisterClassEx(&wClass))                                                            //* Регистрация класса окна
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	hwnd = CreateWindowEx(NULL,    //  Ex-style
		wClass.lpszClassName, "",  // второй заголовок будет обновляться динамически
		//WS_POPUP /*необычное окно*/, CW_USEDEFAULT, CW_USEDEFAULT,
		WS_OVERLAPPEDWINDOW /*обычное окно*/, 0, 0,
		wWidth /*ширин*/, wHeight /*высота*/, NULL, NULL, wClass.hInstance, NULL); // ==      //* Создание окна
		//INVALID_HANDLE_VALUE)
		if(!hwnd)
	{
		MessageBox(NULL, "Window criaton failed", "", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	ShowWindow(hwnd, nCmdShow);															  //* Показ окна
	UpdateWindow(hwnd);																	  //* Перерисовка
	// Теперь осталось три вещи: 
	// 1) Вернуть значение из нашей точки входа: INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, INT nCmdShow) 
	// в случае успешного выполнения программы
	// 2) Запустить цикл обработки сообщений
	// 3) И скорректировать функцию обработки этих сообщений (процедуру)

	while (GetMessage(&msg, NULL /*так как одно окно, указываем 0*/, 0, 0 /*фильтры используются крайне редко*/))												  //* Цикл обработки сообщений
	{
		TranslateMessage(&msg); // расшифровывает сообщение системное, в современных версиях можно не писать, но для совместимости лучше написать
		DispatchMessage(&msg);  // передает сообщение в оконную процедуру на обработку
	}

	return static_cast<int>(msg.wParam);  // возвращаемое значение будет храниться в структуре msg в поле  wParam ,  
	//static_cast<int> - приводим к типу int ,  можно просто написать EXIT_SUCCESS 

}