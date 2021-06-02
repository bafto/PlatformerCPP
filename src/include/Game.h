#pragma once

#include "Player.h"
#include "LevelRelated/Level.h"
#include "Delegate.h"
#include "NonCopyable.h"
#include "Input.h"

class Game : public NonCopyable
{
private:
	Game();

public:
	virtual ~Game();

public:
	//Get the Only instance of the game to ever exist following the singleton design pattern
	static Game& GetInstance();
	void Initialize();

	//only ever called once in main()
	void run();

public:
	void Reset(std::string levelPath);

	int GetDifficulty() { return Difficulty; }

private:
	void updateEvents();
	void update();
	void render();
public:
	sf::RenderWindow wnd;

	Input input;

	Player player;
	Level level;
private:
	float DeltaTime;
	sf::Clock DeltaClock;
	int Difficulty;
};