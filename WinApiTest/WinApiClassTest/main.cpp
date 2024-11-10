#include<Windows.h>
#include"resource.h"

INT WINAPI(HINSTANCE /*дескриптор экземпл€ра приложени€*/ hInstance, 
	HINSTANCE hPrevInst, 
	LPSTR lpCmdLine /*позвол€ет передавать парамтеры чере cmd*/,
	INT nCmdShow /*режим отображени€ окна*/)
{
	MessageBox(/*модальное окно сообщени€ https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
   которое ЅЋќ ирует доступ к
   основному приложению */
		NULL /*родительское окно, если его нет, пишетс€ 0*/,
		"Hello WinAPI!\nЁто окно сообщени€" /*сообщением, которое будет выводить данное окно */,
		"Info" /*заголовок окна*/,
		MB_OK /*флаг определ€ющий какой будет вывоод кнопок*/ |
		MB_ICONINFORMATION /*флаги определ€ющий значок в окне перед сообщением*/ |
		MB_DEFBUTTON1 /*кнопка по умолчанию, на которой находитс€ фокус*/
	);
	return 0;
}