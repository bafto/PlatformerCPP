#include "../../../include/LevelRelated/Enemies/TrackEnemy.h"
#include "../../../include/Utility.h"
#include "../../../include/Game.h"

TrackEnemy::TrackEnemy(sf::Vector2f pos, sf::Vector2f size, float speed)
	:
	Enemy(pos),
	area(size)
{
	this->speed = speed;
	color = sf::Color(205, 92, 92);
	rect.setFillColor(color);
}

TrackEnemy::~TrackEnemy()
{

}

void TrackEnemy::AI(const float& DeltaTime)
{
	//if it saw the player, move towards it
	if (running)
	{
		velocity.x += util::VecNormalize(sf::Vector2f(Game::GetInstance().player.rect.getPosition().x - rect.getPosition().x, 0)).x * speed * DeltaTime;
		velocity = util::VecClamp(velocity, sf::Vector2f(-speed, 0.f), sf::Vector2f(speed, Game::GetInstance().level.gravity));
	}
	nextPosition = rect.getPosition() + velocity;
	sf::Vector2f min = rect.getPosition() - area, max = rect.getPosition() + rect.getSize() + area;
	//if the player entered the area, start following him
	if (!running && !util::IsVecClamp(Game::GetInstance().player.rect.getPosition(), min, max))
		running = true;
}