#pragma once

#include "Player.h"
#include "LevelRelated/Level.h"
#include "Delegate.h"

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
	void Initialize();

	//only ever called once in main()
	void run();

public:
	int GetDifficulty() { return Difficulty; }

private:
	void updateEvents();
	void update();
	void render();
public:
	sf::RenderWindow wnd;

	//Test stuff
	Player player;
	Level level;
	Delegate<int()> onClick;
	Delegate<void(sf::Vector2f)> onClick2;
private:
	float DeltaTime;
	sf::Clock DeltaClock;
	int Difficulty;
};