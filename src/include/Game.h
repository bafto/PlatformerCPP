#pragma once

#include "Player.h"
#include "LevelRelated/Level.h"
#include "Delegate.h"
#include "NonCopyable.h"
#include "Input.h"
#include "UI/UIStates/TestState.h"
#include "UI/UIStates/MainMenu.h"
#include "UI/UIStates/DeathScreen.h"

class Game : public NonCopyable
{
public:
	//The states the game will be in
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
	//only ever called once in main() before run()
	void Initialize();

	//only ever called once in main()
	void run();

public:
	//resets the player and loads a level from levelPath
	void Reset(std::string levelPath);

	sf::View GetHUDView() { return HUDView; } //returns the sf::View used for HUD and UI drawing
	sf::View GetGameView() { return GameView; } //returns the sf::View used for inGame drawing
	const sf::Font& GetFont() { return font; } //returns the font of the game instance

	//adds a string that will be displayed on the top left when ingame (has to be called every frame)
	void AddToHUDText(std::string text) { HUDStr += "\n" + text; } 

private:
	void updateEvents(); //update sfml events on the window
	void update(); //update the current game state
	void render(); //draw the current game state
public:
	sf::RenderWindow wnd; //the window

	Input input; //handles mouse and keyboard input for easy use

	GameMode gameMode; //current game mode
	Player player;
	Level level; //current level if inGame

	int Difficulty; //used to multiply enemy damage values or speeds etc.

private:
	bool frameStep, freeze; //needed for framestepping

private:
	sf::View HUDView, GameView;

	float DeltaTime; //holds the elapsed time since the last frame (used for timers or speed control)
	sf::Clock DeltaClock; //the sf::Clock used for the DeltaTime
	float frameTimer; //used to display the framerate inGame

private:
	sf::Font font; //global font used everywhere

	sf::Text HUDText; //the sf::Text displayed inGame in the top left
	std::string frameRateStr; //the string for the current framerate (is applied to HUDStr so only visible in Debug mode)
	std::string HUDStr; //the HUD string that can be updated from everywhere (only visible in Debug mode)

public:
	DeathScreen deathScreen; //must be public as it takes data for initialization

private:
	TestState testState;
	MainMenu mainMenu;

};