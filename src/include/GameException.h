#pragma once

#include <string>

class GameException
{
public:
	GameException();
	GameException(std::string msg);
	GameException(std::string caption, std::string msg, std::string file, int line);

	std::string msg();
	std::string caption();

private:
	std::string Caption, message, file;
	int line;
};