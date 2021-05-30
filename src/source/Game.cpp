#include "../include/Game.h"

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0)
{
	Debug::Println("Instanciating Game");

	shape.setFillColor(sf::Color::Red);
	shape.setPosition({ 0, 0 });
	shape.setSize({ 50, 50 });

	Debug::Println("Done instanciating");
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		shape.setPosition(shape.getPosition() + sf::Vector2f(0, -30 * DeltaTime));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		shape.setPosition(shape.getPosition() + sf::Vector2f(-30 * DeltaTime, 0));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		shape.setPosition(shape.getPosition() + sf::Vector2f(0, 30 * DeltaTime));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		shape.setPosition(shape.getPosition() + sf::Vector2f(30 * DeltaTime, 0));
}

void Game::render()
{
	wnd.clear();

	wnd.draw(shape);

	wnd.display();
}