#include<Windows.h>
#include"resource.h"

INT WINAPI(HINSTANCE /*���������� ���������� ����������*/ hInstance, 
	HINSTANCE hPrevInst, 
	LPSTR lpCmdLine /*��������� ���������� ��������� ���� cmd*/,
	INT nCmdShow /*����� ����������� ����*/)
{
	MessageBox(/*��������� ���� ��������� https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
   ������� ��������� ������ �
   ��������� ���������� */
		NULL /*������������ ����, ���� ��� ���, ������� 0*/,
		"Hello WinAPI!\n��� ���� ���������" /*����������, ������� ����� �������� ������ ���� */,
		"Info" /*��������� ����*/,
		MB_OK /*���� ������������ ����� ����� ������ ������*/ |
		MB_ICONINFORMATION /*����� ������������ ������ � ���� ����� ����������*/ |
		MB_DEFBUTTON1 /*������ �� ���������, �� ������� ��������� �����*/
	);
	return 0;
}