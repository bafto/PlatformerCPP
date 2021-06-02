#pragma once

#include "Player.h"
#include "LevelRelated/Level.h"
#include "Delegate.h"
#include "NonCopyable.h"
#include "Input.h"

class Game : public NonCopyable
{
public:
	enum class GameMode
	{
		MainMenu = 0,
		InGame,
		DeathScreen
	};

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
	sf::View GetHUDView() { return HUDView; }
	sf::View GetNormalView() { return NormalView; }

private:
	void updateEvents();
	void update();
	void render();
public:
	sf::RenderWindow wnd;

	Input input;

	GameMode gameMode;
	Player player;
	Level level;
private:
	sf::View HUDView, NormalView;

	float DeltaTime;
	sf::Clock DeltaClock;
	int Difficulty;
};