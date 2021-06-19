#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/Utility.h"
#include "../include/GameException.h"

#pragma warning (disable : 26812)

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP", sf::Style::Fullscreen),
	DeltaTime(0),
	Difficulty(0),
	gameMode(GameMode::MainMenu),
	frameTimer(0.f),
	freeze(false),
	frameStep(false)
{
	Debug::Println("Instanciating Game");

	wnd.setFramerateLimit(100); //The game speed depends on the framerate so it is fixed
	if (!font.loadFromFile("assets\\Fonts\\arial.ttf"))
		throw FILEEXCEPTION(std::string("assets\\Fonts\\arial.ttf"));
	HUDText.setFillColor(sf::Color::White);
	HUDText.setFont(font);
	HUDText.setPosition({ 10.f, 10.f });
	HUDText.setCharacterSize(18);

	Debug::Println("Done instanciating Game");
}

Game::~Game()
{}

void Game::Initialize()
{
	Debug::Println("Initializing Game");

	HUDView = sf::View(sf::FloatRect(0, 0, 1920, 1080));

	mainMenu.Initialize();
	deathScreen.Initialize();
	input.Initialize();

	Debug::Println("Done initializing");
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::run()
{
	//closing the window ends the game
	while (wnd.isOpen())
	{
		updateEvents();
		update();
		render();
	}
}

void Game::updateEvents()
{
	//setup input for the next input state
	input.clear();

	sf::Event e;
	while (wnd.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			wnd.close();
			break;
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Escape)
				wnd.close();
			break;
		default:
			break;
		}

		//update keyboard and mouse states
		input.update(e);
	}

	//needed to get correct mouse positions etc.
	input.finishUpdate(&wnd);
}

void Game::update()
{
	DeltaTime = DeltaClock.restart().asSeconds(); //update DeltaTime
#ifdef _DEBUG
	frameTimer += DeltaTime; //update frameTimer by DeltaTime
	HUDStr = frameRateStr; //and set the HUDStr initialiy to frameRateStr
	if (frameTimer >= 0.25f) //framerate is measured every 1/4 second
	{
		frameTimer = 0.f;
		frameRateStr = std::to_string((int)(1.f / DeltaTime));
	}
	AddToHUDText(std::to_string(DeltaTime)); //add the DeltaTime to the HUD
#else
	HUDStr = "";
#endif

	//switch on current gameMode to update either inGame or the correct UIState
	switch (gameMode)
	{
	case Game::GameMode::MainMenu:
		mainMenu.update(DeltaTime);
		break;
	case Game::GameMode::InGame:
		//handle frame stepping in Debug mode, else just update player and level
#ifdef _DEBUG
		if (frameStep)
			freeze = true;
		if (input.KeyboardState(sf::Keyboard::F).pressed)
		{
			frameStep = true;
			freeze = false;
		}
		if (input.KeyboardState(sf::Keyboard::G).pressed)
		{
			frameStep = false;
			freeze = false;
		}
		if (!freeze)
		{
#endif
			//update player and level
			player.update(DeltaTime);
			level.update(DeltaTime);
#ifdef _DEBUG
		}
#endif
#ifdef _DEBUG
		AddToHUDText(player.ToString());
#endif
		break;
	case Game::GameMode::DeathScreen:
		deathScreen.update(DeltaTime);
		break;
	default:
		throw GameException("Game Exception", "Invalid GameMode", __FILE__, __LINE__);
		break;
	}
}

void Game::render()
{
	wnd.clear();

	//switch on current gameMode to render either inGame or the correct UIState
	switch (gameMode)
	{
	case Game::GameMode::MainMenu:
		mainMenu.render(wnd); 
		break;
	case Game::GameMode::InGame:
		//Generate GameView based on the players position
		GameView = sf::View(sf::FloatRect(util::VecClamp(player.rect.getPosition() - sf::Vector2f(960, 540), sf::Vector2f(0.f, 0.f), { level.tilemap.GetPixelSize() - sf::Vector2f(1920, 1080) }), sf::Vector2f(1920, 1080)));
		wnd.setView(GameView);

		//Draw level and player on the GameView
		level.render(wnd);
		player.render(wnd);

		//Draw the HUD string in the HUDView
		wnd.setView(HUDView);

		//Draw inGame HUD (only exists in Debug mode)
		HUDText.setString(HUDStr);
		wnd.draw(HUDText);

		wnd.setView(GameView); //reset the view to GameView
		break;
	case Game::GameMode::DeathScreen:
		deathScreen.render(wnd);
		break;
	default:
		break;
	}

	wnd.display();
}

void Game::Reset(std::string levelPath)
{
	//reset the player
	player = Player();
	player.Initialize();
	//load the level from levelPath
	level.Initialize(levelPath);
	gameMode = GameMode::InGame; //make sure we are inGame
}