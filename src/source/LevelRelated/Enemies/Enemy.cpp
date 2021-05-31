#include "../../../include/LevelRelated/Enemies/Enemy.h"
#include "../../../include/Game.h"
#include "../../../include/Utility.h"

Enemy::Enemy(sf::Vector2f pos)
	:
	Entity(),
	startPosition(pos),
	Damage(Game::GetInstance().GetDifficulty())
{
	color = sf::Color::Red;
}

void Enemy::HandleCollision()
{
	if (util::IsClamp(rect.getPosition(), { 0.f, 0.f }, { (float)Game::GetInstance().tilemap.width, (float)Game::GetInstance().tilemap.height }))
		rect.setPosition(startPosition);
	else
		Entity::HandleCollision();
}

void Enemy::AI()
{
	velocity = util::Clamp(velocity, { 0.f, 0.f }, { 0.f, Game::GetInstance().gravity });
	nextPosition = rect.getPosition() + velocity;
}