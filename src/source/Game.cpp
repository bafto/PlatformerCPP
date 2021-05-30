#include "../include/Game.h"
#include "../include/Debug.h"

Game::Game()
	:
	wnd(sf::VideoMode::getDesktopMode(), "PlatformerCPP"),
	DeltaTime(0),
	TexMap("./assets/Levels/TextMap0.texmap")
{
	Debug::Println("Instanciating Game");

	for (int i = 0; i < 16; i++)
	{
		sf::RectangleShape shape;
		shape.setSize({ 16, 16 });
		shape.setPosition({ i * 16.f, 0 });
		shape.setTexture(&TexMap.textures[0][i]);
		shapes.push_back(shape);
	}
	for (int i = 0; i < 16; i++)
	{
		sf::RectangleShape shape;
		shape.setSize({ 16, 16 });
		shape.setPosition({ i * 16.f, 16 });
		shape.setTexture(&TexMap.textures[1][i]);
		shapes.push_back(shape);
	}
	for (int i = 0; i < 16; i++)
	{
		sf::RectangleShape shape;
		shape.setSize({ 16, 16 });
		shape.setPosition({ i * 16.f, 32 });
		shape.setTexture(&TexMap.textures[2][i]);
		shapes.push_back(shape);
	}

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

	for (auto& shape : shapes)
	{
		wnd.draw(shape);
	}
	player.render(wnd);

	wnd.display();
}