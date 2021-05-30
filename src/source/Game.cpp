#include "../include/Game.h"
#include "../include/Debug.h"

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0),
	gravity(25.f)
{
	Debug::Println("Instanciating Game");

	Debug::Println("Done instanciating");
}

Game::~Game()
{}

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
	
	player.update(DeltaTime);
}

void Game::render()
{
	wnd.clear();

	player.render(wnd);

	wnd.display();
}