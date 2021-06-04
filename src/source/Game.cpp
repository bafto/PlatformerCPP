#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/GameException.h"

#pragma warning (disable : 26812)

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0),
	Difficulty(1),
	gameMode(GameMode::InGame),
	frameTimer(0.f)
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

	input.Initialize();
	level.Initialize("assets\\Levels\\level0.level");

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
		break;
	case Game::GameMode::InGame:
		player.update(DeltaTime);
		level.update(DeltaTime);
		break;
	case Game::GameMode::DeathScreen:
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
		wnd.setView(HUDView);
		break;
	case Game::GameMode::InGame:
		GameView = sf::View(player.rect.getPosition(), { 1920, 1080 });
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
		wnd.setView(HUDView);
		break;
	default:
		break;
	}

	wnd.display();
}

void Game::Reset(std::string levelPath)
{
	player = Player();
	level.Initialize(levelPath);
}