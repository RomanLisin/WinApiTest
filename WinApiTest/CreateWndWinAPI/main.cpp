#include<Windows.h>


INT WINAPI WinMain(
	HINSTANCE hInstance, //  дескриптор экземпл€ра текущего приложени€, HINSTANCE - Handle Instance
	HINSTANCE hPrevInst, // hPrevInstance - дескриптор предыдущего экземпл€ра приложени€, - Handle Previous Instance
	LPSTR lpszCmdLine, // Long Pointer to String ( разр€дность которого соответствует разр€дности нашей прграммы т.е. 64 бит  .... lpszCmdLine  прдоставл€ет доступ ко командной строке
	//  -  long pointer to string zero Command Line  -  указатель на строку (string zero - означает строка в конце который байт с нулевым значением) 
	// Command Line - означает что данна€ строка содержит переменные переданные через командную строку
	INT CmdShow  //  используетс€ дл€ последующей передачи в функцию BOOL ShowWindow(...), определ€ет режим отображени€ окна (свЄрнутое, развернутое и т.д.)
)
//int main()
{
	//HINSTANCE hInstance = GetModuleHandleA(0); // чтобы использовать main() вместо WinMain()  55:00
	//int iShow = 10; // дл€ ShowWindow означает, что режим отображени€ окна SW_SHOWDEFAULT т.е. мы можем режим указать через €рлык
	WNDCLASSA wcl;  // создаЄм экземпл€р класса окна
	memset(&wcl, 0, sizeof(WNDCLASSA));  // инициализируем нул€ми
	wcl.lpszClassName = "my Window";
	wcl.lpfnWndProc = DefDlgProcA; // процедура обработки сообщений по умолчанию
	// регистрируем класс окна путем передачи в функцию ссылки на экземпл€р класса окна
	RegisterClassA(&wcl);

	HWND hwnd;
	hwnd = CreateWindowA("my Window", "Window Name", WS_OVERLAPPEDWINDOW,10, 10, 640, 480, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);  // функци€ передает сообщение в наше окно и в свою очередь вызывает функцию, котора€ была указана в lpfnWndProc структуры класса окна

	}
	return 0;
}