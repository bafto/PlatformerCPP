#pragma once

#include <string>

//custom exception type for game exceptions
class GameException
{
public:
	GameException();
	GameException(std::string msg);
	GameException(std::string caption, std::string msg, std::string file, int line);

	//get a formatted message
	std::string msg();
	std::string caption();

private:
	std::string Caption, message, file;
	int line;
};

//macro for when a file can't be loaded
#define FILEEXCEPTION(file) GameException("File Exception", "Failed to open \"" + file + "\"", __FILE__, __LINE__)