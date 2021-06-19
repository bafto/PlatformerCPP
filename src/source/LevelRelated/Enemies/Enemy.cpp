#include "../../../include/LevelRelated/Enemies/Enemy.h"
#include "../../../include/Game.h"
#include "../../../include/Utility.h"

Enemy::Enemy(sf::Vector2f pos)
	:
	Entity(),
	startPosition(pos),
	speed(25.f),
	Damage(Game::GetInstance().Difficulty)
{
	color = sf::Color::Red;
	rect.setFillColor(color);
	rect.setPosition(startPosition);
}

Enemy::~Enemy()
{}

void Enemy::update(const float& DeltaTime)
{
	AI(DeltaTime);
	Entity::update(DeltaTime);
}

void Enemy::HandleCollision()
{
	//reset the position if enemy falls out of the world
	if (util::IsVecClamp(rect.getPosition(), { 0.f, 0.f }, Game::GetInstance().level.tilemap.GetPixelSize()))
		rect.setPosition(startPosition);
	else
		Entity::HandleCollision();
}

void Enemy::AI(const float& DeltaTime)
{
	//only apply gravity, without other movement
	velocity = util::VecClamp(velocity, { 0.f, 0.f }, { 0.f, Game::GetInstance().level.gravity });
	nextPosition = rect.getPosition() + velocity;
}