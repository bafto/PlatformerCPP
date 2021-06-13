#pragma once

#include "Player.h"
#include "LevelRelated/Level.h"
#include "Delegate.h"
#include "NonCopyable.h"
#include "Input.h"
#include "UI/UIStates/TestState.h"
#include "UI/UIStates/MainMenu.h"

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

	sf::View GetHUDView() { return HUDView; }
	sf::View GetGameView() { return GameView; }
	const sf::Font& GetFont() { return font; }
	void AddToHUDText(std::string text) { HUDStr += "\n" + text; }

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

	int Difficulty;

private:
	bool frameStep, freeze;

private:
	sf::View HUDView, GameView;

	float DeltaTime, frameTimer;
	sf::Clock DeltaClock;

private:
	sf::Text HUDText;
	sf::Font font;
	std::string frameRateStr;
	std::string HUDStr;

private:
	TestState testState;
	MainMenu mainMenu;

};