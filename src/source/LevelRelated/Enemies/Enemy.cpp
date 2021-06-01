#include "../../../include/LevelRelated/Enemies/Enemy.h"
#include "../../../include/Game.h"
#include "../../../include/Utility.h"

Enemy::Enemy(sf::Vector2f pos)
	:
	Entity(),
	startPosition(pos),
	speed(25.f),
	Damage(1/*Game::GetInstance().GetDifficulty()*/)
{
	color = sf::Color::Red;
	rect.setFillColor(color);
}

void Enemy::update(const float& DeltaTime)
{
	AI();
	Entity::update(DeltaTime);
}

void Enemy::HandleCollision()
{
	if (util::IsClamp(rect.getPosition(), { 0.f, 0.f }, Game::GetInstance().tilemap.GetPixelSize()))
		rect.setPosition(startPosition);
	else
		Entity::HandleCollision();
}

void Enemy::AI()
{
	velocity = util::Clamp(velocity, { 0.f, 0.f }, { 0.f, Game::GetInstance().gravity });
	nextPosition = rect.getPosition() + velocity;
}