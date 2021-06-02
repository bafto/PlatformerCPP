#include "../../../include/LevelRelated/Enemies/SpinEnemy.h"
#include "../../../include/Utility.h"

SpinEnemy::SpinEnemy(sf::Vector2f pos, float distToAnchor, float rotationSpeed)
	:
	Enemy(pos),
	distanceToAnchor(distToAnchor),
	timer(0)
{
	noGravity = true;
	color = sf::Color::Yellow;
	speed = rotationSpeed;
}

SpinEnemy::~SpinEnemy()
{

}

void SpinEnemy::AI()
{
	rect.setPosition(startPosition + util::RotateBy(sf::Vector2f(1, 1), timer) * distanceToAnchor);
	nextPosition = rect.getPosition() + velocity;
	timer += speed / 100;
}

void SpinEnemy::HandleCollision()
{

}