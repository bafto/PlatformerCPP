#include "../include/Game.h"
#include "../include/GameException.h"
#include <Windows.h>

int main()
{
	try
	{
		Game::GetInstance().Initialize();
		Game::GetInstance().run();
	}
	catch (GameException& e)
	{
		MessageBoxA(NULL, e.msg().c_str(), e.caption().c_str(), MB_OK);
	}
	catch (std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "Standard Exception", MB_OK);
	}
	catch (...)
	{
		MessageBoxA(NULL, "An error occured", "Unknown Error", MB_OK);
	}

	return 0;
}