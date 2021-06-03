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
	sf::View GetGameView() { return GameView; }
	const sf::Font& GetFont() { return font; }
	void AddToHUDText(std::string text) { HUDText += "\n" + text; }

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
	sf::View HUDView, GameView;

	float DeltaTime, frameTimer;
	sf::Clock DeltaClock;
	int Difficulty;
	unsigned int frameCounter;

private:
	sf::Text FramerateText;
	sf::Font font;
	std::string frameRateStr;
	std::string HUDText;

};