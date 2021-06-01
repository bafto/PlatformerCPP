#include "../include/GameException.h"

GameException::GameException()
	:
	Caption("Game Exception"),
	message("No Information"),
	file("Unknown"),
	line(-1)
{

}

GameException::GameException(std::string msg)
	:
	Caption("Game Exception"),
	message(msg),
	file("Unknown"),
	line(-1)
{

}

GameException::GameException(std::string caption, std::string msg, std::string file, int line)
	:
	Caption(caption),
	message(msg),
	file(file),
	line(line)
{

}

std::string GameException::msg()
{
	return line != -1 ? "File: " + file + "\nLine: " + std::to_string(line) + "\n" + message : message;
}

std::string GameException::caption()
{
	return Caption;
}