#include "../../../include/LevelRelated/Enemies/PathEnemy.h"
#include "../../../include/Utility.h"
#include "../../../include/Game.h"

PathEnemy::PathEnemy(sf::Vector2f pos, int Start, int Stop, float speed)
	:
	Enemy(pos),
	start(Start),
	stop(Stop)
{
	this->speed = speed;
	color = sf::Color(139, 0, 0);
	rect.setFillColor(color);
	Damage = 2;
}

PathEnemy::~PathEnemy()
{

}

void PathEnemy::AI(const float& DeltaTime)
{
	//turn around at either end of the path
	velocity.x += turn ? speed * DeltaTime : -speed * DeltaTime;

	velocity = util::VecClamp(velocity, { -speed, 0.f }, { speed, Game::GetInstance().level.gravity });

	nextPosition = rect.getPosition() + velocity;

	//turn in the other direction if either end of the path is reached
	if (turn)
	{
		if (rect.getPosition().x + rect.getSize().x > stop)
		{
			turn = false;
			velocity.x = 0;
		}
	}
	else
	{
		if (rect.getPosition().x < start)
		{
			turn = true;
			velocity.x = 0;
		}
	}
}
