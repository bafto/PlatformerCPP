#pragma once

#include "GeneralIncludes.h"
#include "Player.h"

class Game
{
private:
	Game();

public:
	//delete all copy stuff as of the singleton design pattern
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	void operator=(const Game&) = delete;
	void operator=(Game&&) = delete;

	~Game();
public:
	//Get the Only instance of the game to ever exist following the singleton design pattern
	static Game& GetInstance();

	//only ever called once in main()
	void run();
private:
	void updateEvents();
	void update();
	void render();
public:
	sf::RenderWindow wnd;

	//Test stuff
	Player player;
	const float gravity;
private:
	float DeltaTime;
	sf::Clock DeltaClock;
};