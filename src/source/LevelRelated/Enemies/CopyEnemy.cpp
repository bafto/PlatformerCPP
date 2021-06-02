#include "../../../include/LevelRelated/Enemies/CopyEnemy.h"
#include "../../../include/Game.h"

CopyEnemy::CopyEnemy(sf::Vector2f pos, float dist)
	:
	Enemy(pos),
	distanceToPlayer(dist)
{
	color = sf::Color::Blue;
}

CopyEnemy::~CopyEnemy()
{

}

void CopyEnemy::AI()
{
	Player& player = Game::GetInstance().player;
	if (player.trail.size() >= 60)
		rect.setPosition(player.trail[(int)(player.trail.size() / distanceToPlayer) - 1]);
	nextPosition = rect.getPosition() + velocity;
}