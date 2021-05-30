#include "../include/Game.h"
#include <Windows.h>

int main()
{
	try
	{
		Game::GetInstance().run();
	}
	catch (...)
	{
		MessageBoxA(NULL, "An error occured", "Error", MB_OK);
	}

	return 0;
}