#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/GameException.h"

#pragma warning (disable : 26812)

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0),
	Difficulty(0),
	gameMode(GameMode::InGame),
	frameCounter(0),
	frameTimer(0.f)
{
	Debug::Println("Instanciating Game");

	wnd.setFramerateLimit(100);
	if (!font.loadFromFile("assets\\Fonts\\arial.ttf"))
		throw FILEEXCEPTION(std::string("assets\\Fonts\\arial.ttf"));
	FramerateText.setFillColor(sf::Color::White);
	FramerateText.setFont(font);
	FramerateText.setPosition({ 10.f, 10.f });
	FramerateText.setCharacterSize(18);

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
	frameCounter++;
	frameTimer += DeltaTime;
	HUDText = frameRateStr;
	if (frameTimer >= 0.25f)
	{
		frameTimer = 0.f;
		frameRateStr = std::to_string((int)(1.f / DeltaTime));
		frameCounter = 0;
	}
	
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
		FramerateText.setString(HUDText);
		wnd.draw(FramerateText);

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