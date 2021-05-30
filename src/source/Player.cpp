#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Debug.h"

Player::Player()
	:
	Entity(),
	speed(70.f)
{
	rect.setFillColor(sf::Color::Red);

	Debug::Println("Player constructed");
}

Player::~Player()
{}

void Player::update(const float DeltaTime)
{
	//temporary movement code

	velocity = { 0, 0 };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y += (-speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x += (-speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += (speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += (speed * DeltaTime);

	Entity::update(DeltaTime);

	rect.move(velocity);
}