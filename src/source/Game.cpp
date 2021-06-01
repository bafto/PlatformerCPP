#include "../include/Game.h"
#include "../include/Debug.h"

#pragma warning (disable : 26812)

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0),
	Difficulty(1)
{
	Debug::Println("Instanciating Game");

	Debug::Println("Done instanciating Game");
}

Game::~Game()
{}

void Game::Initialize()
{
	Debug::Println("Initializing Game");

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
	}
}

void Game::update()
{
	DeltaTime = DeltaClock.restart().asSeconds();
	
	level.update(DeltaTime);
	player.update(DeltaTime);
}

void Game::render()
{
	wnd.clear();

	wnd.setView(sf::View(player.rect.getPosition(), { 1920, 1080 }));
	level.render(wnd);
	player.render(wnd);

	wnd.display();
}

void Game::Reset(std::string levelPath)
{
	player = Player();
	level.Initialize(levelPath);
}