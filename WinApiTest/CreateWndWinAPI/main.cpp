#include<Windows.h>


INT WINAPI WinMain(
	HINSTANCE hInstance, //  ���������� ���������� �������� ����������, HINSTANCE - Handle Instance
	HINSTANCE hPrevInst, // hPrevInstance - ���������� ����������� ���������� ����������, - Handle Previous Instance
	LPSTR lpszCmdLine, // Long Pointer to String ( ����������� �������� ������������� ����������� ����� �������� �.�. 64 ���  .... lpszCmdLine  ������������ ������ �� ��������� ������
	//  -  long pointer to string zero Command Line  -  ��������� �� ������ (string zero - �������� ������ � ����� ������� ���� � ������� ���������) 
	// Command Line - �������� ��� ������ ������ �������� ���������� ���������� ����� ��������� ������
	INT CmdShow  //  ������������ ��� ����������� �������� � ������� BOOL ShowWindow(...), ���������� ����� ����������� ���� (��������, ����������� � �.�.)
)
//int main()
{
	//HINSTANCE hInstance = GetModuleHandleA(0); // ����� ������������ main() ������ WinMain()  55:00
	//int iShow = 10; // ��� ShowWindow ��������, ��� ����� ����������� ���� SW_SHOWDEFAULT �.�. �� ����� ����� ������� ����� �����
	WNDCLASSA wcl;  // ������ ��������� ������ ����
	memset(&wcl, 0, sizeof(WNDCLASSA));  // �������������� ������
	wcl.lpszClassName = "my Window";
	wcl.lpfnWndProc = DefDlgProcA; // ��������� ��������� ��������� �� ���������
	// ������������ ����� ���� ����� �������� � ������� ������ �� ��������� ������ ����
	RegisterClassA(&wcl);

	HWND hwnd;
	hwnd = CreateWindowA("my Window", "Window Name", WS_OVERLAPPEDWINDOW,10, 10, 640, 480, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);  // ������� �������� ��������� � ���� ���� � � ���� ������� �������� �������, ������� ���� ������� � lpfnWndProc ��������� ������ ����

	}
	return 0;
}