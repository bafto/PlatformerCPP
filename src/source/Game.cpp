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

	wnd.setFramerateLimit(100);
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

	//testState.Initialize();
	mainMenu.Initialize();
	deathScreen.Initialize();
	input.Initialize();
	/*player.Initialize();
	level.Initialize("assets\\Levels\\level0.level");*/

	Debug::Println("Done initializing");
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::run()
{
	while (wnd.isOpen())
	{
		updateEvents();
		update();
		render();
	}
}

void Game::updateEvents()
{
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

		input.update(e);
	}

	input.finishUpdate(&wnd);
}

void Game::update()
{
	DeltaTime = DeltaClock.restart().asSeconds();
#ifdef _DEBUG
	frameTimer += DeltaTime;
	HUDStr = frameRateStr;
	if (frameTimer >= 0.25f)
	{
		frameTimer = 0.f;
		frameRateStr = std::to_string((int)(1.f / DeltaTime));
	}
	AddToHUDText(std::to_string(DeltaTime));
#else
	HUDStr = "";
#endif

	switch (gameMode)
	{
	case Game::GameMode::MainMenu:
		mainMenu.update(DeltaTime);
		//testState.update(DeltaTime);
		break;
	case Game::GameMode::InGame:
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

	switch (gameMode)
	{
	case Game::GameMode::MainMenu:
		mainMenu.render(wnd); 
		//testState.render(wnd);
		break;
	case Game::GameMode::InGame:
		GameView = sf::View(sf::FloatRect(util::VecClamp(player.rect.getPosition() - sf::Vector2f(960, 540), sf::Vector2f(0.f, 0.f), { level.tilemap.GetPixelSize() - sf::Vector2f(1920, 1080) }), sf::Vector2f(1920, 1080)));
		wnd.setView(GameView);

		level.render(wnd);
		player.render(wnd);

		wnd.setView(HUDView);

		//Draw Global HUD
		HUDText.setString(HUDStr);
		wnd.draw(HUDText);

		wnd.setView(GameView);
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
	player = Player();
	player.Initialize();
	level.Initialize(levelPath);
	gameMode = GameMode::InGame;
}