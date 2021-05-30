#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Debug.h"

Player::Player()
{
	rect.setFillColor(sf::Color::Red);
	rect.setSize({ 50, 50 });
	rect.setPosition({ 0, 0 });

	Debug::Println("Player constructed");
}

Player::~Player()
{}

void Player::update(const float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		rect.setPosition(rect.getPosition() + sf::Vector2f(0, -Game::GetInstance().PlayerSpeed * DeltaTime));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		rect.setPosition(rect.getPosition() + sf::Vector2f(-Game::GetInstance().PlayerSpeed * DeltaTime, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		rect.setPosition(rect.getPosition() + sf::Vector2f(0, Game::GetInstance().PlayerSpeed * DeltaTime));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		rect.setPosition(rect.getPosition() + sf::Vector2f(Game::GetInstance().PlayerSpeed * DeltaTime, 0));
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(rect);
}