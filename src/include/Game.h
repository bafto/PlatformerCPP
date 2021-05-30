#pragma once

#include "GeneralIncludes.h"

class Game
{
private:
	Game();

public:
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	void operator=(const Game&) = delete;
	void operator=(Game&&) = delete;

public:
	static Game& GetInstance();

	void run();
private:
	void updateEvents();
	void update();
	void render();
public:
	sf::RenderWindow wnd;

	//Test stuff
	sf::RectangleShape shape;
private:
	float DeltaTime;
	sf::Clock DeltaClock;
};