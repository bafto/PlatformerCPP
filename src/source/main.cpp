#include "../include/Game.h"
#include "../include/GameException.h"
#include <Windows.h>

int main()
{
	try
	{
		Game::GetInstance().Initialize(); //Initalize the game instance
		Game::GetInstance().run(); //run the game
	}
	catch (GameException& e) //custom exceptions thrown when assets are not loading etc
	{
		MessageBoxA(NULL, e.msg().c_str(), e.caption().c_str(), MB_OK);
	}
	catch (std::exception& e) //standard exceptions for example vector out of range errors
	{
		MessageBoxA(NULL, e.what(), "Standard Exception", MB_OK);
	}
	catch (...) //someone fucked up baaad
	{
		MessageBoxA(NULL, "An error occured", "Unknown Error", MB_OK);
	}

	return 0;
}