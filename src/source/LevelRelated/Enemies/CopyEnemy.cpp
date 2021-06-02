#include "../../../include/LevelRelated/Enemies/CopyEnemy.h"
#include "../../../include/Game.h"
#include "../../../include/Utility.h"

CopyEnemy::CopyEnemy(sf::Vector2f pos, float dist)
	:
	Enemy(pos),
	distanceToPlayer(dist)
{
	color = sf::Color::Blue;
	util::Clamp(distanceToPlayer, 1.1f, 60.f);
}

CopyEnemy::~CopyEnemy()
{

}

void CopyEnemy::AI(const float& DeltaTime)
{
	Player& player = Game::GetInstance().player;
	if (player.trail.size() >= 60)
		rect.setPosition(player.trail[(int)(player.trail.size() / distanceToPlayer) - 1]);
	nextPosition = rect.getPosition() + velocity;
}