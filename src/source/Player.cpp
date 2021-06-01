#include "../include/Player.h"
#include "../include/Game.h"
#include "../include/Debug.h"
#include "../include/Utility.h"

Player::Player()
	:
	Entity(),
	speed(10.f),
	lastPosition(0.f, 0.f)
{
	rect.setFillColor(sf::Color::Blue);
	noGravity = true;

	Debug::Println("Player constructed");
}

Player::~Player()
{}

void Player::update(const float& DeltaTime)
{
	if (util::IsClamp(rect.getPosition(), { 0.f, 0.f }, Game::GetInstance().level.tilemap.GetPixelSize()))
		Game::GetInstance().level.Reset();

	velocity.x = util::Clamp(velocity.x, -speed, speed);

	//temporary movement code
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x += (-speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += (speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y += (-speed * DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += (speed * DeltaTime);

	lastPosition = rect.getPosition();
	nextPosition = rect.getPosition() + velocity;

	Entity::update(DeltaTime);
}