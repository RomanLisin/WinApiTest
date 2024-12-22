#include <windows.h>
#include<commctrl.h> // для работы с прогресс-баром
#include <shlobj.h>
#include <string>

#pragma comment(lib,"Comctl32.lib")

HINSTANCE hInst;
HWND hProgressBar;

VOID CopyDirectory(LPCSTR source, LPCSTR target);
VOID CreateShortcut(LPCSTR shortcutPath, LPCSTR targetPath, LPCSTR description);
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//Регистрация класса
	WNDCLASSEX wClass = {};
	//ZeroMemory(&wClass, sizeof(wClass)); 
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.hInstance = hInstance;
	wClass.lpszClassName = "SetupApp";
	wClass.lpszMenuName = NULL;
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2 создание окна

	HWND hwnd = CreateWindowEx
	(
		NULL,
		"SetupApp", "Установщик калькулятора",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 300, NULL, NULL, hInstance, NULL
	);
	if (!hwnd) return -1;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3 запуск цилка сообщений

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hInstallButton;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		// кнопка установить
		hInstallButton = CreateWindow("Button", "Установить", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			140, 160, 120, 30, hwnd, (HMENU)1, hInst, NULL);

		hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
			50, 50, 300, 30, hwnd, NULL, hInst, NULL);
		SendMessage(hProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
	}
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 1)
		{  // если нажата кнопка установить
			LPCSTR sourcePath = "C:\\Users\\rls\\source\\repos\\WindowsDevelopment\\WinAPI\\Calc";
			LPCSTR installDirectory = "C:\\Program Files\\Calc";
			LPCSTR shortcutPath = "C:\\Users\\rls\\Desktop\\Calc.lnk";

			//Создание папки назначения
			if (CreateDirectory(installDirectory,NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
			{
				/*DWORD error = GetLastError();
				MessageBox(hwnd, std::to_string(error).c_str(), "Код ошибки", MB_OK);*/

				// обновляем прогресс
				SendMessage(hProgressBar, PBM_SETPOS, 25, 0);

				//копирование каталога
				CopyDirectory(sourcePath, installDirectory);
				SendMessage(hProgressBar, PBM_SETPOS, 75, 0);

				CHAR exePath[MAX_PATH] = { 0 };
				WIN32_FIND_DATA findFileData;
				HANDLE hFind;

				CHAR searchPath[MAX_PATH];
				wsprintf(searchPath, "%s\\*.exe", sourcePath);
				hFind = FindFirstFile(searchPath, &findFileData);

				if (hFind != INVALID_HANDLE_VALUE) {
					wsprintf(exePath, "%s\\%s", sourcePath, findFileData.cFileName);
					FindClose(hFind);

					CreateShortcut(shortcutPath, exePath, "Запустить MyApp");
					SendMessage(hProgressBar, PBM_SETPOS, 100, 0);

					MessageBox(hwnd, "Установка завершена!", "Информация", MB_OK | MB_ICONINFORMATION);
				}
				else {
					MessageBox(hwnd, "Файл .exe не найден!", "Ошибка", MB_OK | MB_ICONERROR);
				}
			}
			else {
				MessageBox(hwnd, "Ошибка создания каталога.", "Ошибка", MB_OK | MB_ICONERROR);
			}
			
		}
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;
	case WM_CLOSE: DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}

void CopyDirectory(LPCSTR source, LPCSTR target) 
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind;

	CHAR searchPath[MAX_PATH];
	wsprintf(searchPath, "%s\\*", source);
	hFind = FindFirstFile(searchPath, &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			if (lstrcmp(findFileData.cFileName, ".") != 0 && lstrcmp(findFileData.cFileName, "..") != 0) {
				CHAR sourcePath[MAX_PATH];
				CHAR targetPath[MAX_PATH];

				wsprintf(sourcePath, "%s\\%s", source, findFileData.cFileName);
				wsprintf(targetPath, "%s\\%s", target, findFileData.cFileName);

				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					CreateDirectory(targetPath, NULL);
					CopyDirectory(sourcePath, targetPath);
				}
				else {
					CopyFile(sourcePath, targetPath, FALSE);
				}
			}
		} while (FindNextFile(hFind, &findFileData));
		FindClose(hFind);
	}
}

void CreateShortcut(LPCSTR shortcutPath, LPCSTR targetPath, LPCSTR description) 
{
	CoInitialize(NULL);

	IShellLink* pShellLink = NULL;
	HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pShellLink);

	if (SUCCEEDED(hr))
	{
		pShellLink->SetPath(targetPath);
		pShellLink->SetDescription(description);

		IPersistFile* pPersistFile = NULL;
		hr = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
		if (SUCCEEDED(hr)) {
			WCHAR wsz[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, shortcutPath, -1, wsz, MAX_PATH);
			hr = pPersistFile->Save(wsz, TRUE);
			pPersistFile->Release();
		}
		pShellLink->Release();
	}

	CoUninitialize();
}




